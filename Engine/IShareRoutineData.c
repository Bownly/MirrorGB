#include <gb/gb.h>
#include <stdio.h>
#include <string.h>

#include "../Database/RoutineData.h"
#include "../Objects/RoutineObject.h"


#define DATA_BANK 4U

extern ActionObject tempAction;
UINT8 returnVal;

// Returns next actionId
UINT8 getAction(UINT8 routineId, UINT8 actionId)
{
    UINT8 nextBank = CURRENT_BANK;
    SWITCH_ROM(DATA_BANK);
    tempAction.action =    (*routineDex[routineId].actions)[actionId].action;
    tempAction.direction = (*routineDex[routineId].actions)[actionId].direction;
    tempAction.magnitude = (*routineDex[routineId].actions)[actionId].magnitude;

    returnVal = (actionId + 1U) % routineDex[routineId].length;
    SWITCH_ROM(nextBank);

    return returnVal;
}
