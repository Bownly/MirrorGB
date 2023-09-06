#include <gb/gb.h>
#include <stdio.h>
#include <string.h>

#include "../Database/RoomData.h"
#include "../Objects/RoomObject.h"

extern UINT8 i;  // Used mostly for loops
extern UINT8 j;  // Used mostly for loops
extern UINT8 (*playGridPtr)[32U][32U];
extern UINT8 playGrid[32U][32U];
extern UINT8 playGridM[32U][32U];

#define OWTILES_BKG_INDEX  0x60U
#define MAP_BANK 3U

static UINT8 nextBank;
static UINT8 returnVal;

void loadMapDataFromDatabase(UINT8 (*playGridPtr)[32U], UINT8 mapId, UINT8 w, UINT8 h)
{
    nextBank = CURRENT_BANK;

    SWITCH_ROM(MAP_BANK);

    UINT16 c = 0U;
    for (j = 0U; j != h; j++)
    {
        memcpy(playGridPtr[j], roomDex[mapId].map + c, w);
        c += w;
    }

    SWITCH_ROM(nextBank);
}

UINT8 getOwMapHeight(UINT8 mapId)
{
    nextBank = CURRENT_BANK;
    SWITCH_ROM(MAP_BANK);
    returnVal;
    returnVal = roomDex[mapId].h;
    SWITCH_ROM(nextBank);
    return returnVal;
}

UINT8 getOwMapWidth(UINT8 mapId)
{   
    nextBank = CURRENT_BANK;
    SWITCH_ROM(MAP_BANK);
    returnVal;
    returnVal = roomDex[mapId].w;
    SWITCH_ROM(nextBank);
    return returnVal;
}

