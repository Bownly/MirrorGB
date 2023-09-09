#include <gb/gb.h>
#include <rand.h>

#include "../Engine/common.h"
#include "../Engine/enums.h"
#include "../Engine/fade.h"
// #include "../Engine/ram.h"
#include "../Engine/songPlayer.h"

#include "../Assets/Illustrations/TitleScreenIllustration.h"

#include "../Assets/Illustrations/TitleScreenIllustration.h"
#include "../Assets/Sprites/PressSprite.h"
#include "../Assets/Sprites/StartSprite.h"
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
static UINT8 pressX = 62U;
static UINT8 startX = 114U;
extern UINT8 roomId;


static UINT8 junk = 0U;


/* SUBSTATE METHODS */
static void phaseIntroInit(void);
static void phaseIntroLoop(void);

/* INPUT METHODS */

/* HELPER METHODS */

/* DISPLAY METHODS */
static void animatePressStart(void);


void TitleStateMain(void)
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
    // Initializations
    // stopSong();
    init_bkg(0xFFU);
    animTick = 0U;
    HIDE_WIN;
    SHOW_SPRITES;
    // scroll_bkg(4, 0U);  // For centering the screen

    set_sprite_data(0x00U, PressSprite_TILE_COUNT, PressSprite_tiles);
    set_sprite_data(10U, StartSprite_TILE_COUNT, StartSprite_tiles);
    // set_bkg_data(PressSprite_TILE_COUNT, StartSprite_TILE_COUNT, StartSprite_tiles);
    set_bkg_data(0U, TitleScreenIllustration_TILE_COUNT, TitleScreenIllustration_tiles);
    set_bkg_tiles(0U, 0U, 20U, 18U, TitleScreenIllustration_map);

    substate = SUB_LOOP;
    animatePressStart();
    fadein();

    // OBP1_REG = DMG_PALETTE(DMG_WHITE, DMG_LITE_GRAY, DMG_DARK_GRAY, DMG_BLACK);
    playOutsideSong(SONG_MAINMENU);
}

static void phaseIntroLoop(void)
{
    animatePressStart();

    if ((curJoypad & J_A && !(prevJoypad & J_A)) || (curJoypad & J_START && !(prevJoypad & J_START)))
    {
        fadeOutToBlack();
        move_bkg(0U, 0U);
        initrand(DIV_REG);

        gamestate = STATE_INTRO;
        substate = SUB_INIT;
        stopSong();

        roomId = 0U;
    }
    // else if (curJoypad & J_B && !(prevJoypad & J_B))
    // {
    //     playSfx(junk);
    //     junk++;
    //     junk %= 0x0CU;
    // }
}

/******************************** INPUT METHODS *********************************/


/******************************** HELPER METHODS *********************************/


/******************************** DISPLAY METHODS ********************************/
static void animatePressStart(void)
{
    ++animTick;
    
    if ((animTick % 128U) / 104U == 0U)
    {
        move_metasprite(PressSprite_metasprites[0U], 0U, 0U, pressX, 130U);
        move_metasprite(StartSprite_metasprites[0U], 10U, 10U, startX, 130U);
    }
    else
    {
        hide_sprites_range(0U, 20U);
    }


}
