//AUTOGENERATED FILE FROM png2asset
#ifndef METASPRITE_MC_H
#define METASPRITE_MC_H

#include <stdint.h>
#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#define MC_TILE_ORIGIN 0
#define MC_TILE_W 8
#define MC_TILE_H 8
#define MC_WIDTH 16
#define MC_HEIGHT 16
#define MC_TILE_COUNT 19
#define MC_PALETTE_COUNT 1
#define MC_COLORS_PER_PALETTE 4
#define MC_TOTAL_COLORS 4
#define MC_PIVOT_X 8
#define MC_PIVOT_Y 8
#define MC_PIVOT_W 0
#define MC_PIVOT_H 0

BANKREF_EXTERN(MC)

extern const palette_color_t MC_palettes[4];
extern const uint8_t MC_tiles[304];

extern const metasprite_t* const MC_metasprites[9];

#endif
