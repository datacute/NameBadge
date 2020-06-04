/* 
 * Name Badge
 * 
 * Displays a name badge.
 * 
 * When using Spence Konde's ATTinyCore https://github.com/SpenceKonde/ATTinyCore
 * and using a chip without Optiboot, with LTO enabled, this sketch takes 8160 bytes of flash.
 * 
 * The Name Badge contains 5 screens
 * A screen is a list of 16 items
 * An item is a portion of a text string shown in a particular location, font, and font size.
 * The text string is able to be up to 256 characters long.
 * 
 * The details are stored in EEPROM
 * 
 * Menu system
 * -----------
 * Single button menu system to support editing every detail.
 * A short press on the button changes selection, a long press on the button actions the selection.
 * A second button is also supported, and a short press on the second button actions the selection.
 * 
 * 4 fonts:
 *   6x8
 *   8x16
 *   Menu Icons
 *   QR Code
 * 
 * Power on:
 * set up buttons
 * Load contrast from EEPROM
 * Load current screen number from EEPROM
 * Display current screen
 * turn on screen
 * Go to sleep till a button is pressed.
 * 
 */

#include <avr/sleep.h>
#include <EEPROM.h>
#include <TinyI2CMaster.h>
#include <Tiny4kOLED.h>
#include "eeprom_contents.h"
#include "symbol_font.h"
#include "qr_code_font.h"
#include "menus.h"

// Routines to set and clear bits (used in the sleep code)
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

const DCfont * const fonts[] PROGMEM = { FONT6X8, FONT8X16, &symbolFont, &qrCodeFont };

static bool eepromOk = false;
static uint8_t currentContrast = 16;

static uint8_t currentScreen = 0;
static uint8_t currentScreenItem;

static uint8_t currentMode = 0;
static uint8_t lastMode = 0;

static uint8_t numMenuItems;
static MenuItem * menuItems;
static uint8_t menuLine;

static uint8_t itemLocationX;
static uint8_t itemLocationY;
static uint8_t itemFontNum;
static const DCfont * itemFont;
static uint8_t itemDoubleSize;
static uint8_t itemOffset;
static uint16_t itemAddress;
static uint8_t itemLength;
static uint8_t currentItemCharacterPos;
static uint8_t currentLetter;

#define MAIN_BUTTON 4
#define ENTER_BUTTON 1
static bool mainButtonWasDown = false;
static bool enterButtonWasDown = false;
static bool longPressActioned = false;
static long buttonDownTime;
#define LONG_PRESS_REPEAT 500L

ISR(PCINT0_vect) {}

void setup() {
  setupADC();
  setupInputs();
  setupOLED();
  setupFromEEPROM();
  oled.setContrast(currentContrast);
  displayScreenForMode();
  oled.on();
}

static void setupADC() {
  ADMUX = 0b1100<<MUX0; // Vcc Ref, Measure bandgap voltage (1.1)
  ADCSRA = 1<<ADEN | 4<<ADPS0;            // Enable, 62.5kHz ADC clock (16x prescalar)
}

void setupInputs() {
  pinMode(MAIN_BUTTON, INPUT_PULLUP);
  pinMode(ENTER_BUTTON, INPUT_PULLUP);
  GIMSK = 1 << PCIE;                   // Enable pin-change interrupt
  PCMSK = (1 << MAIN_BUTTON) | (1 << ENTER_BUTTON);
}

void setupOLED(void) {
  oled.begin(128, 64, sizeof(tiny4koled_init_128x64r), tiny4koled_init_128x64r);
}

static void setupFromEEPROM() {
  eepromOk = EEPROM.read(NAMEBADGE_MAGIC_ADDRESS    ) == NAMEBADGE_MAGIC0 &&
             EEPROM.read(NAMEBADGE_MAGIC_ADDRESS + 1) == NAMEBADGE_MAGIC1 &&
             EEPROM.read(NAMEBADGE_MAGIC_ADDRESS + 2) == NAMEBADGE_MAGIC2 &&
             EEPROM.read(NAMEBADGE_MAGIC_ADDRESS + 3) == NAMEBADGE_MAGIC3;
  if (eepromOk) {
    currentScreen = EEPROM.read(NAMEBADGE_CURRENT_SCREEN_ADDRESS);
    currentContrast = EEPROM.read(NAMEBADGE_CONTRAST_ADDRESS);
  } else {
    currentMode = SETTINGS_MENU_MODE;
  }
}

static void displayScreenForMode() {
  numMenuItems = pgm_read_byte(&(menus[currentMode].numItems));
  menuItems = pgm_read_word(&(menus[currentMode].items));
  ((DisplayFunc)pgm_read_ptr(&(menus[currentMode].displayFn)))();
  if (numMenuItems > 0) {
    redrawMenuCursor();
  }
}

void loop() {
  processButtonInputs();
  if (!processButtonInputs()) {
    system_sleep();
  }
}

bool processButtonInputs(void) {
  bool mainButtonIsDown = digitalRead(MAIN_BUTTON) == LOW;
  if (mainButtonIsDown) {
    if (mainButtonWasDown) {
      long buttonDownDuration = millis() - buttonDownTime;
      if (buttonDownDuration >= LONG_PRESS_REPEAT) {
        buttonDownTime = millis();
        longPress();
        longPressActioned = true;
      }
    } else {
      mainButtonWasDown = true;
      buttonDownTime = millis();
    }
  } else {
    if (mainButtonWasDown && !longPressActioned) {
      long buttonDownDuration = millis() - buttonDownTime;
      if (buttonDownDuration < LONG_PRESS_REPEAT) {
        shortPress();
      } else {
        longPress();
      }
    }
    mainButtonWasDown = false;
    longPressActioned = false;
  }
  bool enterButtonIsDown = digitalRead(ENTER_BUTTON) == LOW;
  if (enterButtonIsDown) {
    enterButtonWasDown = true;
  } else {
    if (enterButtonWasDown) {
      enterButtonWasDown = false;
      longPress();
    }
  }
  return mainButtonIsDown || enterButtonIsDown;
}

static void shortPress() {
  if (currentMode == 0) {
    nextScreenAction();
  } else {
    nextMenuItemAction();
  }
  displayScreenForMode();
}

static void longPress() {
  if (currentMode == 0) {
    if (currentScreen > 0) {
      showMenuAction();
    } else {
      nextScreenAction();
    }
  } else {
    invokeMenuItemAction();
  }
  displayScreenForMode();
}

static void nextMenuItemAction(void) {
  menuLine++;
  if (menuLine > numMenuItems) menuLine = 0;
}

static void invokeMenuItemAction(void) {
  if (menuLine == 0) {
    if (eepromOk) {
      currentMode = pgm_read_byte(&(menus[currentMode].exitMode));
    }
  } else {
    ((ActionFunc)pgm_read_ptr(&(menuItems[menuLine - 1].actionFn)))();
  }
}

void drawScreen(void) {
  oled.clear();
  currentScreenItem = 0;
  currentItemChanged();
  do {
    displayItem();
    nextItemAction();
  } while (currentScreenItem != 0);
}

static void displayItem(void) {
  if (itemLength == 0) return;
  itemFont = (const DCfont *)pgm_read_ptr(&fonts[itemFontNum]);
  oled.setFont(itemFont);
  if (itemDoubleSize) {
    for (uint8_t pageLine = 0; pageLine < itemFont->height * 2; pageLine++) {
      oled.setCursor(itemLocationX, itemLocationY + pageLine);
      oled.startData();
      for (uint8_t offset = 0; offset < itemLength; offset++) {
        uint8_t c = EEPROM.read(itemAddress + offset);
        c = limitToFont(c);
        uint16_t bitmapOffset = itemFont->width * (itemFont->height * (c - itemFont->first) + (pageLine >> 1));
        uint8_t * cPtr = &(itemFont->bitmap[bitmapOffset]);
        uint8_t i = itemFont->width;
        do {
          uint8_t b = pgm_read_byte(cPtr++);
          if ((pageLine & 0x01) == 0x01) {
            b = b >> 4;
          }
          b = ((b & 8) << 3) | ((b & 4) << 2) | ((b & 2) << 1) | (b & 1);
          b += b << 1;
          oled.sendData(b);
          oled.sendData(b);
        }
        while (--i);
      }
      oled.endData();
    }
  } else {
    outputCurrentTextAt(itemLocationX, itemLocationY, 0, itemLength);
  }
}

static void nextScreenAction() {
  currentScreen++;
  if (currentScreen >= NUMBER_OF_SCREENS) currentScreen = 0;
  EEPROM.write(NAMEBADGE_CURRENT_SCREEN_ADDRESS, currentScreen);
}

static void showMenuAction(void) {
  switchToMode(ITEM_SELECTION_MODE);
}

static void displayMenu() { 
  if (currentMode != lastMode) {
    oled.clear();
    lastMode = currentMode;
  }
  oled.setCursor(0,1);
  oled.fillLength(0x18, 120);

  for (uint8_t l = 0; l < numMenuItems; l++) {
    redrawMenuLine(l);
  }
  oled.setCursor(0,7);
  oled.fillLength(0x18, 120);
}

static void redrawMenuLine(uint8_t l) {
  oled.setFont(FONT6X8);
  oled.setCursor(0, 2 + l);
  PGM_P namePtr = pgm_read_word(&(menuItems[l].name));
  if (namePtr != NULL) {
    oled.print(FPSTR(pgm_read_word(&(menuItems[l].name))));
  }
}

static void redrawMenuCursor(void) {
  for (uint8_t p = 0; p < 8; p++) {
    oled.setCursor(120,p);
    oled.fillLength(0x00,8);
  }
  oled.setFont(&symbolFont);
  if (menuLine == 0) {
    oled.setCursor(120,0);
    oled.write(CLOSE_MENU_SYMBOL);
  } else {
    oled.setCursor(120,menuLine + 1);
    oled.write(ACTIVE_MENU_SYMBOL);
  }
}

static void switchToMode(uint16_t m) {
  currentMode = m;
  menuLine = 0;
  oled.clear();
  displayScreenForMode();
}

static uint8_t getCurrentItemAddress(void) {
  return NAMEBADGE_ITEM_BASE_ADDRESS + currentScreen * ITEMS_PER_SCREEN * BYTES_PER_ITEM + currentScreenItem * BYTES_PER_ITEM;
}

static void currentItemChanged(void) {
  currentScreenItem &= 0x0F;
  uint8_t offset = getCurrentItemAddress();
  uint8_t nextLocation = EEPROM.read(offset++);
  uint8_t nextOffset = EEPROM.read(offset++);
  uint8_t nextDetail = EEPROM.read(offset++);
  decodeItem(nextLocation, nextOffset, nextDetail);
}

static void decodeItem(uint8_t nextLocation, uint8_t nextOffset, uint8_t nextDetail) {
  itemLocationX = nextLocation & 0x78;
  itemLocationY = nextLocation & 0x07;
  itemOffset = nextOffset;
  itemAddress = NAMEBADGE_TEXT_BASE_ADDRESS + itemOffset;
  itemDoubleSize = (nextDetail & 0x80);// == 0x80;
  itemFontNum = (nextDetail & 0x60) >> 5;
  itemLength = nextDetail & 0x1F;
}

static void saveItem(void) {
  uint8_t offset = getCurrentItemAddress();
  EEPROM.write(offset++, itemLocationX | itemLocationY);
  EEPROM.write(offset++, itemOffset);
  EEPROM.write(offset++, (itemDoubleSize/* ? 0x80 : 0x00*/) | (itemFontNum << 5) | itemLength);
  itemAddress = NAMEBADGE_TEXT_BASE_ADDRESS + itemOffset;
}

static void outputCurrentTextAt(uint8_t x, uint8_t y, uint8_t initialOffset, uint8_t displayedLength) {
  oled.setCursor(x,y);
  for (uint8_t offset = initialOffset; (offset < itemLength) && ((offset - initialOffset) < displayedLength); offset++) {
    uint8_t c = EEPROM.read(itemAddress + offset);
    c = limitToFont(c);
    oled.write(c);
  }
}

static void preview() {
  displayItem();
  saveItem();
  delay(400);
  oled.clear();
}



void drawItemMenu(void) {
  displayMenu();
  oled.setFont(FONT6X8);
  oled.setCursor(0,0);
  oled.print(FPSTR(ITEM_NAME));
  if (currentScreenItem < 9) {
      oled.write(' ');
  }
  oled.print(currentScreenItem + 1);
  oled.write(',');
  outputCurrentTextAt(48, 0, 0, 12);
  for (uint8_t filler = itemLength; filler <= 12; filler++) {
    oled.write(' ');
  }
}

void nextItemAction(void) {
  currentScreenItem++;
  currentItemChanged();
}
void prevItemAction(void) {
  currentScreenItem--;
  currentItemChanged();
}
void editItemAction(void) {
  switchToMode(EDIT_ITEM_MODE);
}
void alterTextAction(void) {
  switchToMode(TEXT_EDIT_OPTIONS_MODE);
}
void settingsAction(void) {
  switchToMode(SETTINGS_MENU_MODE);
}



void changeLocationAction(void) {
  switchToMode(CHANGE_LOCATION_MODE);
}
void changeFontAction(void) {
  itemFontNum++;
  itemFontNum &= 3;
  preview();
}
void changeSizeAction(void) {
  itemDoubleSize ^= 0x80; //!itemDoubleSize;
  preview();
}
void selectTextAction(void) {
  switchToMode(SELECT_TEXT_MODE);
}



void locationLeftAction(void) {
  if (itemLocationX > 0) {
    itemLocationX -= 8;
    preview();
  }
}
void locationRightAction(void) {
  if (itemLocationX < 120) {
    itemLocationX += 8;
    preview();
  }
}
void locationUpAction(void) {
  if (itemLocationY > 0) {
    itemLocationY--;
    preview();
  }
}
void locationDownAction(void) {
  if (itemLocationY < 7) {
    itemLocationY++;
    preview();
  }
}

void drawSelectTextMenu(void) {
  drawItemMenu();
  showTextSelection(0, itemLength > 0 ? itemLength - 1 : 0);
}
void selectTextLeftAction(void) {
  if (itemOffset > 16) {
    itemOffset--;
    saveItem();
  }
}
void selectTextRightAction(void) {
  if (itemOffset < 256 - itemLength) {
    itemOffset++;
    saveItem();
  }
}
void selectTextLongerAction(void) {
  if ((itemLength < 31) && (itemOffset < 256 - itemLength)) {
    itemLength++;
    saveItem();
  }
}
void selectTextShorterAction(void) {
  if (itemLength > 0) {
    itemLength--;
    saveItem();
  }
}



void drawTextEditOptionsMenu(void) {
  drawItemMenu();
  showTextSelection(currentItemCharacterPos, currentItemCharacterPos);
}
static void showTextSelection(uint8_t startPos, uint8_t endPos) {
  oled.setFont(FONT6X8);
  outputCurrentTextAt(12, 6, 0, itemLength); // todo scroll
  oled.setCursor(8,7);
  oled.fillLength(0x18, 112);
  oled.setFont(&symbolFont);
  oled.setCursor(11 + 6 * startPos, 7);
  oled.write(SELECTED_LETTER_SYMBOL);
  oled.setCursor(11 + 6 * endPos, 7);
  oled.write(SELECTED_LETTER_SYMBOL);
}
void textEditLeftAction(void) {
  if (currentItemCharacterPos > 0) {
    currentItemCharacterPos--;
    currentLetter = EEPROM.read(itemAddress + currentItemCharacterPos);
  }
}
void textEditRightAction(void) {
  if (currentItemCharacterPos < itemLength - 1) {
    currentItemCharacterPos++;
    currentLetter = EEPROM.read(itemAddress + currentItemCharacterPos);
  }
}
void textEditAction(void) {
  switchToMode(TEXT_EDIT_MODE);
}
void textEditInsertDeleteAction(void){
  switchToMode(TEXT_INSERT_DELETE_MODE);
}

static uint8_t limitToFont(uint8_t c) {
  if (c > itemFont->last) {
    c = itemFont->first;
  }
  if (c < itemFont->first) {
    c = itemFont->last;
  }
  return c;
}

void textEditNextAction(void) {
  currentLetter++;
  updateCurrentLetter();
}
void textEditPrevAction(void) {
  currentLetter--;
  updateCurrentLetter();
}
void textEditChangeCaseAction(void) {
  if ((currentLetter >= 'A') && (currentLetter <= 'Z')) {
    currentLetter += ('a' - 'A');
    updateCurrentLetter();
  } else if ((currentLetter >= 'a') && (currentLetter <= 'z')) {
    currentLetter -= ('a' - 'A');
    updateCurrentLetter();
  }
}
static void updateCurrentLetter(void) {
  currentLetter = limitToFont(currentLetter);
  EEPROM.write(itemAddress + currentItemCharacterPos, currentLetter);
}

void drawTextInsertDeleteMenu(void) {
  drawItemMenu();
  showTextSelection(currentItemCharacterPos, currentItemCharacterPos);
}
void textInsertAction(void) {
  if (itemLength == 31) return;
  // All items that start after get shifted. All items that start before and end on or after get lengthened
  uint8_t insertPosition = itemOffset + currentItemCharacterPos;
  uint8_t s = currentScreen;
  uint8_t i = currentScreenItem;
  for (currentScreen = 0; currentScreen < NUMBER_OF_SCREENS; currentScreen++) {
    for (uint8_t item = 0; item < ITEMS_PER_SCREEN; item++) {
      currentScreenItem = item;
      currentItemChanged();
      if (itemOffset <= insertPosition) {
        if ((itemOffset + itemLength > insertPosition) && (itemLength < 31) && (itemLength > 0)) {
          itemLength++;
          saveItem();
        }
      } else {
        if (itemOffset < 255) {
          itemOffset++;
          saveItem();
        }
        if ((uint16_t)itemOffset + itemLength > 256) {
          itemLength--;
          saveItem();
        }
      }
    }
  }
  // All the characters get shifted.
  for (uint16_t p = 511; p >= NAMEBADGE_TEXT_BASE_ADDRESS + (uint16_t)insertPosition + 1; p--) {
    uint8_t c = EEPROM.read(p - 1);
    EEPROM.write(p, c);
  }
  currentScreen = s;
  currentScreenItem = i;
  currentItemChanged();
}
void textDeleteAction(void) {
  // All items that start after get shifted. All items that start before and end on or after get shortened
  if (itemLength == 0) return;
  uint8_t insertPosition = itemOffset + currentItemCharacterPos;
  uint8_t s = currentScreen;
  uint8_t i = currentScreenItem;
  for (currentScreen = 0; currentScreen < NUMBER_OF_SCREENS; currentScreen++) {
    for (uint8_t item = 0; item < ITEMS_PER_SCREEN; item++) {
      currentScreenItem = item;
      currentItemChanged();
      if (itemOffset <= insertPosition) {
        if (itemOffset + itemLength > insertPosition) {
          itemLength--;
          saveItem();
        }
      } else {
        itemOffset--;
        saveItem();
      }
    }
  }
  // All the characters get shifted.
  for (uint16_t p = NAMEBADGE_TEXT_BASE_ADDRESS + insertPosition; p < 511; p++) {
    uint8_t c = EEPROM.read(p + 1);
    EEPROM.write(p, c);
  }
  currentScreen = s;
  currentScreenItem = i;
  currentItemChanged();
}



void drawSettingsMenu(void) {
  displayMenu();
  oled.setFont(FONT6X8);
  oled.setCursor(0,0);
  oled.print(FPSTR(SETTINGS_NAME));
  oled.write(' ');
  outputVoltage();
}
void settingsIncreaseContractAction(void) {
  // It can wrap to 0
  currentContrast++;
  setContrast();
}
void settingsDecreaseContractAction(void) {
  // It can wrap to 255
  currentContrast--;
  setContrast();
}
static void setContrast(void) {
  oled.setContrast(currentContrast);
  if (eepromOk) {
    EEPROM.write(NAMEBADGE_CONTRAST_ADDRESS, currentContrast);
  }
}
void settingsResetAction(void) {
  // EEPROM Header
  for (uint16_t offset = 0; offset < sizeof(header); offset++) {
    EEPROM.write(offset, pgm_read_byte(&header[offset]));
  }
  // Unused
  for (uint16_t address = sizeof(header); address < 256; address++) {
    EEPROM.write(address, 0);
  }

  // Item Definitions
  for (uint16_t offset = 0; offset < sizeof(screenItems0); offset++) {
    EEPROM.write(NAMEBADGE_ITEM_BASE_ADDRESS + offset, pgm_read_byte(&screenItems0[offset]));
  }

  for (uint16_t offset = 0; offset < sizeof(screenItems1); offset++) {
    uint8_t itemByte = pgm_read_byte(&screenItems1[offset]);
    EEPROM.write(NAMEBADGE_ITEM_BASE_ADDRESS + ITEMS_PER_SCREEN * BYTES_PER_ITEM + offset, itemByte);
    EEPROM.write(NAMEBADGE_ITEM_BASE_ADDRESS + ITEMS_PER_SCREEN * BYTES_PER_ITEM * 2 + offset, itemByte);
    EEPROM.write(NAMEBADGE_ITEM_BASE_ADDRESS + ITEMS_PER_SCREEN * BYTES_PER_ITEM * 3 + offset, itemByte);
    EEPROM.write(NAMEBADGE_ITEM_BASE_ADDRESS + ITEMS_PER_SCREEN * BYTES_PER_ITEM * 4 + offset, itemByte);
  }
  // Item Contents
  for (uint16_t offset = 0; offset < sizeof(textContents); offset++) {
    EEPROM.write(NAMEBADGE_TEXT_BASE_ADDRESS + offset, pgm_read_byte(&textContents[offset]));
  }
  for (uint16_t offset = sizeof(textContents); offset < 256; offset++) {
    EEPROM.write(NAMEBADGE_TEXT_BASE_ADDRESS + offset, ' ');
  }
  eepromOk = true;
  currentScreen = 0;
  switchToMode(DRAW_SCREEN_MODE);
}

static void outputVoltage(void) {
  uint16_t result = readADC();
  result = 1126400L / result; // Calculate Vcc (in mV); 1.1*1024*1000
  // A very rough estimate saves 54 bytes:
  //result = 6100 - 8 * result;
  oled.print(result);
  oled.print(F(" mV"));
}

static uint16_t readADC() {
  uint8_t low,high;
  ADCSRA = ADCSRA | 1<<ADSC;     // Start
  do {} while (ADCSRA & 1<<ADSC); // Wait while conversion in progress
  low = ADCL;
  high = ADCH;
  return ((uint16_t)high<<8 | low);
}

void system_sleep() {
  cbi(ADCSRA,ADEN);                    // switch Analog to Digitalconverter OFF
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here
  sleep_enable();
  sleep_mode();                        // System actually sleeps here
  sleep_disable();                     // System continues execution here when watchdog timed out 
  sbi(ADCSRA,ADEN);                    // switch Analog to Digitalconverter ON  
}
