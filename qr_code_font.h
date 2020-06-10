/*
 * QR Code for the Name Badge github page
 * 
 * This could be replaced with your own QR code, or your own brand or logo
 * 
 * The single character of this font, the capital A, is a 32x32 pixel image.
 * 
 * When shown double-sized, it takes up 64 colums by 64 rows
 */

const uint8_t qrCodeFontData [128] PROGMEM = {
0x00,0xFC,0x04,0x74,0x74,0x74,0x04,0xFC, 0x00,0xBC,0xF0,0xE0,0x08,0x78,0x0C,0x1C, 0x08,0x24,0x88,0xD4,0x10,0x98,0x00,0xFC, 0x04,0x74,0x74,0x74,0x04,0xFC,0x00,0x00,
0x00,0x85,0x6D,0xD9,0xA9,0x1D,0xED,0x55, 0xF8,0x79,0x30,0x97,0x42,0xA5,0x4E,0x69, 0x0A,0xFF,0x54,0x91,0xEE,0x61,0x60,0x19, 0xFD,0x91,0x75,0xDD,0x45,0x15,0x00,0x00,
0x00,0x4E,0x45,0x38,0x75,0x4E,0x63,0x55, 0x23,0x84,0x58,0xE2,0x43,0xA5,0x4F,0x69, 0x19,0x9D,0x02,0x15,0x6E,0xF3,0x4A,0x51, 0x4C,0xD9,0xDD,0xBD,0x3F,0x10,0x00,0x00,
0x00,0x7F,0x41,0x5D,0x5D,0x5D,0x41,0x7F, 0x00,0x66,0x15,0x18,0x43,0x25,0x4F,0x69, 0x11,0x15,0x72,0x51,0x7D,0x47,0x1C,0x75, 0x4C,0x67,0x2A,0x3B,0x5A,0x15,0x00,0x00
};

const DCfont qrCodeFont = {
  (uint8_t *)qrCodeFontData,
  32, // character width in pixels
  4, // character height in pages (8 pixels)
  65,65 // ASCII extents
  };
