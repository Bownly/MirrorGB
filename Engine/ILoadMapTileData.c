#include <gb/gb.h>
#include <stdio.h>
#include <string.h>

#include "../Assets/Tiles/HouseTiles.h"
#include "../Assets/Tiles/HouseMTiles.h"
#include "../Database/MetatilesData.h"

#define TILES_BKG_INDEX 0x00U
#define MAP_BANK 4U

extern UINT8 metaTiles[256U][4U];
UINT8 nextBank;

void loadMapTileData(UINT8 tilesetId)
{
    nextBank = CURRENT_BANK;

    SWITCH_ROM(MAP_BANK);

    switch (tilesetId)
    {
        case 0U:
            set_bkg_data(TILES_BKG_INDEX, HouseTiles_tileset_size, HouseTiles_tileset);
            break;
        case 1U:
            set_bkg_data(TILES_BKG_INDEX, HouseMTiles_tileset_size, HouseMTiles_tileset);
            break;
    }
    memcpy(metaTiles, metatilesDex[tilesetId], 1024U);

    SWITCH_ROM(nextBank);
}