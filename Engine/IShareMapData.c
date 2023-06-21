#include <gb/gb.h>
#include <stdio.h>
#include <string.h>

#include "../Database/LevelData.h"
#include "../Objects/LevelObject.h"

extern UINT8 i;  // Used mostly for loops
extern UINT8 j;  // Used mostly for loops
extern UINT8 playGrid[32U][32U];

#define OWTILES_BKG_INDEX  0x60U

#define MAP_BANK 3U

void loadMapDataFromDatabase(UINT8 mapId, UINT8 w, UINT8 h)
{
    UINT8 nextBank = CURRENT_BANK;

    SWITCH_ROM(MAP_BANK);

    UINT16 c = 0U;
    for (j = 0U; j != h; j++)
    {
        memcpy(playGrid[j], levelDex[mapId].map + c, w);
        c += w;
    }
    SWITCH_ROM(nextBank);
}

// UINT8 loadTileDataForMap(UINT8 mapId)
// {
//     UINT8 nextBank = CURRENT_BANK;
//     UINT8 returnVal = 6U;

//     if (mapId >= FIRST_WORLD_MAP)  // World map maps
//     {
//         mapId = worldMapDistribution[mapId - OWMAP_WORLDMAP_NW];
//         SWITCH_ROM(14U);
//         switch (mapId)
//         {
//             case 0U:
//                 set_bkg_data(OWTILES_BKG_INDEX, 124U, owDBZTiles);
//                 returnVal = 11U;
//                 break;
//             case 1U:
//                 set_bkg_data(OWTILES_BKG_INDEX, 124U, owDQTiles);
//                 returnVal = 11U;
//                 break;
//             case 2U:
//                 set_bkg_data(OWTILES_BKG_INDEX, 124U, owDQMTiles);
//                 returnVal = 11U;
//                 break;
//             case 3U:
//             case 4U:
//                 set_bkg_data(OWTILES_BKG_INDEX, 124U, owFFLTiles);
//                 returnVal = 11U;
//                 break;
//             case 5U:
//                 set_bkg_data(OWTILES_BKG_INDEX, 124U, owGLTiles);
//                 returnVal = 11U;
//                 break;
//             case 7U:
//                 set_bkg_data(OWTILES_BKG_INDEX, 124U, owSMTiles);
//                 returnVal = 11U;
//                 break;
//             case 6U:
//                 set_bkg_data(OWTILES_BKG_INDEX, 124U, owGQTiles);
//                 returnVal = 11U;
//                 break;
//             default:
//             case 8U:
//                 set_bkg_data(OWTILES_BKG_INDEX, 124U, owZ2Tiles);
//                 returnVal = 11U;
//                 break;
//         }
//     }
//     else if (mapId > 20U)  // Oasis rooms
//     {
//         SWITCH_ROM(2U);
//         set_bkg_data(OWTILES_BKG_INDEX, 124U, owOasisTiles);
//         returnVal = 10U;
//     }
//     else if (mapId > 10U)  // Rocks rooms
//     {
//         SWITCH_ROM(2U);
//         set_bkg_data(OWTILES_BKG_INDEX, 124U, owRocksTiles);
//         returnVal = 3U;
//     }
//     else if (mapId > 0U)  // Ningami rooms
//     {
//         SWITCH_ROM(2U);
//         set_bkg_data(OWTILES_BKG_INDEX, 124U, forestTiles);
//         returnVal = 3U;
//     }
//     else
//     {
//         SWITCH_ROM(2U);
//         set_bkg_data(OWTILES_BKG_INDEX, 124U, owLibraryTiles);
//         returnVal = 3U;
//     }
//     SWITCH_ROM(nextBank);

//     return returnVal;
// }

UINT8 getOwMapHeight(UINT8 mapId)
{
    UINT8 nextBank = CURRENT_BANK;
    SWITCH_ROM(MAP_BANK);
    UINT8 returnVal;
    returnVal = levelDex[mapId].h;
    SWITCH_ROM(nextBank);
    return returnVal;
}

UINT8 getOwMapWidth(UINT8 mapId)
{   
    UINT8 nextBank = CURRENT_BANK;
    SWITCH_ROM(MAP_BANK);
    UINT8 returnVal;
    returnVal = levelDex[mapId].w;
    SWITCH_ROM(nextBank);
    return returnVal;
}

