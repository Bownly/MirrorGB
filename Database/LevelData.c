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
        .npcSpecies = { 0U, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU },
        .npcIds = { 0U, 1U, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU }
    },
    // Church level
    { 
        .roomRId = 4U,
        .roomMId = 5U,
        .metatilesRId = 2U,
        .metatilesMId = 3U,
        .npcCount = 6U,
        .npcSpecies = { 5U, 1U, 2U, 3U, 0xFFU, 0xFFU, 0xFFU, 0xFFU },
        .npcIds = { 8U, 9U, 10U, 11U, 12U, 13U, 0xFFU, 0xFFU }
    },
    // House level
    { 
        .roomRId = 2U,
        .roomMId = 3U,
        .metatilesRId = 2U,
        .metatilesMId = 3U,
        .npcCount = 6U,
        .npcSpecies = { 1U, 2U, 3U, 4U, 0xFFU, 0xFFU, 0xFFU, 0xFFU },
        .npcIds = { 2U, 3U, 4U, 5U, 6U, 7U, 0xFFU, 0xFFU }
    },
    // School level
    { 
        .roomRId = 6U,
        .roomMId = 7U,
        .metatilesRId = 2U,
        .metatilesMId = 3U,
        .npcCount = 6U,
        .npcSpecies = { 4U, 1U, 2U, 3U, 0xFFU, 0xFFU, 0xFFU, 0xFFU },
        .npcIds = { 14U, 15U, 16U, 17U, 18U, 19U, 0xFFU, 0xFFU }
    }
};
