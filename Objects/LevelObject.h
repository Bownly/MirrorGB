#include <gb/gb.h>
#include "../Engine/enums.h"

#ifndef LEVELOBJECT_H
#define LEVELOBJECT_H

typedef struct LevelObject {
    UINT8 roomRId;
    UINT8 roomMId;
    UINT8 metatilesRId;
    UINT8 metatilesMId;
    UINT8 npcCount;
    UINT8 npcSpecies[8U];
    UINT8 npcIds[8U];
} LevelObject;

#endif