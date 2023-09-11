#include <gb/gb.h>
#include <rand.h>

#include "../Engine/common.h"
#include "../Engine/enums.h"
#include "../Engine/fade.h"
// #include "../Engine/ram.h"
#include "../Engine/songPlayer.h"

#include "../Assets/Illustrations/BeatLevelIllustration.h"
#include "../Assets/Illustrations/BeatLevel1Illustration.h"
#include "../Assets/Illustrations/BeatLevel2Illustration.h"
#include "../Assets/Illustrations/BeatLevel3Illustration.h"

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
extern UINT8 roomId;


/* SUBSTATE METHODS */
static void phaseBeatGameInit(void);
static void phaseBeatGameLoop(void);

/* INPUT METHODS */

/* HELPER METHODS */

/* DISPLAY METHODS */


void BeatLevelStateMain(void)
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

    move_bkg(0, 0U);

    set_bkg_data(0x40U, BeatLevelIllustration_TILE_COUNT, BeatLevelIllustration_tiles);
    set_bkg_tiles(0U, 0U, 20U, 18U, BeatLevelIllustration_map);

    substate = SUB_LOOP;
    fadeInFromBlack();

    // OBP1_REG = DMG_PALETTE(DMG_WHITE, DMG_LITE_GRAY, DMG_DARK_GRAY, DMG_BLACK);
    playOutsideSong(SONG_WIN);
}

static void phaseBeatGameLoop(void)
{
    ++animTick;

    // if ((animTick % 64U) / 48U == 0U)
    // {
    //     printLine(5U, 13U, "PRESS START", FALSE);
    // }
    // else
    // {
    //     for (i = 5U; i != 16U; ++i)
    //         set_bkg_tile_xy(i, 13U, 0xFFU);
    // }
    //
    if ((curJoypad & J_A && curJoypad & J_A) || (curJoypad & J_START && !(prevJoypad & J_START)))
    {
        fadeOutToBlack();
        gamestate = STATE_LEVEL;
        substate = SUB_INIT;

        // This looks really silly
        roomId >>= 1U;
        roomId += 1U;
        roomId <<= 1U;

        stopSong();
    }
}

/******************************** INPUT METHODS *********************************/


/******************************** HELPER METHODS *********************************/


/******************************** DISPLAY METHODS ********************************/
