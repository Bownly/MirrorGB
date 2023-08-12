#include <gb/gb.h>
#include "../Engine/enums.h"

#ifndef ROOMOBJECT_H
#define ROOMOBJECT_H

typedef struct RoomObject {
    const unsigned char* map;
    UINT8 w;
    UINT8 h;
    UINT8 tilesetId;
} RoomObject;

#endif