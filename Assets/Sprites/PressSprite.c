#pragma bank 1

//AUTOGENERATED FILE FROM png2asset

#include <stdint.h>
#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

BANKREF(PressSprite)

const palette_color_t PressSprite_palettes[4] = {
	RGB8(255,255,255), RGB8(106,190, 48), RGB8( 55,148,110), RGB8( 34, 32, 52)
	
};

const uint8_t PressSprite_tiles[160] = {
	0x81,0xff,0x8e,0xc1,
	0x40,0x80,0x40,0x80,
	0x40,0x80,0x80,0xc4,
	0x80,0xc4,0x84,0xc0,
	
0xc0,0xff,0x23,0xc0,
	0x80,0x40,0x00,0x40,
	0x40,0x00,0x40,0x04,
	0x44,0x00,0x04,0x40,
	
0x40,0xff,0x20,0xc0,
	0x00,0x40,0x00,0x40,
	0x40,0x00,0x46,0x00,
	0x41,0x06,0x06,0x41,
	
0x41,0xff,0x02,0xe1,
	0x80,0x41,0x81,0x00,
	0x01,0x00,0x01,0x00,
	0x8c,0x01,0x00,0x87,
	
0x83,0xff,0x05,0xc3,
	0x00,0x83,0x02,0x01,
	0x00,0x01,0x02,0x01,
	0x00,0x0b,0x01,0x0f,
	
0xa0,0xc0,0x81,0xc0,
	0x84,0xc3,0x83,0xc7,
	0xa3,0xc7,0xab,0xc7,
	0x93,0xef,0xc7,0xff,
	
0x80,0x40,0x00,0xc0,
	0x00,0xc0,0xa0,0xc0,
	0xa4,0xc0,0xaa,0xc4,
	0x91,0xee,0xc4,0xff,
	
0x01,0x40,0x00,0xc1,
	0x04,0xc3,0x02,0xc4,
	0xa0,0x40,0x20,0x40,
	0x0a,0xf1,0x60,0xff,
	
0x40,0x83,0x20,0xc1,
	0x10,0xe1,0x21,0xd0,
	0x40,0x81,0x02,0xc1,
	0x3d,0xc3,0xc3,0xff,
	
0x81,0x07,0x41,0x83,
	0x20,0xc3,0x42,0xa1,
	0x80,0x03,0x05,0x83,
	0x7b,0x87,0x83,0xff
	
};

const metasprite_t PressSprite_metasprite0[] = {
	METASPR_ITEM(-8, -20, 0, S_PAL(0)),
	METASPR_ITEM(0, 8, 1, S_PAL(0)),
	METASPR_ITEM(0, 8, 2, S_PAL(0)),
	METASPR_ITEM(0, 8, 3, S_PAL(0)),
	METASPR_ITEM(0, 8, 4, S_PAL(0)),
	METASPR_ITEM(8, -32, 5, S_PAL(0)),
	METASPR_ITEM(0, 8, 6, S_PAL(0)),
	METASPR_ITEM(0, 8, 7, S_PAL(0)),
	METASPR_ITEM(0, 8, 8, S_PAL(0)),
	METASPR_ITEM(0, 8, 9, S_PAL(0)),
	METASPR_TERM
};

const metasprite_t* const PressSprite_metasprites[1] = {
	PressSprite_metasprite0
};