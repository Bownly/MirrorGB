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
#include "../Assets/Tiles/HUD.h"

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
extern UINT8 (*playGridPtr)[32U][32U];
extern UINT8 playGrid[32U][32U];
extern UINT8 playGridM[32U][32U];

// static UINT8 entityGrid[32U][32U];  // Holds IDs of entities
static EntityObject entityList[24U];
static UINT8 headCount;

static const UINT8 hudMouthMap[8U] = {0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7};

#define STARTPOS 0U
#define STARTCAM 0U

static UINT8 roomId;
static UINT8 gridW;
static UINT8 gridH;
static UINT16 camera_max_x = 10U * 128U;
static UINT16 camera_max_y = 9U * 128U;
static UINT8 walkableTileCount = 6U;


// current and new positions of the camera in pixels
static WORD camera_x = STARTCAM, camera_y = STARTCAM, new_camera_x = STARTCAM, new_camera_y = STARTCAM;
// current and new position of the map in tiles
static UBYTE map_pos_x = STARTPOS, map_pos_y = STARTPOS, new_map_pos_x = STARTPOS, new_map_pos_y = STARTPOS;
static UBYTE oldTileX, oldTileY;
// redraw flag, indicates that camera position was changed
static UBYTE redraw;

#define PLAYER_X_LEFT_BOUND_PX   0U
#define PLAYER_X_CENTER_BOUND_PX 72U
#define PLAYER_X_RIGHT_BOUND_PX  160U
#define PLAYER_Y_UPPER_BOUND_PX     0U
#define PLAYER_Y_CENTER_BOUND_PX 64U
#define PLAYER_Y_LOWER_BOUND_PX   144U
#define PLAYER_X_LEFT   16U
#define PLAYER_X_CENTER 88U
#define PLAYER_X_RIGHT  160U
#define PLAYER_Y_UP     24U
#define PLAYER_Y_CENTER 80U
#define PLAYER_Y_DOWN   152U
#define PLAYER_SPEED    2
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
static void phaseInit(void);
static void phaseLoop(void);

/* INPUT METHODS */
static void inputs(void);

/* HELPER METHODS */
static void calcPhysics(void);
static void commonInit(void);
static void checkUnderfootTile(void);
static void loadLevel(void);
static void loadRoom(UINT8);
static void walkPlayer(void);

/* DISPLAY METHODS */
static void animatePlayer(void);
static void displayHealthPips(void);
static void displayHeadcount(void);
static void drawNewBkg(void);
static void drawBkgTile(UINT8, UINT8, UINT8);
// static void showOrHideEntities();


void LevelStateMain(void)
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
static void phaseInit(void)
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

    playGridPtr = &playGrid;
    commonInit();

    substate = SUB_LOOP;

    player.moveSpeed = PLAYER_SPEED;
    set_bkg_tile_xy(18U,17U,player.moveSpeed/10U);
    set_bkg_tile_xy(19U,17U,player.moveSpeed%10U);

    // fadein();
    OBP0_REG = DMG_PALETTE(DMG_LITE_GRAY, DMG_WHITE, DMG_LITE_GRAY, DMG_BLACK);
}

static void phaseLoop(void)
{
    // shouldHidePlayer = FALSE;
    ++animTick;

    // Player movements and inputs
    if (playerstate == PLAYER_WALKING)
        walkPlayer();

    // Need to recheck playerstate because the previous fn might have changed it
    if (playerstate == PLAYER_IDLE)
        inputs();

    animatePlayer();

    if (redraw && playerstate == PLAYER_WALKING)
    {
        // wait_vbl_done();
        drawNewBkg();
        redraw = FALSE;
    }
    // else
    //     wait_vbl_done();
}


/******************************** INPUT METHODS *********************************/
static void inputs(void)
{    
    if (playerstate == PLAYER_IDLE)
    {
        if (curJoypad & J_A && !(prevJoypad & J_A))
        {
            player.xTile = 31U - player.xTile;
            if (roomId % 2U == 0U)  // Normal world
            {
                ++roomId;
                playGridPtr = &playGridM;
            }
            else  // Mirror world
            {
                --roomId;
                playGridPtr = &playGrid;
            }
            loadRoom(roomId);

            return;
        }


        if (curJoypad & J_UP)
        {
            player.dir = DIR_UP;

            if (player.ySpr != 0U && (*playGridPtr)[player.yTile-1U][player.xTile] < walkableTileCount)
            {
                // Move sprite, not camera
                if (camera_y == 0U || player.ySpr > PLAYER_Y_CENTER)
                {
                    if (player.ySpr != PLAYER_Y_UP)
                    {
                        playerstate = PLAYER_WALKING;
                    }
                }
                else  // Move camera
                {
                    new_camera_y -= 16;
                    playerstate = PLAYER_WALKING;
                    redraw = TRUE;
                }
            }
        }
        else if (curJoypad & J_DOWN)
        {
            player.dir = DIR_DOWN;

            if (player.ySpr != 0U && (*playGridPtr)[player.yTile+1U][player.xTile] < walkableTileCount)
            {
                // Move sprite, not camera
                if (camera_y == camera_max_y || player.ySpr < PLAYER_Y_CENTER)
                {
                    if (player.ySpr != PLAYER_Y_DOWN)
                    {
                        playerstate = PLAYER_WALKING;
                    }
                }
                else  // Move camera
                {
                    new_camera_y += 16;
                    playerstate = PLAYER_WALKING;
                    redraw = TRUE;
                }
            }
        } 
        else if (curJoypad & J_LEFT)
        {
            player.dir = DIR_LEFT;

            if (player.ySpr != 0U && (*playGridPtr)[player.yTile][player.xTile-1U] < walkableTileCount)
            {
                // Move sprite, not camera
                if (camera_x == 0U || player.xSpr > PLAYER_X_CENTER)
                {
                    if (player.xSpr != PLAYER_X_LEFT)
                    {
                        playerstate = PLAYER_WALKING;
                    }
                }
                else  // Move camera
                {
                    new_camera_x -= 16;
                    playerstate = PLAYER_WALKING;
                    redraw = TRUE;
                }
            }
        }
        else if (curJoypad & J_RIGHT)
        {
            player.dir = DIR_RIGHT;

            if (player.ySpr != 0U && (*playGridPtr)[player.yTile][player.xTile+1U] < walkableTileCount)
            {
                // Move sprite, not camera
                if (camera_x == camera_max_x || player.xSpr < PLAYER_X_CENTER)
                {
                    if (player.xSpr != PLAYER_X_RIGHT)
                    {
                        playerstate = PLAYER_WALKING;
                    }
                }
                else  // Move camera
                {
                    new_camera_x += 16;
                    playerstate = PLAYER_WALKING;
                    redraw = TRUE;
                }
            }
        }
    }
}


/******************************** HELPER METHODS *********************************/
static void fillerFn1(void)
{
    // static void calcPhysics(void)
    // {
    //     UINT8 x = player.xSpr;
    //     UINT8 y = player.ySpr;

    //     if (player.state == PLAYER_WALKING)
    //     {
    //         // Compare movement to animation frames...
    //         if (player.animFrame == 3U || player.animFrame == 6U || player.animFrame == 9U || player.animFrame == 12U)
    //         {
    //             // Don't move during this frame
    //         }
    //         else
    //         {
    //             x += player.xVel;
    //             y += player.yVel;
    //         }

    //         // Increment frame count
    //         player.animFrame++;
            
    //         // Roll around after max frame
    //         player.animFrame %= 8U;
    //     }


    //     UINT8 topOffset = 8;
    //     UINT8 bottomOffset = 1;
    //     UINT8 leftOffset = 4;
    //     UINT8 rightOffset = 5;

    //     UINT8 playerTopMetatileIndex = pxToMetatile(y - 16U + topOffset);
    //     UINT8 playerBottomMetatileIndex = pxToMetatile(y - bottomOffset);
    //     UINT8 playerLeftMetatileIndex = pxToMetatile(x - 8U + leftOffset);
    //     UINT8 playerRightMetatileIndex = pxToMetatile(x + 8U - rightOffset);

    //     UINT8 collided = TRUE;
    //     switch (player.dir)
    //     {
    //         case DIR_UP:
    //             if ((playGrid[playerTopMetatileIndex][playerLeftMetatileIndex] < walkableTileCount)
    //             && (playGrid[playerTopMetatileIndex][playerRightMetatileIndex] < walkableTileCount))
    //                 collided = FALSE;
    //             break;
    //         case DIR_DOWN:
    //             if ((playGrid[playerBottomMetatileIndex][playerLeftMetatileIndex] < walkableTileCount)
    //             && (playGrid[playerBottomMetatileIndex][playerRightMetatileIndex] < walkableTileCount))
    //                 collided = FALSE;
    //             break;
    //         case DIR_LEFT:
    //             if ((playGrid[playerTopMetatileIndex][playerLeftMetatileIndex] < walkableTileCount)
    //             && (playGrid[playerBottomMetatileIndex][playerLeftMetatileIndex] < walkableTileCount))
    //                 collided = FALSE;
    //             break;
    //         case DIR_RIGHT:
    //             if ((playGrid[playerTopMetatileIndex][playerRightMetatileIndex] < walkableTileCount)
    //             && (playGrid[playerBottomMetatileIndex][playerRightMetatileIndex] < walkableTileCount))
    //                 collided = FALSE;
    //             break;
    //     }

    //     if (collided == FALSE)
    //     {
    //         UINT8 shouldMoveSprite = TRUE;  // TRUE = sprite move; FALSE = screen scroll

    //             set_bkg_tile_xy(2,2,player.ySpr%10);
    //             set_bkg_tile_xy(1,2,player.ySpr/10);
    //         if (player.dir == DIR_DOWN)
    //         {
    //             set_bkg_tile_xy(2,2,0x09);
    //             // Move sprite, not camera
    //             if (camera_y == camera_max_y || player.ySpr < PLAYER_Y_CENTER_BOUND_PX)
    //             {
    //             set_bkg_tile_xy(2,2,0x0A);
    //                 if (player.ySpr != PLAYER_Y_LOWER_BOUND_PX)
    //                 {

    //                     shouldMoveSprite = TRUE;
    //             set_bkg_tile_xy(2,2,0x0F);
    //                 }
    //             }
    //             else  // Move camera
    //             {
    //             set_bkg_tile_xy(2,2,0x0B);

    //                 shouldMoveSprite = FALSE;
    //             }

    //         }

    //         if (shouldMoveSprite == TRUE)
    //         {
    //             set_bkg_tile_xy(2,2,0x0C);
    //             player.xSpr = x;
    //             player.ySpr = y;
    //         }
    //         else
    //         {
    //             set_bkg_tile_xy(2,2,0x0D);
    //             // new_camera_x = subPxToPx(player.xSpr);
    //             // camera_x += player.xVel;
    //             // camera_y += player.yVel;
    //             new_camera_x += player.xVel;
    //             new_camera_y += player.yVel;
    //             redraw = TRUE;
    //             if ((new_camera_y % 16U) == 0U)
    //             {
    //                 set_bkg_tile_xy(2,2,new_camera_y%16);
    //             }
    //         }
    //         player.xMapPos += player.xVel;
    //         player.yMapPos += player.yVel;
    //         player.xTile = player.xMapPos >> 4U;
    //         player.yTile = player.yMapPos >> 4U;
    //     }
    //     else
    //     {
    //         // switch (player.dir)
    //         // {
    //         //     case DIR_UP:    player.ySpr = pxToSubpx(metatileToPx(playerTopMetatileIndex + 1U) + topOffset);   break;
    //         //     case DIR_DOWN:  player.ySpr = pxToSubpx(metatileToPx(playerBottomMetatileIndex) - bottomOffset);  break;
    //         //     case DIR_LEFT:  player.xSpr = pxToSubpx(metatileToPx(playerLeftMetatileIndex + 1U) + leftOffset); break;
    //         //     case DIR_RIGHT: player.xSpr = pxToSubpx(metatileToPx(playerRightMetatileIndex) - leftOffset);     break;
    //         //     default: break;
    //         // }

    //         player.xVel = 0U;
    //         player.yVel = 0U;
    //     }
    // }
}

static void checkUnderfootTile(void)
{
    playerstate = PLAYER_IDLE;
}

static void commonInit(void)
{
    // Screen initializations
    init_bkg(0U);
    for (i = 0U; i != 39U; ++i)
        move_sprite(i, 0U, 0U);

    // Initializations
    animTick = 0U;
    playerstate = PLAYER_IDLE;

    player.xSpr = player.xTile * 16U + 8U;
    player.ySpr = player.yTile * 16U + 16U;
    player.xMapPos = player.xTile * 16U;
    player.yMapPos = player.yTile * 16U;
    player.hpMax = 16U;
    player.hpCur = 16U;

    // Load graphics
    set_sprite_data(OBAKE_BKG_INDEX, 16U, GhostTiles); 
    set_bkg_data(0x60U, 128U, HouseTiles);
    set_bkg_data(0x00U, 40U, fontTiles);
    set_bkg_data(0xF0U, HUD_tileset_size-1, HUD_tileset + 16U);
    set_sprite_data(0U, 48U, owTadTiles);

    // HUD
    SHOW_WIN;
    move_win(7U, 128U);
    set_win_tiles(0U, 0U, 4U, 2U, hudMouthMap);
    displayHealthPips();
    displayHeadcount();
    headCount = 8U;

    // Check levelId, pull appropriate level
    loadRoom(0U);

    // Check player coords/dir, draw player appropriately
    SCX_REG = camera_x; SCY_REG = camera_y;
    oldTileX = player.xTile;
    oldTileY = player.yTile;

    animatePlayer();
}

static void loadRoom(UINT8 id)
{
    roomId = id;

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
            player.xSpr = PLAYER_X_RIGHT_BOUND_PX - metatileToPx(gridW - player.xTile) + 8U;
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
        player.xSpr = metatileToPx(player.xTile) + 8U;
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
            player.ySpr = PLAYER_Y_LOWER_BOUND_PX - metatileToPx(gridH - player.yTile) + 16U;
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
        player.ySpr = metatileToPx(player.yTile) + 16U;
    }

    // Load room map into playGrid
    loadMapDataFromDatabase(&(playGridPtr[0][0]), roomId, gridW, gridH);

    // Draw grid
    for (i = 0U; i != 10U; i++)
        for (j = 0U; j != 9U; j++)
            // drawBkgTile(((i<<1U))%32U, ((j<<1U))%32U, playGrid[j][i]);
            drawBkgTile((map_pos_x+(i<<1U))%32U, (map_pos_y+(j<<1U))%32U, (*playGridPtr)[(map_pos_y>>1U)+j][(map_pos_x>>1U)+i]);

    SCX_REG = camera_x; SCY_REG = camera_y;
}

static void walkPlayer(void)
{
    if (player.dir == DIR_UP)
    {
        if (camera_y == 0U || player.ySpr != PLAYER_Y_CENTER)
        {
            player.ySpr -= PLAYER_SPEED;
            if ((player.ySpr) % 16U == 0U)
            {
                player.yTile--;
                checkUnderfootTile();
            }
        }
        else
        {
            camera_y -= PLAYER_SPEED;
            if (camera_y % 16U == 0U)
            {
                player.yTile--;
                checkUnderfootTile();
            }
        }
    }
    else if (player.dir == DIR_DOWN)
    {
        if (camera_y == camera_max_y || player.ySpr != PLAYER_Y_CENTER)
        {
            player.ySpr += PLAYER_SPEED;
            if ((player.ySpr) % 16U == 0U)
            {
                player.yTile++;
                checkUnderfootTile();
            }
        }
        else
        {
            camera_y += PLAYER_SPEED;
            if (camera_y % 16U == 0U)
            {
                player.yTile++;
                checkUnderfootTile();
            }
        }
    }
    else if (player.dir == DIR_LEFT)
    {
        if (camera_x == 0U || player.xSpr != PLAYER_X_CENTER)
        {
            player.xSpr -= PLAYER_SPEED;
            if ((player.xSpr + 8U) % 16U == 0U)
            {
                player.xTile--;
                checkUnderfootTile();
            }
        }
        else
        {
            camera_x -= PLAYER_SPEED;
            if (camera_x % 16U == 0U)
            {
                player.xTile--;
                checkUnderfootTile();
            }
        }
    }
    else if (player.dir == DIR_RIGHT)
    {
        if (camera_x == camera_max_x || player.xSpr != PLAYER_X_CENTER)
        {
            player.xSpr += PLAYER_SPEED;
            if ((player.xSpr + 8U) % 16U == 0U)
            {
                player.xTile++;
                checkUnderfootTile();
            }
        }
        else
        {
            camera_x += PLAYER_SPEED;
            if (camera_x % 16U == 0U)
            {
                player.xTile++;
                checkUnderfootTile();
            }
        }
    }
    SCX_REG = camera_x; SCY_REG = camera_y;
}


/******************************** DISPLAY METHODS ********************************/
static void animatePlayer(void)
{
    // if (shouldHidePlayer == FALSE)
    // {
        animFrame = animTick % 16U;
            animFrame /= 8U;

        switch (playerstate)
        {
            default:
                animFrame = 1U;
                animFrame += (player.dir >> 2U);
                break;
            case PLAYER_WALKING:
                animFrame = animTick % 16U;
                animFrame /= 4U;
                if (animFrame == 3U)
                    animFrame = 1U;
                animFrame += (player.dir >> 2U);
                break;
        }
        animFrame <<= 2U;

        move_sprite(0U, player.xSpr,      player.ySpr);
        move_sprite(1U, player.xSpr + 8U, player.ySpr);

        set_sprite_tile(0U, 0U + animFrame);
        set_sprite_tile(1U, 2U + animFrame);
    // }
    // else
    // {
    //     move_sprite(0U, 0U, 0U);
    //     move_sprite(1U, 0U, 0U);
    // }
}

static void displayHealthPips(void)
{
    k = 0U;
    for (i = 0U; i != (player.hpCur / 2U); ++i)
    {
        set_win_tile_xy(4U + i, 0U, 0xFAU);
        set_win_tile_xy(4U + i, 1U, 0xFBU);
    }
    if (player.hpCur % 2U == 1U)
    {
        set_win_tile_xy(4U + i, 0U, 0xF8U);
        set_win_tile_xy(4U + i, 1U, 0xF9U);
        i++;
    }
    for (;i != (player.hpMax / 2U); ++i)
    {
        set_win_tile_xy(4U + i, 0U, 0xFEU);
        set_win_tile_xy(4U + i, 1U, 0xFEU);
    }
}

static void displayHeadcount(void)
{
    headCount = 8U;

    k = 0U;
    for (i = 0U; i != headCount; ++i)
    {
        set_win_tile_xy(12U + i, 0U, 0xFCU);
        set_win_tile_xy(12U + i, 1U, 0xFDU);
    }
    for (;i != 8U; ++i)
    {
        set_win_tile_xy(12U + i, 0U, 0xFEU);
        set_win_tile_xy(12U + i, 1U, 0xFEU);
    }
}

static void drawNewBkg(void)
{
    // Vertical
    new_map_pos_y = (BYTE)(new_camera_y >> 3U);
    if (map_pos_y != new_map_pos_y) { 
        if (new_camera_y < camera_y) 
        {
            for (k = 0U; k != 10U; ++k)
            {
                drawBkgTile((map_pos_x+(k<<1U))%32U, new_map_pos_y%32U, (*playGridPtr)[new_map_pos_y>>1U][(map_pos_x>>1U)+k]);
            }
        } else
        {
            for (UINT8 k = 0U; k != 10U; ++k)
            {
                drawBkgTile((map_pos_x+(k<<1U))%32U, (new_map_pos_y+16U)%32U, (*playGridPtr)[((new_map_pos_y+16U)>>1U)][(map_pos_x>>1U)+k]);
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
                drawBkgTile(new_map_pos_x%32U, (map_pos_y+(k<<1U))%32U, (*playGridPtr)[(map_pos_y>>1U)+k][new_map_pos_x>>1U]);
            }
        } else 
        {
            for (UINT8 k = 0U; k != 9U; ++k)
            {
                drawBkgTile((new_map_pos_x + 18U)%32U, (map_pos_y+(k<<1U))%32U, (*playGridPtr)[(map_pos_y>>1U)+k][(new_map_pos_x+18U)>>1U]);
            }
        }
        map_pos_x = new_map_pos_x;
    }
}

static void fillerFn2(void)
{
// static void drawNewBkg(void)
// {
//     SCX_REG = camera_x; SCY_REG = camera_y;

//     // Vertical
//     // set_bkg_tile_xy(8,8,map_pos_y);
//     // set_bkg_tile_xy(8,9,new_map_pos_y);
//     // set_bkg_tile_xy(8,10,new_camera_y >> 3U);
//     set_bkg_tile_xy(8,8,player.yTile);
//     set_bkg_tile_xy(8,9,oldTileY);
//     set_bkg_tile_xy(8,10,new_camera_y >> 3U);

//     new_map_pos_y = (BYTE)(new_camera_y >> 3U);
//     // if (map_pos_y != new_map_pos_y) {
//     if (oldTileY != player.yTile) {
//         // if (new_camera_y < camera_y)
//         if (player.yTile < oldTileY)
//         {
//             set_bkg_tile_xy(3,3,0x0A);
//             for (k = 0U; k != 10U; ++k)
//             {
//                 drawBkgTile((map_pos_x+(k<<1U))%32U, new_map_pos_y%32U, playGrid[player.yTile>>1U][(player.xTile>>1U)+k]);
//             }
//         // } else if (new_camera_y > camera_y) 
//         } else if (player.yTile > oldTileY) 
//         {
//             set_bkg_tile_xy(3,3,0x0B);
//             for (UINT8 k = 0U; k != 10U; ++k)
//             {
//                 drawBkgTile((map_pos_x+(k<<1U))%32U, (new_map_pos_y+16U)%32U, playGrid[(player.yTile+16U)>>1U][(player.xTile>>1U)+k]);
//                 // drawBkgTile((map_pos_x+(k<<1U))%32U, (new_map_pos_y+16U)%32U, playGrid[((new_map_pos_y+16U)>>1U)][(map_pos_x>>1U)+k]);
//             }
//         }

//         map_pos_y = new_map_pos_y;
//         oldTileY = player.yTile; 
//     }

//     // Horizontal
//     new_map_pos_x = (BYTE)(new_camera_x >> 4U);
//     if (map_pos_x != new_map_pos_x) {
//         if (new_camera_x < camera_x) 
//         {
//             for (k = 0U; k != 9U; ++k)
//             {
//                 drawBkgTile(new_map_pos_x%32U, (map_pos_y+(k<<1U))%32U, playGrid[(map_pos_y>>1U)+k][new_map_pos_x>>1U]);
//             }
//         } else 
//         {
//             for (k = 0U; k != 9U; ++k)
//             {
//                 drawBkgTile((new_map_pos_x + 18U)%32U, (map_pos_y+(k<<1U))%32U, playGrid[(map_pos_y>>1U)+k][(new_map_pos_x+18U)>>1U]);
//             }
//         }
//         map_pos_x = new_map_pos_x;
//     }
//     // set old camera position to current camera position
//     camera_x = new_camera_x, camera_y = new_camera_y;
// }
}

static void drawBkgTile(UINT8 x, UINT8 y, UINT8 tileIndex)
{
    set_bkg_tiles(x, y, 2U, 2U, YaMetaTiles[tileIndex]);
    // set_bkg_tile_xy(x,y,x);
    // set_bkg_tile_xy(x+1,y,y);
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
