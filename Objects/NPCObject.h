#include <gb/gb.h>
#include "../Engine/enums.h"

#ifndef NPCOBJECT_H
#define NPCOBJECT_H

typedef struct NPCObject {
    UINT8 speciesId;
    UINT8 xTile;
    UINT8 yTile;
    UINT8 routineId;
} NPCObject;

#endif