#include <gb/gb.h>
#include <rand.h>

#include "../Engine/common.h"
#include "../Engine/enums.h"
#include "../Engine/fade.h"
// #include "../Engine/ram.h"
#include "../Engine/ILoadIllustrationData.h"
#include "../Engine/songPlayer.h"


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

static UINT8 slideNumber = 0U;
static UINT8 screenShakeTick;
static UINT8 hideWinY1;
static UINT8 hideWinY2;
static UINT8 showWinY1;
static UINT8 showWinY2;

#define SLIDE_COUNT 5U


/* SUBSTATE METHODS */
static void phaseIntroInit(void);
static void phaseIntroLoop(void);

/* INPUT METHODS */

/* HELPER METHODS */
static void exitState(void);
static void initSlide(void);

/* DISPLAY METHODS */
static void parallaxMagic(void);
static void shakeScreen(void);


void IntroStateMain(void)
{
    curJoypad = joypad();

    switch (substate)
    {
        case SUB_INIT:
            phaseIntroInit();
            break;
        case SUB_LOOP:
            phaseIntroLoop();
            break;
        default:  // Abort to... uh, itself in the event of unexpected state
            gamestate = STATE_TITLE;
            substate = SUB_INIT;
            break;
    }
    prevJoypad = curJoypad;
}


/******************************** SUBSTATE METHODS *******************************/
static void phaseIntroInit(void)
{
    // Parallax magic
    // Set the LYC register at 0, where we will start the scrolling logic
    STAT_REG|=STATF_LYC; // prepare LYC=LY interrupt when LCD/STAT interrupts are enabled
    LYC_REG=0U; // set the scanline where interrupt first fires
    CRITICAL{
        add_LCD(parallaxMagic);
    }
    set_interrupts(LCD_IFLAG|VBL_IFLAG); // additionally enable LCD interrupt 

    // Initializations
    // stopSong();
    animTick = 0U;
    SHOW_WIN;
    SHOW_SPRITES;

    slideNumber = 0U;
    initSlide();

    substate = SUB_LOOP;
    fadeInFromBlack();

    // OBP1_REG = DMG_PALETTE(DMG_WHITE, DMG_LITE_GRAY, DMG_DARK_GRAY, DMG_BLACK);
    playOutsideSong(SONG_INTRO);
}

static void phaseIntroLoop(void)
{
    shakeScreen();
    // animatePressStart();

    if ((curJoypad & J_A && !(prevJoypad & J_A)))
    {
        fadeOutToBlack();
        move_bkg(0U, 0U);
        ++slideNumber;
        
        if (slideNumber == SLIDE_COUNT)
        {
            // CRITICAL {
            //     remove_LCD(parallaxMagic);
            // }
            // // set_interrupts(LCD_IFLAG); // additionally enable LCD interrupt 
            // gamestate = STATE_LEVEL;
            // substate = SUB_INIT;
            // stopSong();
            exitState();
            return;
        }
        else
            initSlide();

        // set_bkg_tile_xy(0,0,slideNumber);
    }
    else if (curJoypad & J_START && !(prevJoypad & J_START))
    {
        fadeOutToBlack();
        move_bkg(0U, 0U);
        exitState();
        return;
    }
}

/******************************** INPUT METHODS *********************************/


/******************************** HELPER METHODS *********************************/
static void exitState(void)
{
    // fadeOutToBlack();
    // move_bkg(0U, 0U);
    CRITICAL {
        remove_LCD(parallaxMagic);
    }
    gamestate = STATE_LEVEL;
    substate = SUB_INIT;
    LYC_REG = 0U;
    stopSong();
}

static void initSlide(void)
{
    init_bkg(0x00U);
    move_bkg(0U, 0U);
    screenShakeTick = 0U;

    wait_vbl_done();
    CRITICAL{
        remove_LCD(parallaxMagic);
    }
    loadIllustrationData(slideNumber);
    // if (slideNumber != SLIDE_COUNT)
    // {
        CRITICAL{
            add_LCD(parallaxMagic);
        }
    // }
    LYC_REG = 0U;
    
    switch(slideNumber)
    {
        case 0U:
            move_win(7U, 72U);
            break;
        case 1U:
            move_win(7U, 0U);
            break;
        case 2U:
            move_win(167U, 0U);
            break;
        case 4U:
            move_win(7U, 0U);
            break;
        // case SLIDE_COUNT:
        //     LYC_REG = 0U;
        //     break;
    }

    fadeInFromBlack();
}


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
        // case 5U:
        //     if (LYC_REG == 88U)
        //         WX_REG = 7U;
        //     break;
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
    if (slideNumber == 3U)
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
