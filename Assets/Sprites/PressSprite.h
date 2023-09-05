//AUTOGENERATED FILE FROM png2asset
#ifndef METASPRITE_PressSprite_H
#define METASPRITE_PressSprite_H

#include <stdint.h>
#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#define PressSprite_TILE_ORIGIN 0
#define PressSprite_TILE_W 8
#define PressSprite_TILE_H 8
#define PressSprite_WIDTH 40
#define PressSprite_HEIGHT 16
#define PressSprite_TILE_COUNT 10
#define PressSprite_PALETTE_COUNT 1
#define PressSprite_COLORS_PER_PALETTE 4
#define PressSprite_TOTAL_COLORS 4
#define PressSprite_PIVOT_X 20
#define PressSprite_PIVOT_Y 8
#define PressSprite_PIVOT_W 0
#define PressSprite_PIVOT_H 0

BANKREF_EXTERN(PressSprite)

extern const palette_color_t PressSprite_palettes[4];
extern const uint8_t PressSprite_tiles[160];

extern const metasprite_t* const PressSprite_metasprites[1];

#endif