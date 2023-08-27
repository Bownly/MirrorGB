#include <gb/gb.h>
#include <rand.h>

#include "../Engine/common.h"
#include "../Engine/enums.h"
#include "../Engine/fade.h"
// #include "../Engine/ram.h"
#include "../Engine/songPlayer.h"

#include "../Assets/Illustrations/TitleScreenIllustration.h"

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
static void phaseTitleInit(void);
static void phaseTitleLoop(void);

/* INPUT METHODS */

/* HELPER METHODS */

/* DISPLAY METHODS */


void TitleStateMain(void)
{
    curJoypad = joypad();

    switch (substate)
    {
        case SUB_INIT:
            phaseTitleInit();
            break;
        case SUB_LOOP:
            phaseTitleLoop();
            break;
        default:  // Abort to... uh, itself in the event of unexpected state
            gamestate = STATE_TITLE;
            substate = SUB_INIT;
            break;
    }
    prevJoypad = curJoypad;
}


/******************************** SUBSTATE METHODS *******************************/
static void phaseTitleInit(void)
{
    // Initializations
    // stopSong();
    init_bkg(0xFFU);
    animTick = 0U;
    HIDE_WIN;

    // scroll_bkg(4, 0U);  // For centering the screen

    set_bkg_data(0x40U, TitleScreenIllustration_TILE_COUNT, TitleScreenIllustration_tiles);
    set_bkg_tiles(0U, 0U, 20U, 18U, TitleScreenIllustration_map);

    substate = SUB_LOOP;
    fadein();

    // OBP1_REG = DMG_PALETTE(DMG_WHITE, DMG_LITE_GRAY, DMG_DARK_GRAY, DMG_BLACK);
    playOutsideSong(SONG_MAINMENU);
}

static void phaseTitleLoop(void)
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
        fadeout();
        // initrand(DIV_REG);
        // move_bkg(0U, 0U);

        gamestate = STATE_LEVEL;
        substate = SUB_INIT;
        stopSong();

        roomId = 0U;
    }
    // else if (curJoypad & J_SELECT && curJoypad & J_B)
    // {
    //     fadeout();
    //     gamestate = STATE_DELETE_SAVE;
    //     substate = SUB_INIT;
    // }
    // else if (curJoypad & J_SELECT && curJoypad & J_A)
    // {
    //     fadeout();
    //     ENABLE_RAM;
    //     // language = loadLanguageSetting();
    //     language = (language + 1U) % 2U;
    //     saveLanguageSetting(language);
    //     if (language == 1U)
    //         set_bkg_data(0U, 46U, alBhedFontTiles);
    //     else
    //         set_bkg_data(0U, 46U, fontTiles);
    //     DISABLE_RAM;
    //     fadein();
    //
    //
    // }
}

/******************************** INPUT METHODS *********************************/


/******************************** HELPER METHODS *********************************/


/******************************** DISPLAY METHODS ********************************/
