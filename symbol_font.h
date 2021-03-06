/******************
 * 8*8 symbol font
 * 
 * Borders, menu icons, could be extended to include twitter/facebook/other symbols
 */

#define CLOSE_MENU_SYMBOL '0'
#define ACTIVE_MENU_SYMBOL '6'
#define SELECTED_LETTER_SYMBOL '9'
#define WORKING_SYMBOL ' '

const uint8_t symbolFontData [] PROGMEM = {

  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // space
  0x88,0x22,0x44,0x11,0x88,0x22,0x44,0x11, // ! ░
  0xAA,0x55,0xAA,0x55,0xAA,0x55,0xAA,0x55, // " ▒
  0x77,0xDD,0xBB,0xEE,0x77,0xDD,0xBB,0xEE, // # ▓
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, // $ █
  0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00, // % │
  0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18, // & ─
  0x18,0x18,0x18,0xFF,0xFF,0x18,0x18,0x18, // ' ┼
  0x18,0x18,0x18,0xF8,0xF8,0x00,0x00,0x00, // ( ┐
  0x00,0x00,0x00,0x1F,0x1F,0x18,0x18,0x18, // ) └
  0x18,0x18,0x18,0x1F,0x1F,0x00,0x00,0x00, // * ┘
  0x00,0x00,0x00,0xF8,0xF8,0x18,0x18,0x18, // + ┌
  0x18,0x18,0x18,0xFF,0xFF,0x00,0x00,0x00, // , ┤
  0x18,0x18,0x18,0x1F,0x1F,0x18,0x18,0x18, // - ┴
  0x18,0x18,0x18,0xF8,0xF8,0x18,0x18,0x18, // . ┬
  0x00,0x00,0x00,0xFF,0xFF,0x18,0x18,0x18, // / ├

  0x42,0xE7,0x76,0x1C,0x38,0x6E,0xE7,0x42, // 0 X
  0xFF,0x81,0x99,0xB9,0xB1,0x99,0x8D,0xF6, // 1 tick
  0x3C,0x66,0xC3,0x99,0x91,0xC3,0x66,0x3C, // 2 circle
  0x00,0x18,0x18,0x7E,0x7E,0x18,0x18,0x00, // 3 +
  0x00,0x18,0x18,0x18,0x18,0x18,0x18,0x00, // 4 -
  0x18,0x18,0x00,0x18,0x18,0x00,0x18,0x18, // 5 ...
  0x18,0x3C,0x7E,0xFF,0x5A,0x18,0x18,0x18, // 6 Left Arrow
  0x18,0x18,0x18,0x5A,0xFF,0x7E,0x3C,0x18, // 7 Right Arrow
  0x10,0x38,0x70,0xFF,0xFF,0x70,0x38,0x10, // 8 Down Arrow
  0x08,0x1C,0x0E,0xFF,0xFF,0x0E,0x1C,0x08, // 9 Up Arrow
  0x1C,0x3E,0x66,0xC4,0x42,0x22,0x1C,0x00, // : heart
};

const DCfont symbolFont = {
  (uint8_t *)symbolFontData,
  8, // character width in pixels
  1, // character height in pages (8 pixels)
  32,58 // ASCII extents
  };
