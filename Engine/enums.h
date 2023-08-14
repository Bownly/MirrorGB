#ifndef ENUMS_H
#define ENUMS_H

typedef enum {
    STATE_TITLE,
    STATE_LEVEL,
    STATE_PAUSEMENU,
} GAMESTATE;

typedef enum {
    SUB_INIT,
    SUB_REINIT,
    SUB_LOOP,
    SUB_SPOTTED
} SUBSTATE;

typedef enum {
    ENTITY_IDLE,
    ENTITY_WAITING,
    ENTITY_WALKING,
    ENTITY_DEAD,
    ENTITY_TOGGLING_HIDE
} ENTITYSTATE;

typedef enum {
    DIR_UP = 0U,
    DIR_DOWN = 1U,
    DIR_LEFT = 2U,
    DIR_RIGHT = 3U
} DIRECTION;

typedef enum {
    ACT_WALK,
    ACT_TURN,
    ACT_WAIT,
    ACT_TOGGLE_HIDING,
    ACT_SWITCH_ROUTINE
} ACTION;

#endif
