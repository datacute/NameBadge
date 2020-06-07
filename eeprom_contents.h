/*
EEPROM CONTENTS

Location (HEX)
000:  4 bytes - magic EEPROM content identifier #1DBAD6E0 (ID Badge 0) (We could use the last bits to indicate how many buttons are available?)
004:  1 byte - current screen number to be redisplayed at power-on.
005:  1 byte - current contrast
006:  10 bytes unused

010:  240 bytes - 5 screens of 16 items, 3 bytes per item:
        1 byte item location: 1 bit unused, 4 bits for x 0-127 (16 positions, multiples of 8), 3 bits for y 0-7
        1 byte text offset
        1 byte: 1 bit for double size, 2 bits for font, 5 bits selecting data item length

100: 256 bytes of item text content.

*/

/*
 * The Magic Number
 * 
 * If this does not match the first four bytes of the EEPROM,
 * then the EEPROM does not contain name badge information.
 * The only action available is to reset the EEPROM.
 * This should also match the first four bytes written to the EEPROM,
 * found in the 'header' array below.
 * 
 * 1DBAD6E0 was chosen as being close to "ID BADGE"
 * The 0 on the end allows for future versions.
 */
#define NAMEBADGE_MAGIC 0x1DBAD6E0
#define NAMEBADGE_MAGIC0 0x1D
#define NAMEBADGE_MAGIC1 0xBA
#define NAMEBADGE_MAGIC2 0xD6
#define NAMEBADGE_MAGIC3 0xE0

#define NAMEBADGE_MAGIC_ADDRESS 0
#define NAMEBADGE_CURRENT_SCREEN_ADDRESS 4
#define NAMEBADGE_CONTRAST_ADDRESS 5
#define NAMEBADGE_ITEM_BASE_ADDRESS 16
#define NAMEBADGE_TEXT_BASE_ADDRESS 256

#define ITEMS_PER_SCREEN 16
#define BYTES_PER_ITEM 3
#define NUMBER_OF_SCREENS 5

const byte header [] PROGMEM = {
  NAMEBADGE_MAGIC0, NAMEBADGE_MAGIC1, NAMEBADGE_MAGIC2, NAMEBADGE_MAGIC3, 
  0x01, // current screen
  0x10  // contrast
};

// The first screen shows the QR Code, and is not editable
const byte screenItems0 [] PROGMEM = {
// X times 8  Y , offset,  Dbl   font   length
  (0 << 3) | (0),  0,      0x80 | 0x60 | 4,
  (0 << 3) | (2),  4,      0x80 | 0x60 | 4,
  (0 << 3) | (4),  8,      0x80 | 0x60 | 4,
  (0 << 3) | (6),  12,     0x80 | 0x60 | 4
};

const byte screenItems1 [] PROGMEM = {
// X times 8  Y , offset,  Dbl   font   length
  (0 << 3) | (0),  16,    0x80 | 0x20 | 8,
  (0 << 3) | (5),  24,    0x80 | 0x00 | 10
};

#define RESERVED_TEXT 16

const char textContents [] PROGMEM = {
  // 0
  'A','B','C','D',
  // 4
  'E','F','G','H',
  // 8
  'I','J','K','L',
  // 12
  'M','N','O','P',

  // 16
  'D','a','t','a','c','u','t','e',
  // 24
  'N','a','m','e',' ','B','a','d','g','e',
};
