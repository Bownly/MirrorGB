#include <gb/gb.h>
#include <rand.h>

// #include "Engine/common.h"
#include "Engine/enums.h"
// #include "Engine/fade.h"
// #include "Engine/ram.h"
// #include "Engine/songPlayer.h"

// #include "Assets/Tiles/borderTiles.h"
// #include "Assets/Tiles/fontTiles.h"

#include "Objects/EntityObject.h"

#include "States/LevelState.h"


// Save data stuff
const UBYTE RAM_SIG[6U] = {'M','I','R','R','O','R'};
UBYTE *data;

UINT8 vbl_count;
UINT8 curJoypad;
UINT8 prevJoypad;
UINT8 i;  // Used mostly for loops
UINT8 j;  // Used mostly for loops
UINT8 k;  // Used for whatever
UINT8 l;  // Used for whatever
UINT8 m;  // Used for menus generally
UINT8 n;  // Used for menus generally
UINT8 p;  // Used for passing values between states
UINT8 r;  // Used for randomization stuff

UINT8 gamestate = STATE_TITLE;
UINT8 substate;
// GAMESTATE nextGamestate;
// SUBSTATE prevSubstate;
// SUBSTATE nextSubstate;

// UINT8 shouldSkipMusicThisFrame;

UINT8 animFrame = 0U;
UINT8 animTick = 0U;

UINT16 camera_x = 0U;
UINT16 camera_y = 0U;

EntityObject player;
UINT8 handyDandyString[19U];
UINT8 (*playGridPtr)[32U][32U];
UINT8 playGrid[32U][32U];
UINT8 playGridM[32U][32U];


void initRAM(UINT8);

void main(void)
{
 	// initRAM(0U);

    // Sound stuff
    NR52_REG = 0x80; // is 1000 0000 in binary and turns on sound
    NR50_REG = 0x77; // sets the volume for both left and right channel just set to max 0x77
    NR51_REG = 0xFF; // is 1111 1111 in binary, select which chanels we want to use in this case all of them. One bit for the L one bit for the R of all four channels
    set_interrupts(TIM_IFLAG | VBL_IFLAG);
 
    // set_bkg_data(0xF0U, 8U, borderTiles);
    // set_bkg_data(0U, 91U, fontTiles);

    SPRITES_8x8;

    init_bkg(0xFFU);
    DISPLAY_ON;
    SHOW_SPRITES;
    SHOW_BKG;
    // fadeout();

    // // Misc inits and stuff
    // shouldSkipMusicThisFrame = FALSE;
    // add_VBL(songPlayerUpdate);

    gamestate = STATE_LEVEL;
    substate = SUB_INIT;
    
    while(1U)
    {
        wait_vbl_done();

        switch(gamestate)
        {
            case STATE_TITLE:
                // titleStateMain();
                break;
            case STATE_LEVEL:
                SWITCH_ROM(2U);
                LevelStateMain();
                break;
           
        }
    }
}


// void initRAM(UBYTE force_clear)
// {
//     UBYTE initialized;

//     ENABLE_RAM;
//     SWITCH_RAM(0U);

//     // Check for signature
//     initialized = 1U;
//     for (i = 0U; i != 6U; ++i)
//     {
//         if (ram_data[RAM_SIG_ADDR + i] != RAM_SIG[i])
//         {
//             initialized = 0U;
//             break;
//         }
//     }

//     // Initialize memory
//     if (initialized == 0U || force_clear)
//     {
//         for(i = 0U; i != 255U; ++i) {
//             ram_data[i] = 0U;
//         }

//         for (i = 0U; i != 6U; ++i) {
//             ram_data[RAM_SIG_ADDR + i] = RAM_SIG[i];
//         }
//     }

//     if (ram_data[RAM_UNLOCKED_CHARS] == 0U)
//         ram_data[RAM_UNLOCKED_CHARS] = 0b00000011;
    
//     DISABLE_RAM;
// }
