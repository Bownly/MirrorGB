#include <gb/gb.h>
#include <rand.h>

#include "../Engine/common.h"
#include "../Engine/enums.h"
#include "../Engine/fade.h"
// #include "../Engine/ram.h"
#include "../Engine/songPlayer.h"

#include "../Assets/Illustrations/ending01.h"
#include "../Assets/Illustrations/ending02.h"
#include "../Assets/Illustrations/ending03.h"

extern UINT8 curJoypad;
extern UINT8 prevJoypad;
extern UINT8 i;  // Used mostly for loops
extern UINT8 j;  // Used mostly for loops
extern UINT8 k;  // Used for whatever
extern INT8 l;  // Used for whatever
extern UINT8 m;  // Used for menus generally
extern UINT8 n;  // Used for menus generally
extern UINT8 p;  // Used for passing values between states
extern UINT8 r;  // Used for randomization stuff

extern UINT8 animTick;
extern UINT8 animFrame;

extern UINT8 gamestate;
extern UINT8 substate;


/* SUBSTATE METHODS */
static void phaseBeatGameInit(void);
static void phaseBeatGameLoop(void);

/* INPUT METHODS */

/* HELPER METHODS */

/* DISPLAY METHODS */


void BeatGameStateMain(void)
{
    curJoypad = joypad();

    switch (substate)
    {
        case SUB_INIT:
            phaseBeatGameInit();
            break;
        case SUB_LOOP:
            phaseBeatGameLoop();
            break;
        default:  // Abort to title screen in the event of unexpected state
            gamestate = STATE_TITLE;
            substate = SUB_INIT;
            break;
    }
    prevJoypad = curJoypad;
}


/******************************** SUBSTATE METHODS *******************************/
static void phaseBeatGameInit(void)
{
    // Initializations
    // stopSong();
    init_bkg(0xFFU);
    animTick = 0U;
    HIDE_WIN;
    HIDE_SPRITES;

    move_bkg(0U, 0U);

    if (p == 0U)
    {
        set_bkg_data(0x00U, ending01_TILE_COUNT, ending01_tiles);
        set_bkg_tiles(0U, 0U, 20U, 18U, ending01_map);
        playOutsideSong(SONG_WIN);
    }
    else if (p == 1U)
    {
        set_bkg_data(0x00U, ending02_TILE_COUNT, ending02_tiles);
        set_bkg_tiles(0U, 0U, 20U, 18U, ending02_map);
    }
    else if (p == 2U)
    {
        set_bkg_data(0x00U, ending03_TILE_COUNT, ending03_tiles);
        set_bkg_tiles(0U, 0U, 20U, 18U, ending03_map);
    }


    substate = SUB_LOOP;
    fadeInFromBlack();

    // OBP1_REG = DMG_PALETTE(DMG_WHITE, DMG_LITE_GRAY, DMG_DARK_GRAY, DMG_BLACK);
}

static void phaseBeatGameLoop(void)
{
    ++animTick;

    if ((curJoypad & J_A && curJoypad & J_A) || (curJoypad & J_START && !(prevJoypad & J_START)))
    {
        fadeOutToBlack();

        ++p;
        if (p != 3U)
            gamestate = STATE_BEAT_GAME;
        else
        {
            p = 0xFF;
            gamestate = STATE_TITLE;
        }
        substate = SUB_INIT;
    }
}

/******************************** INPUT METHODS *********************************/


/******************************** HELPER METHODS *********************************/


/******************************** DISPLAY METHODS ********************************/
