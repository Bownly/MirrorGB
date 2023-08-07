#include <gb/gb.h>
#include "../Engine/enums.h"
#include "RoutineObject.h"

#ifndef ENTITYOBJECT_H
#define ENTITYOBJECT_H
 
typedef struct EntityObject {
    ENTITYSTATE state;
    UINT8 id;
    UINT8 speciesId;
    UINT8 spriteId;
    UINT8 animTick;
    UINT8 animFrame;
    UINT16 xSpr;
    UINT16 ySpr;
    UINT8 xTile;
    UINT8 yTile;
    DIRECTION dir;
    UINT8 moveSpeed;
    UINT16 actionTimer;
    UINT8 curActionIndex;
    UINT8 curRoutineIndex;
    UINT8 isVisible;
    UINT8 isHiding;
    UINT8 visionDistance;
    INT8 xVel;
    INT8 yVel;
    UINT8 hpMax;
    UINT8 hpCur;
    UINT8 lives;
} EntityObject;

#endif
