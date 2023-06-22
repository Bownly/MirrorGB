#include <gb/gb.h>
#include <rand.h>
#include <string.h>

#include "../Engine/common.h"
#include "../Engine/enums.h"
// #include "../Engine/fade.h"
// #include "../Engine/ram.h"
// #include "../Engine/songPlayer.h"
#include "../Engine/IShareMapData.h"

#include "../Assets/Tiles/GhostTiles.h"
#include "../Assets/Tiles/TadTiles.h"
#include "../Assets/Tiles/HouseTiles.h"
#include "../Assets/Tiles/YaMetaTiles.h"
#include "../Assets/Tiles/fontTiles.h"

// #include "../Assets/Maps/Level1Map.h"

#include "../Objects/EnemyObject.h"
#include "../Objects/LevelObject.h"
#include "../Objects/PlayerObject.h"


// extern const hUGESong_t templateTwilightDriveSong;

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

extern PlayerObject player;
UINT8 playerstate;

extern UINT8 gamestate;
extern UINT8 substate;
// extern UINT8 currentLevel;
extern UINT8 playGrid[32U][32U];
static UINT8 entityGrid[16U][10U];  // Holds IDs of entities
static EntityObject entityList[24U];
static EntityObject* obakeList = entityList;
static EntityObject* okyakusanList = entityList + 12;

#define STARTPOS 0U
#define STARTCAM 0U

static UINT8 roomId;
static UINT8 gridW;
static UINT8 gridH;
static UINT16 camera_max_x = 10U * 16U;
static UINT16 camera_max_y = 9U * 16U;
static UINT8 walkableTileCount = 6U;

// current and new positions of the camera in pixels
static WORD camera_x = STARTCAM, camera_y = STARTCAM, new_camera_x = STARTCAM, new_camera_y = STARTCAM;
// current and new position of the map in tiles
static UBYTE map_pos_x = STARTPOS, map_pos_y = STARTPOS, new_map_pos_x = STARTPOS, new_map_pos_y = STARTPOS;
// redraw flag, indicates that camera position was changed
static UBYTE redraw;

#define PLAYER_X_LEFT_BOUND_PX   8U
#define PLAYER_X_CENTER_BOUND_PX 88U
#define PLAYER_X_RIGHT_BOUND_PX  160U
#define PLAYER_Y_UP_BOUND_PX     16U
#define PLAYER_Y_CENTER_BOUND_PX 80U
#define PLAYER_Y_DOWN_BOUND_PX   152U
#define PLAYER_SPEED    21
#define LEFT_BOUND 48
#define RIGHT_BOUND 652
#define TOP_BOUND 48
#define BOTTOM_BOUND 652
#define OBAKE_BKG_INDEX     0x08U

#define pxToSubpx(px) ((px) << 4U)
#define subPxToPx(subpx) ((subpx) >> 4U)

#define tileToPx(tile) ((tile) << 3U)
#define pxToTile(px) ((px) >> 3U)

#define metatileToPx(metatile) ((metatile) << 4U)
#define pxToMetatile(px) ((px) >> 4U)


/* SUBSTATE METHODS */
static void phaseInit();
static void phaseLoop();

/* INPUT METHODS */
static void inputs();

/* HELPER METHODS */
static void calcPhysics();
static void commonInit();
static UINT8 entityListAdd(UINT8, UINT8, UINT8);
static void entityDetermineNextStep(EntityObject*);
static void entityResolveStep(EntityObject*);
static UINT8 entityTryWalk(EntityObject*, DIRECTION);
static void entityWalk(EntityObject*);
static void loadLevel();
static void loadRoom();

/* DISPLAY METHODS */
static void animatePlayer();
static void drawBkgTile(UINT8, UINT8, UINT8);
// static void showOrHideEntities();


void LevelStateMain()
{
    curJoypad = joypad();

    switch (substate)
    {
        case SUB_INIT:
            phaseInit();
            break;
        case SUB_LOOP:
            phaseLoop();
            break;
        default:  // Abort to title in the event of unexpected state
            gamestate = STATE_TITLE;
            substate = SUB_INIT;
            break;
    }
    prevJoypad = curJoypad;
}


/******************************** SUBSTATE METHODS *******************************/
static void phaseInit()
{
    // Initializations
    animTick = 0U;
    
    HIDE_WIN;
    SHOW_SPRITES;
    SPRITES_8x16;

    // // Check levelId, pull appropriate level
    // loadLevel();

    player.xTile = 1U;
    player.yTile = 1U;
    player.xSpr = 88U;
    player.ySpr = 88U;

    commonInit();

    substate = SUB_LOOP;

    player.moveSpeed = 21U;
    set_bkg_tile_xy(18U,17U,player.moveSpeed/10U);
    set_bkg_tile_xy(19U,17U,player.moveSpeed%10U);

    // fadein();
    OBP0_REG = DMG_PALETTE(DMG_LITE_GRAY, DMG_WHITE, DMG_LITE_GRAY, DMG_BLACK);
}

static void phaseLoop()
{
    ++animTick;

    // Check for player inputs
    inputs();

    // for (k = 0U; k != 24U; ++k)
    //     if (entityList[k].id != 0xFFU)
    //     switch (entityList[k].state)
    //     {
    //         case ENTITY_IDLE:
    //             entityDetermineNextStep(&entityList[k]);
    //             break;
    //         case ENTITY_WALKING:
    //             entityWalk(&entityList[k]);
    //             break;
    //     }

    // showOrHideEntities();
    animatePlayer();

    if (player.state == PLAYER_WALKING)
        calcPhysics();
}


/******************************** INPUT METHODS *********************************/
static void inputs()
{
    if (curJoypad & J_A && !(prevJoypad & J_A))
    {
        player.moveSpeed++;
        set_bkg_tile_xy(18U,17U,player.moveSpeed/10U);
        set_bkg_tile_xy(19U,17U,player.moveSpeed%10U);
    }
    else if (curJoypad & J_B && !(prevJoypad & J_B))
    {
        player.moveSpeed--;
        set_bkg_tile_xy(18U,17U,player.moveSpeed/10U);
        set_bkg_tile_xy(19U,17U,player.moveSpeed%10U);
    }

    // Movement
    if (player.state == PLAYER_IDLE || player.state == PLAYER_WALKING)
    {
        if (curJoypad & J_UP)
        {
            if (player.xSpr != TOP_BOUND)
            {
                player.xVel = 0;
                player.yVel = -player.moveSpeed;
                player.state = PLAYER_WALKING;
                player.dir = DIR_UP;
            }
        }
        else if (curJoypad & J_DOWN)
        {
            if (player.xSpr != BOTTOM_BOUND)
            {
                player.xVel = 0;
                player.yVel = player.moveSpeed;
                player.state = PLAYER_WALKING;
                player.dir = DIR_DOWN;
            }
        }
        else if (curJoypad & J_LEFT)
        {
            if (player.xSpr != LEFT_BOUND)
            {
                player.xVel = -player.moveSpeed;
                player.yVel = 0;
                player.state = PLAYER_WALKING;
                player.dir = DIR_LEFT;
            }
        }
        else if (curJoypad & J_RIGHT)
        {
            if (player.xSpr != RIGHT_BOUND)
            {
                player.xVel = player.moveSpeed;
                player.yVel = 0;
                player.state = PLAYER_WALKING;
                player.dir = DIR_RIGHT;
            }
        }

        else if (player.state == PLAYER_WALKING && !(curJoypad & 0x00001111))
        {
            player.state = PLAYER_IDLE;
            player.xVel = 0;
            player.yVel = 0;
        }
    }

}


/******************************** HELPER METHODS *********************************/
static void calcPhysics()
{
    // Hypothetical coords that include velocity changes
    INT16 x = player.xSpr + player.xVel;
    INT16 y = player.ySpr + player.yVel;

    UINT8 topOffset = 8U;
    UINT8 bottomOffset = 1U;
    UINT8 leftOffset = 4U;
    UINT8 rightOffset = 5U;

    UINT8 playerTopMetatileIndex = pxToMetatile(subPxToPx(y) - 16U + topOffset);
    UINT8 playerBottomMetatileIndex = pxToMetatile(subPxToPx(y));
    k = playerBottomMetatileIndex;
    UINT8 playerLeftMetatileIndex = pxToMetatile(subPxToPx(x) - 8U + leftOffset);
    UINT8 playerRightMetatileIndex = pxToMetatile(subPxToPx(x) + 8U - rightOffset);

// set_bkg_tile_xy(8,8,subPxToPx(y));
// set_bkg_tile_xy(8,9,pxToMetatile(subPxToPx(y)));
// set_bkg_tile_xy(8,10,pxToMetatile(subPxToPx(y) - bottomOffset));

    UINT8 collided = TRUE;
    switch (player.dir)
    {
        case DIR_UP:
            if ((playGrid[playerTopMetatileIndex][playerLeftMetatileIndex] < walkableTileCount)
             && (playGrid[playerTopMetatileIndex][playerRightMetatileIndex] < walkableTileCount))
                collided = FALSE;
            break;
        case DIR_DOWN:
            if ((playGrid[playerBottomMetatileIndex][playerLeftMetatileIndex] < walkableTileCount)
             && (playGrid[playerBottomMetatileIndex][playerRightMetatileIndex] < walkableTileCount))
                collided = FALSE;
            break;
        case DIR_LEFT:
            if ((playGrid[playerTopMetatileIndex][playerLeftMetatileIndex] < walkableTileCount)
             && (playGrid[playerBottomMetatileIndex][playerLeftMetatileIndex] < walkableTileCount))
                collided = FALSE;
            break;
        case DIR_RIGHT:
            if ((playGrid[playerTopMetatileIndex][playerRightMetatileIndex] < walkableTileCount)
             && (playGrid[playerBottomMetatileIndex][playerRightMetatileIndex] < walkableTileCount))
                collided = FALSE;
            break;
    }


    // Check for left wall collisions
    i = pxToMetatile(subPxToPx(x) - 8U);
    j = pxToMetatile(subPxToPx(y) - 16U);
    set_bkg_tile_xy(0,0,i);
    set_bkg_tile_xy(1,0,j);


set_bkg_tile_xy(1,5, playerTopMetatileIndex);
set_bkg_tile_xy(1,7, playerBottomMetatileIndex);
set_bkg_tile_xy(0,6, playerLeftMetatileIndex);
set_bkg_tile_xy(2,6, playerRightMetatileIndex);

    if (collided == FALSE)
    {
        player.xSpr = x;
        player.ySpr = y;
    }
    else
    {
        switch (player.dir)
        {
            case DIR_UP:    player.ySpr = pxToSubpx(metatileToPx(playerTopMetatileIndex + 1U) + topOffset);   break;
            case DIR_DOWN:  player.ySpr = pxToSubpx(metatileToPx(k) - bottomOffset);  break;
            case DIR_LEFT:  player.xSpr = pxToSubpx(metatileToPx(playerLeftMetatileIndex + 1U) + leftOffset); break;
            case DIR_RIGHT: player.xSpr = pxToSubpx(metatileToPx(playerRightMetatileIndex) - leftOffset);     break;
            default: break;
        }

        player.xVel = 0U;
        player.yVel = 0U;
    }
}

static void commonInit()
{
    // Screen initializations
    init_bkg(0U);
    for (i = 0U; i != 39U; ++i)
        move_sprite(i, 0U, 0U);

    // Initializations
    animTick = 0U;
    playerstate = PLAYER_IDLE;

    player.xSpr = player.xTile * 64U + 32U;
    player.ySpr = player.yTile * 64U + 64U;

    // Load graphics
    set_sprite_data(OBAKE_BKG_INDEX, 16U, GhostTiles); 
    set_bkg_data(0x60U, 128U, HouseTiles);
    set_bkg_data(0x00U, 10U, fontTiles);
    set_sprite_data(0U, 48U, owTadTiles);

    // Check levelId, pull appropriate level
    loadRoom();

    // Check player coords/dir, draw player appropriately
    SCX_REG = camera_x; SCY_REG = camera_y;

    // Load room map into playGrid
    // loadMapDataFromDatabase(room.roomId, gridW, gridH);
    loadMapDataFromDatabase(0U, gridW, gridH);

    // Draw grid
    for (i = 0U; i != 10U; i++)
        for (j = 0U; j != 9U; j++)
            // drawBkgTile(((i<<1U))%32U, ((j<<1U))%32U, playGrid[j][i]);
            drawBkgTile((map_pos_x+(i<<1U))%32U, (map_pos_y+(j<<1U))%32U, playGrid[(map_pos_y>>1U)+j][(map_pos_x>>1U)+i]);    

    animatePlayer();

}

static void loadRoom()
{
    // roomId = ???;
    roomId = 0U;

    gridW = getOwMapWidth(roomId);
    gridH = getOwMapHeight(roomId);
    camera_max_x = (((gridW - 20U) * 2U) + 20U) * 8U;
    camera_max_y = (((gridH - 18U) * 2U) + 18U) * 8U;
  
    // Reset camera and player position
    if (player.xTile > 5U)  // 5 is the x offset from left to center
    {
        // If on the far right side
        if (player.xTile > (gridW - 5U))  // 5 is the x offset from right to center
        {
            camera_x = camera_max_x;
            new_camera_x = camera_x;
            map_pos_x = (BYTE)(camera_x >> 3U);
            player.xSpr = pxToSubpx(PLAYER_X_RIGHT_BOUND_PX - metatileToPx(gridW - player.xTile) + 8U);
        }
        else
        {
            camera_x = (player.xTile-5U)*16U;
            if (camera_x > camera_max_x)
                camera_x = camera_max_x;
            new_camera_x = camera_x;
            map_pos_x = (BYTE)(camera_x >> 3U);
            player.xSpr = PLAYER_X_CENTER_BOUND_PX;
        }
    }
    else
    {
        map_pos_x = 0U;
        camera_x = 0U;
        new_camera_x = camera_x;
        // player.xSpr = player.xTile % 20U * 64U + 64U;  // Classic annoying padding
        player.xSpr = pxToSubpx(metatileToPx(player.xTile) + 8U);
    }
    if (player.yTile > 4)  // 4 is the y offset from top to center
    {
        // If on the far bottom
        if (player.yTile > (gridH - 5U))  // 4 is the y offset from bottom to center; - 1 extra for index adjustments
        {
            camera_y = camera_max_y;
            new_camera_y = camera_y;
            map_pos_y = (BYTE)(camera_y >> 3U);
            // player.ySpr = PLAYER_Y_DOWN - ((gridH - player.yTile) * 64U) + 128U;  // Classic annoying padding
            player.ySpr = pxToSubpx(PLAYER_Y_DOWN_BOUND_PX - metatileToPx(gridH - player.yTile) + 16U);
        }
        else
        {
            camera_y = (player.yTile-4U)*16U;
            if (camera_y > camera_max_y)
                camera_y = camera_max_y;
            new_camera_y = camera_y;
            map_pos_y = (BYTE)(camera_y >> 3U);
            player.ySpr = PLAYER_Y_CENTER_BOUND_PX;
        }
    }
    else
    {
        map_pos_y = 0U;
        camera_y = 0U;
        new_camera_y = camera_y;
        // player.ySpr = player.yTile % 18U * 64U + 128U;  // Classic annoying padding
        player.ySpr = pxToSubpx(metatileToPx(player.yTile) + 16U);
    }
}


/******************************** DISPLAY METHODS ********************************/
static void animatePlayer()
{
    // if (shouldHidePlayer == FALSE)
    // {

        // animFrame = animTick % 16U;
        //     animFrame /= 8U;

        switch (player.state)
        {
            default:
                animFrame = 1U;
                animFrame += (player.dir >> 2U);
                break;
            case PLAYER_WALKING:
                animFrame = animTick % 32U;
                animFrame /= 8U;
                if (animFrame == 3U)
                    animFrame = 1U;
                animFrame += (player.dir >> 2U);
                break;
        }
        animFrame <<= 2U;

        // move_sprite(0U, (player.xSpr >> 2U) +  8U, (player.ySpr >> 2U) + 16U);
        // move_sprite(1U, (player.xSpr >> 2U) + 16U, (player.ySpr >> 2U) + 16U);
        move_sprite(0U, subPxToPx(player.xSpr),      subPxToPx(player.ySpr));
        move_sprite(1U, subPxToPx(player.xSpr) + 8U, subPxToPx(player.ySpr));

        set_sprite_tile(0U, 0U + animFrame);
        set_sprite_tile(1U, 2U + animFrame);

    // }
    // else
    // {
    //     move_sprite(0U, 0U, 0U);
    //     move_sprite(1U, 0U, 0U);
    // }
}

static void drawNewBkg()
{
    // Vertical
    new_map_pos_y = (BYTE)(new_camera_y >> 3U);
    if (map_pos_y != new_map_pos_y) { 
        if (new_camera_y < camera_y) 
        {
            for (k = 0U; k != 10U; ++k)
            {
                drawBkgTile((map_pos_x+(k<<1U))%32U, new_map_pos_y%32U, playGrid[new_map_pos_y>>1U][(map_pos_x>>1U)+k]);
            }
        } else
        {
            for (UINT8 k = 0U; k != 10U; ++k)
            {
                drawBkgTile((map_pos_x+(k<<1U))%32U, (new_map_pos_y+16U)%32U, playGrid[((new_map_pos_y+16U)>>1U)][(map_pos_x>>1U)+k]);
            }
        }
        map_pos_y = new_map_pos_y; 
    }
  
    // Horizontal 
    new_map_pos_x = (BYTE)(new_camera_x >> 3U);
    if (map_pos_x != new_map_pos_x) {
        if (new_camera_x < camera_x) 
        {
            for (UINT8 k = 0U; k != 9U; ++k)
            {
                drawBkgTile(new_map_pos_x%32U, (map_pos_y+(k<<1U))%32U, playGrid[(map_pos_y>>1U)+k][new_map_pos_x>>1U]);
            }
        } else 
        {
            for (UINT8 k = 0U; k != 9U; ++k)
            {
                drawBkgTile((new_map_pos_x + 18U)%32U, (map_pos_y+(k<<1U))%32U, playGrid[(map_pos_y>>1U)+k][(new_map_pos_x+18U)>>1U]);
            }
        }
        map_pos_x = new_map_pos_x;
    }
}

static void drawBkgTile(UINT8 x, UINT8 y, UINT8 tileIndex)
{
    set_bkg_tiles(x, y, 2U, 2U, YaMetaTiles[tileIndex]);
    // set_bkg_tile_xy(x, y, tileIndex);
}

// static void showOrHideEntities()
// {
//     UINT8 upperBound = camera_y - 16U;
//     UINT8 lowerBound = upperBound + 144U;
//     for (i = 0U; i != 24U; ++i)
//     {
//         if (entityList[i].id != 0xFF)
//         {
//             if (entityList[i].ySpr > upperBound || entityList[i].ySpr < lowerBound)
//                 entityList[i].visible = FALSE;
//             else
//                 entityList[i].visible = TRUE;
//         }

//         if (entityList[i].visible == TRUE)
//         {
//             move_sprite((entityList[i].id * 2U) + 2U, entityList[i].x, entityList[i].ySpr - camera_y);
//             move_sprite((entityList[i].id * 2U) + 3U, entityList[i].x + 8U, entityList[i].ySpr - camera_y);
//         }
//     }
// }
