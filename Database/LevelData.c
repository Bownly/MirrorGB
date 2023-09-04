#include <gb/gb.h>

// #include "../Engine/enums.h"
#include "../Objects/LevelObject.h"

const LevelObject levelDex[8U] = {
    // Tutorial level
    { 
        .roomRId = 0U,
        .roomMId = 1U,
        .metatilesRId = 0U,
        .metatilesMId = 1U,
        .npcCount = 2U,
        .npcSpecies = { 0U, 0U, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU },
        .npcIds = { 0U, 1U, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU }
    },
    // House level
    { 
        .roomRId = 2U,
        .roomMId = 3U,
        .metatilesRId = 2U,
        .metatilesMId = 3U,
        .npcCount = 6U,
        .npcSpecies = { 1U, 1U, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU },
        .npcIds = { 2U, 3U, 4U, 5U, 6U, 7U, 0xFFU, 0xFFU }
    }
};
