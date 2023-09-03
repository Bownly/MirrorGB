#include <gb/gb.h>

#include "../Engine/enums.h"
#include "../Objects/NPCObject.h"


const NPCObject npcDex[] =
    {
        // Tutorial
        { .speciesId =  0U, .xTile = 12U, .yTile =  8U, .routineId =  6U },
        { .speciesId =  0U, .xTile =  7U, .yTile =  5U, .routineId =  7U },
        // House map
        { .speciesId =  1U, .xTile = 16U, .yTile = 15U, .routineId =  0U },
        { .speciesId =  1U, .xTile = 27U, .yTile = 26U, .routineId =  1U },
        { .speciesId =  1U, .xTile = 16U, .yTile = 29U, .routineId =  2U },
        { .speciesId =  1U, .xTile =  7U, .yTile = 22U, .routineId =  3U },
        { .speciesId =  1U, .xTile =  4U, .yTile = 15U, .routineId =  4U },
        { .speciesId =  1U, .xTile =  2U, .yTile = 10U, .routineId =  5U }
    };
