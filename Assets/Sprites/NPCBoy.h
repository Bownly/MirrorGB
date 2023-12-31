//AUTOGENERATED FILE FROM png2asset
#ifndef METASPRITE_NPCBoy_H
#define METASPRITE_NPCBoy_H

#include <stdint.h>
#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#define NPCBoy_TILE_ORIGIN 0
#define NPCBoy_TILE_W 8
#define NPCBoy_TILE_H 8
#define NPCBoy_WIDTH 16
#define NPCBoy_HEIGHT 16
#define NPCBoy_TILE_COUNT 24
#define NPCBoy_PALETTE_COUNT 1
#define NPCBoy_COLORS_PER_PALETTE 4
#define NPCBoy_TOTAL_COLORS 4
#define NPCBoy_PIVOT_X 8
#define NPCBoy_PIVOT_Y 8
#define NPCBoy_PIVOT_W 0
#define NPCBoy_PIVOT_H 0

BANKREF_EXTERN(NPCBoy)

extern const palette_color_t NPCBoy_palettes[4];
extern const uint8_t NPCBoy_tiles[384];

extern const metasprite_t* const NPCBoy_metasprites[12];

#endif
