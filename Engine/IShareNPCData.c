#include <gb/gb.h>
#include <stdio.h>
#include <string.h>

#include "../Database/NPCData.h"
#include "../Objects/NPCObject.h"


#define DATA_BANK 4U

static UINT8 nextBank;
extern NPCObject tempNPC;


NPCObject getNPCData(UINT8 npcId)
{
    nextBank = CURRENT_BANK;
    SWITCH_ROM(DATA_BANK);

    tempNPC.speciesId = npcDex[npcId].speciesId;
    tempNPC.xTile =     npcDex[npcId].xTile;
    tempNPC.yTile =     npcDex[npcId].yTile;
    tempNPC.routineId = npcDex[npcId].routineId;

    SWITCH_ROM(nextBank);
    return tempNPC;
}

