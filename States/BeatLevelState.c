#include <gb/gb.h>
#include <rand.h>

#include "../Engine/common.h"
#include "../Engine/enums.h"
#include "../Engine/fade.h"
// #include "../Engine/ram.h"
#include "../Engine/songPlayer.h"

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

static UINT8 slideNumber = 0U;
static UINT8 screenShakeTick;
static UINT8 hideWinY1;
static UINT8 hideWinY2;
static UINT8 showWinY1;
static UINT8 showWinY2;


/* SUBSTATE METHODS */
static void phaseBeatLevelInit(void);
static void phaseBeatLevelLoop(void);

/* INPUT METHODS */

/* HELPER METHODS */
static void initSlide(void);
static void parallaxMagic(void);

/* DISPLAY METHODS */
static void shakeScreen(void);


void BeatLevelStateMain(void)
{
    curJoypad = joypad();

    switch (substate)
    {
        case SUB_INIT:
            phaseBeatLevelInit();
            break;
        case SUB_LOOP:
            phaseBeatLevelLoop();
            break;
        default:  // Abort to... uh, itself in the event of unexpected state
            gamestate = STATE_TITLE;
            substate = SUB_INIT;
            break;
    }
    prevJoypad = curJoypad;
}


/******************************** SUBSTATE METHODS *******************************/
static void phaseBeatLevelInit(void)
{
    // // Parallax magic
    // // Set the LYC register at 0, where we will start the scrolling logic
    // STAT_REG|=STATF_LYC; // prepare LYC=LY interrupt when LCD/STAT interrupts are enabled
    // LYC_REG=0U; // set the scanline where interrupt first fires
    // CRITICAL{
    //     add_LCD(parallaxMagic);
    // }

    // Initializations
    animTick = 0U;
    HIDE_WIN;
    SHOW_SPRITES;

    init_bkg(0x00U);
    move_bkg(0U, 0U);
    screenShakeTick = 0U;

    switch (roomId >> 1U)
    {
        case 0U:
            set_bkg_data(0U, BeatLevel1Illustration_TILE_COUNT, BeatLevel1Illustration_tiles);
            set_bkg_tiles(0U, 0U, 20U, 18U, BeatLevel1Illustration_map);
            break;
        case 1U:
            set_bkg_data(0U, BeatLevel2Illustration_TILE_COUNT, BeatLevel2Illustration_tiles);
            set_bkg_tiles(0U, 0U, 20U, 18U, BeatLevel2Illustration_map);
            break;
        case 2U:
            set_bkg_data(0U, BeatLevel3Illustration_TILE_COUNT, BeatLevel3Illustration_tiles);
            set_bkg_tiles(0U, 0U, 20U, 18U, BeatLevel3Illustration_map);
            break;
    }
    substate = SUB_LOOP;
    fadeInFromBlack();


    // switch(slideNumber)
    // {
    //     case 0U:
    //         move_win(7U, 72U);
    //         break;
    //     case 1U:
    //         move_win(7U, 0U);
    //         break;
    //     case 2U:
    //         move_win(167U, 0U);
    //         break;
    //     case 4U:
    //         move_win(7U, 0U);
    //         break;
    //     case 5U:
    //         LYC_REG = 0U;
    //         break;
    // }

    // OBP1_REG = DMG_PALETTE(DMG_WHITE, DMG_LITE_GRAY, DMG_DARK_GRAY, DMG_BLACK);
    playOutsideSong(SONG_WIN);
}

static void phaseBeatLevelLoop(void)
{
    shakeScreen();
    // animatePressStart();

    if ((curJoypad & J_A && curJoypad & J_A) || (curJoypad & J_START && !(prevJoypad & J_START)))
    {
        fadeout();
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
static void parallaxMagic(void)
{
    // What scanline are we currently at?
    switch(slideNumber)
    {
        case 0U:
            switch(LYC_REG)
            {
                case 0U:
                    WX_REG = 7U;
                    break;
            }
            break;
        case 1U:
            switch(LYC_REG)
            {
                case 0U:
                    WX_REG = 7U;
                    LYC_REG = 55U;
                    break;
                case 55U:
                    WX_REG = 160U;
                    LYC_REG = 80U;
                    break;
                case 80U:
                    WX_REG = 7U;
                    LYC_REG = 0U;
                    break;
            }
            break;
        // case 2U:
        //     switch(LYC_REG)
        //     {
        //         case 0U:
        //             WX_REG = 160U;
        //             LYC_REG = 55U;
        //             break;
        //     }
        //     break;
        case 4U:
            switch(LYC_REG)
            {
                case 0U:
                    WX_REG = 7U;
                    LYC_REG = 70U;
                    break;
                case 70U:
                    WX_REG = 160U;
                    LYC_REG = 0U;
                    break;
            }
            break;
        case 5U:
            if (LYC_REG == 88U)
                WX_REG = 7U;
            break;
    }
    // switch(LYC_REG)
    // {
    //     case hideWinY1:
    //     case hideWinY2:
    //         WX_REG = 167U;
    //         break;
    //     case showWinY1:
    //     case showWinY2:
    //         WX_REG = 7U;
    //         break;
    // }
    // if (LYC_REG == hideWinY1 || LYC_REG == hideWinY2)
    //     WX_REG = 167U;
    // else if (LYC_REG == showWinY1 || LYC_REG == showWinY2)
    //     WX_REG = 7U;

}

static void shakeScreen(void)
{
    k = 1U;
    if ((roomId >> 2U) == 3U)
        k = 2U;
        
    if (screenShakeTick != 26U)
    {
        ++screenShakeTick;
        switch (screenShakeTick)
        {
            case 5U:
                scroll_bkg(k, 0);
                break;
            case 10U:
                scroll_bkg(-k, 0);
                break;
            case 15U:
                scroll_bkg(0, k);
                break;
            case 20U:
                scroll_bkg(0, -k);
                screenShakeTick = 0U;
                break;
        }
    }
}
