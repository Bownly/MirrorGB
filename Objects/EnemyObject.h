#include <gb/gb.h>
#include "../Engine/enums.h"

#ifndef ENEMYOBJECT_H
#define ENEMYOBJECT_H
 
typedef struct EnemyObject {
    UINT8 id;
    UINT8 speciesId;
    ENEMYSTATE state;
    UINT8 spriteId;
    UINT8 animFrame;
    UINT16 xSpr;
    UINT16 ySpr;
    UINT16 xMap;
    UINT16 yMap;
    UINT8 visible;
    DIRECTION dir;
    UINT8 moveSpeed;
    UINT8 hpMax;
    UINT8 hpCur;
} EntityObject;

#endif
