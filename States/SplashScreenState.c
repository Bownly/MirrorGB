#include <gb/gb.h>
#include <rand.h>

#include "../Engine/common.h"
#include "../Engine/enums.h"
#include "../Engine/fade.h"
// #include "../Engine/ram.h"
#include "../Engine/songPlayer.h"

#include "../Assets/Illustrations/GBCompoIllustration.h"
#include "../Assets/Illustrations/AttributionIllustration.h"

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
static void phaseSplashScreenInit(void);
static void phaseSplashScreenLoop(void);

/* INPUT METHODS */

/* HELPER METHODS */

/* DISPLAY METHODS */


void SplashScreenStateMain(void)
{
    curJoypad = joypad();

    switch (substate)
    {
        case SUB_INIT:
            phaseSplashScreenInit();
            break;
        case SUB_LOOP:
            phaseSplashScreenLoop();
            break;
        default:  // Abort to title screen in the event of unexpected state
            gamestate = STATE_TITLE;
            substate = SUB_INIT;
            break;
    }
    prevJoypad = curJoypad;
}


/******************************** SUBSTATE METHODS *******************************/
static void phaseSplashScreenInit(void)
{
    // Initializations
    // stopSong();
    init_bkg(0xFFU);
    animTick = 0U;
    HIDE_WIN;
    HIDE_SPRITES;

    move_bkg(0, 0U);

    if (p == 0U)
    {
        set_bkg_data(0x00U, GBCompoIllustration_TILE_COUNT, GBCompoIllustration_tiles);
        set_bkg_tiles(0U, 0U, 20U, 18U, GBCompoIllustration_map);
    }
    else if (p == 1U)
    {
        set_bkg_data(0x00U, AttributionIllustration_TILE_COUNT, AttributionIllustration_tiles);
        set_bkg_tiles(0U, 0U, 20U, 18U, AttributionIllustration_map);
    }

    substate = SUB_LOOP;
    fadeInFromBlack();

    // OBP1_REG = DMG_PALETTE(DMG_WHITE, DMG_LITE_GRAY, DMG_DARK_GRAY, DMG_BLACK);
    playOutsideSong(SONG_WIN);
}

static void phaseSplashScreenLoop(void)
{
    ++animTick;

    if (animTick == 180U || (curJoypad & J_A && curJoypad & J_A))
    {
        fadeOutToBlack();
        playSfx(SFX_7);

        ++p;
        if (p != 2U)
            gamestate = STATE_SPLASH;
        else
        {
            p = 0xFF;
            gamestate = STATE_TITLE;
            stopSong();
        }
        substate = SUB_INIT;
    }
    else if (curJoypad & J_START && curJoypad & J_START)
    {
        p = 0xFF;
        gamestate = STATE_TITLE;
        substate = SUB_INIT;
        stopSong();
    }

}

/******************************** INPUT METHODS *********************************/


/******************************** HELPER METHODS *********************************/


/******************************** DISPLAY METHODS ********************************/
