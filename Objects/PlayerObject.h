#include <gb/gb.h>
#include "../Engine/enums.h"

#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H
 
typedef struct PlayerObject {
    PLAYERSTATE state;
    UINT8 spriteId;
    UINT8 animFrame;
    UINT16 xMapPos;
    UINT16 yMapPos;
    UINT8 xSpr;
    UINT8 ySpr;
    UINT8 xTile;
    UINT8 yTile;
    UINT8 xTileSmall;
    UINT8 yTileSmall;
    UINT8 topOffsetInPx;  // Offset from top to center in px
    UINT8 bottomOffsetInPx;
    UINT8 leftOffsetInPx;
    UINT8 rightOffsetInPx;
    DIRECTION dir;
    UINT8 moveSpeed;
    INT8 xVel;
    INT8 yVel;
    UINT8 hpMax;
    UINT8 hpCur;
} PlayerObject;

#endif
