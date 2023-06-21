#include <gb/gb.h>
#include "../Engine/enums.h"

#ifndef LEVELOBJECT_H
#define LEVELOBJECT_H

typedef struct LevelObject {
    const unsigned char* map;
    UINT8 w;
    UINT8 h;
} LevelObject;

#endif