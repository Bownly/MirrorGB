#include <gb/gb.h>
#include <stdio.h>
#include <string.h>

#include "../Assets/Tiles/HouseTiles.h"
#include "../Assets/Tiles/HouseMTiles.h"
#include "../Assets/Tiles/LabRTiles.h"
#include "../Assets/Tiles/LabMTiles.h"
#include "../Database/MetatilesData.h"

#define TILES_BKG_INDEX 0x00U
#define MAP_BANK 4U

extern UINT8 metaTiles[256U][4U];
UINT8 nextBank;

void loadMapTileData(UINT8 roomId)
{
    nextBank = CURRENT_BANK;

    SWITCH_ROM(MAP_BANK);

    UINT8 tilesetId;

    switch (roomId)
    {
        default:
        case 0U:
            tilesetId = 0U;
            set_bkg_data(TILES_BKG_INDEX, LabRTiles_tileset_size, LabRTiles_tileset);
            break;
        case 1U:
            tilesetId = 1U;
            set_bkg_data(TILES_BKG_INDEX, LabMTiles_tileset_size, LabMTiles_tileset);
            break;
        case 2U:
        case 4U:
        case 6U:
            tilesetId = 2U;
            set_bkg_data(TILES_BKG_INDEX, HouseTiles_tileset_size, HouseTiles_tileset);
            break;
        case 3U:
        case 5U:
        case 7U:
            tilesetId = 3U;
            set_bkg_data(TILES_BKG_INDEX, HouseMTiles_tileset_size, HouseMTiles_tileset);
            break;
    }
    memcpy(metaTiles, metatilesDex[tilesetId], 1024U);

    SWITCH_ROM(nextBank);
}
