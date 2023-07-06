#ifndef ENUMS_H
#define ENUMS_H

typedef enum {
    STATE_TITLE,
    STATE_LEVEL,
    STATE_PAUSEMENU,
} GAMESTATE;

typedef enum {
    SUB_INIT,
    SUB_LOOP
} SUBSTATE;

typedef enum {
    ENTITY_IDLE,
    ENTITY_WAITING,
    ENTITY_WALKING,
    ENTITY_DEAD
} ENTITYSTATE;

typedef enum {
    DIR_UP = 0U,
    DIR_DOWN = 24U,
    DIR_LEFT = 36U,
    DIR_RIGHT = 12U
} DIRECTION;  // These are in increments of 12 to make the math faster when using directions for sprite frame indices

typedef enum {
    ACT_WALK,
    ACT_TURN,
    ACT_WAIT,
    ACT_SWITCH_ROUTINE
} ACTION;

#endif
