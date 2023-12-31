//AUTOGENERATED FILE FROM png2asset
#ifndef METASPRITE_NPCGuy_H
#define METASPRITE_NPCGuy_H

#include <stdint.h>
#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#define NPCGuy_TILE_ORIGIN 0
#define NPCGuy_TILE_W 8
#define NPCGuy_TILE_H 8
#define NPCGuy_WIDTH 16
#define NPCGuy_HEIGHT 16
#define NPCGuy_TILE_COUNT 29
#define NPCGuy_PALETTE_COUNT 1
#define NPCGuy_COLORS_PER_PALETTE 4
#define NPCGuy_TOTAL_COLORS 4
#define NPCGuy_PIVOT_X 8
#define NPCGuy_PIVOT_Y 8
#define NPCGuy_PIVOT_W 0
#define NPCGuy_PIVOT_H 0

BANKREF_EXTERN(NPCGuy)

extern const palette_color_t NPCGuy_palettes[4];
extern const uint8_t NPCGuy_tiles[464];

extern const metasprite_t* const NPCGuy_metasprites[12];

#endif
