/*
 * QR Code for the Tiny4kOLED github page
 * 
 * These could be replaced with your own QR code, or your own brand or logo
 * 
 * The 16 characters of the font are 8x8 pixel graphics
 * designed to be joined together:
 * 
 * ABCD
 * EFGH
 * IJKL
 * MNOP
 * 
 * When shown double-sized they take up 64x64 rows
 */

const uint8_t qrCodeFontData [128] PROGMEM = {
0x00,0xFE,0x82,0xBA,0xBA,0xBA,0x82,0xFE, // A
0x00,0xBA,0x72,0xA0,0x38,0xC8,0x48,0xD0, // B
0x76,0xF2,0x60,0xF6,0x40,0xBA,0x00,0xFE, // C
0x82,0xBA,0xBA,0xBA,0x82,0xFE,0x00,0x00, // D

0x00,0x26,0xA2,0x1A,0xB6,0xAC,0x68,0xAA, // E
0x4C,0xF2,0xE5,0xC0,0x71,0x90,0x52,0xCB, // F
0x38,0x41,0xC3,0xD8,0x43,0x3C,0xDE,0x80, // G
0x98,0xAA,0x4E,0xC2,0x1C,0x02,0x00,0x00, // H

0x00,0x8A,0xA4,0xAC,0xA7,0xA9,0xB6,0xAA, // I
0x1C,0x59,0xF5,0x2C,0xAA,0xFD,0xE5,0x40, // J
0x90,0x7E,0x1A,0x22,0xFD,0xE4,0x29,0xB1, // K
0x31,0xE5,0x2C,0x2A,0xC7,0x35,0x00,0x00, // L

0x00,0x3F,0x20,0x2E,0x2E,0x2E,0x20,0x3F, // M
0x00,0x3C,0x2F,0x1A,0x1C,0x26,0x08,0x36, // N
0x0B,0x1A,0x27,0x2C,0x12,0x33,0x06,0x26, // O
0x0A,0x07,0x3A,0x1F,0x26,0x1A,0x00,0x00  // P
};

const DCfont qrCodeFont = {
  (uint8_t *)qrCodeFontData,
  8, // character width in pixels
  1, // character height in pages (8 pixels)
  65,80 // ASCII extents
  };
