#ifndef ENUMS_H
#define ENUMS_H

typedef enum {
    STATE_TITLE,
    STATE_SPLASH,
    STATE_INTRO,
    STATE_LEVEL,
    STATE_PAUSED,
    STATE_BEAT_LEVEL,
    STATE_BEAT_GAME,
    STATE_GAMEOVER
} GAMESTATE;

typedef enum {
    SUB_INIT,
    SUB_REINIT,
    SUB_LOOP,
    SUB_SPOTTED,
    SUB_KILL_PLAYER,
    SUB_MIRRORING,
    SUB_MIRROROUTING,
    SUB_PAUSED,
    SUB_TASTEFUL_PAUSE
} SUBSTATE;

typedef enum {
    ENTITY_IDLE,
    ENTITY_WAITING,
    ENTITY_WALKING,
    ENTITY_FINISHING_WALK,
    ENTITY_DEAD,
    ENTITY_TOGGLING_HIDE,
    ENTITY_ACTIONING
} ENTITYSTATE;

typedef enum {
    DIR_UP = 0U,
    DIR_DOWN = 1U,
    DIR_LEFT = 2U,
    DIR_RIGHT = 3U,
    DIR_RAND
} DIRECTION;

typedef enum {
    ACT_WALK,
    ACT_FINISHING_WALK,
    ACT_TURN,
    ACT_WAIT,
    ACT_TOGGLE_HIDING,
    ACT_SWITCH_ROUTINE,
    ACT_SPECIAL_ACTION
} ACTION;

typedef enum {
    SONG_LEVEL01,
    SONG_LEVEL02,
    SONG_LEVEL03,
    SONG_YOUDIED,
    SONG_WIN,
    SONG_CGSCENE,
    SONG_INTRO,
    SONG_MAINMENU,
    SONG_PREMENU
} SONGS;

typedef enum {
    SFX_0,
    SFX_1,
    SFX_2,
    SFX_3,
    SFX_4,
    SFX_5,
    SFX_6,
    SFX_7,
    SFX_8,
    SFX_9,
    SFX_A,
    SFX_B
} SFX;

#endif
