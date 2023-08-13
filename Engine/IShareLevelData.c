#include <gb/gb.h>
#include <stdio.h>
#include <string.h>

#include "../Database/LevelData.h"
#include "../Objects/LevelObject.h"


extern UINT8 handyDandyString[19U];

#define DATA_BANK 4U

static UINT8 nextBank;


void loadLevelNPCSpeciesList(UINT8 levelId)
{
    nextBank = CURRENT_BANK;
    SWITCH_ROM(DATA_BANK);
    memcpy(handyDandyString, levelDex[levelId].npcSpecies, 8U);
    SWITCH_ROM(nextBank);
}
