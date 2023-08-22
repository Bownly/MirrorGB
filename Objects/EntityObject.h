#include <gb/gb.h>
#include "../Engine/enums.h"
#include "ActionObject.h"
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
    ENTITYSTATE oldState;
    DIRECTION oldDir;
    UINT16 oldXSpr;
    UINT16 oldYSpr;
    UINT8 oldXTile;
    UINT8 oldYTile;
    UINT8 oldActionTimer;
    UINT8 oldActionIndex;
    UINT8 oldRoutineIndex;
    UINT8 isChasing;
    UINT8 isVisible;
    UINT8 isHiding;
    UINT8 visionDistance;
    INT8 xVel;
    INT8 yVel;
    UINT8 hpMax;
    UINT8 hpCur;
    UINT8 lives;
    // RoutineObject chasingRoutine;
    ActionObject chasingActions[8U];
    UINT8 chasingActionsCount;
} EntityObject;

#endif
