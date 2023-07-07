#include <gb/gb.h>
#include <rand.h>
#include <string.h>

#include "../Engine/common.h"
#include "../Engine/enums.h"
// #include "../Engine/fade.h"
// #include "../Engine/ram.h"
// #include "../Engine/songPlayer.h"
#include "../Engine/IShareMapData.h"

#include "../Assets/Sprites/MC.h"
#include "../Assets/Sprites/NPCgirl.h"

#include "../Assets/Tiles/HouseTiles.h"
#include "../Assets/Tiles/YaMetaTiles.h"
#include "../Assets/Tiles/fontTiles.h"
#include "../Assets/Tiles/HUD.h"

#include "../Objects/ActionObject.h"
#include "../Objects/EntityObject.h"
#include "../Objects/LevelObject.h"
#include "../Objects/RoutineObject.h"



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

extern UINT8 gamestate;
extern UINT8 substate;
// extern UINT8 currentLevel;
extern UINT8 (*playGridPtr)[32U][32U];
extern UINT8 playGrid[32U][32U];
extern UINT8 playGridM[32U][32U];

extern EntityObject player;
static EntityObject* entityPtr;
static UINT8 entityGrid[32U][32U];  // Holds IDs of entities
static EntityObject entityList[8U];
#define ENTITY_MAX 8U
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


ActionObject routine0[] = { 
                            {ACT_WALK, DIR_DOWN, 2U},
                            {ACT_WALK, DIR_RIGHT, 3U},
                            {ACT_WALK, DIR_UP, 2U},
                            {ACT_WALK, DIR_LEFT, 3U},
                            {ACT_WAIT, DIR_RIGHT, 16U}
                          };
                          #define ROUTINE_LENGTH 5U


/* SUBSTATE METHODS */
static void phaseInit(void);
static void phaseLoop(void);

/* INPUT METHODS */
static void inputs(void);

/* HELPER METHODS */
static void commonInit(void);
static void checkUnderfootTile(void);
static UINT8 entityListAdd(UINT8, UINT8, UINT8);
static void handleRoutines(void);
static void loadLevel(void);
static void loadRoom(UINT8);
static void walkPlayer(void);

/* DISPLAY METHODS */
static void animateEntities(void);
static void animatePlayer(void);
static void displayHealthPips(void);
static void displayHeadcount(void);
static void drawNewBkg(void);
static void drawBkgTile(UINT8, UINT8, UINT8);


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
    
    // Init entity stuff
    for (i = 0U; i != 8U; ++i)
        entityList[i].id = 0xFFU;
    for (i = 0U; i != 32U; ++i)
        for (j = 0U; j != 32U; ++j)
            entityGrid[j][i] = 0xFFU;

    HIDE_WIN;
    SHOW_SPRITES;
    SPRITES_8x8;

    // // Check levelId, pull appropriate level
    // loadLevel();

    player.xTile = 1U;
    player.yTile = 1U;
    player.xSpr = 88U;
    player.ySpr = 88U;
    player.dir - DIR_DOWN;

    playGridPtr = &playGridM;
    commonInit();

    set_sprite_data(0x30U, NPCgirl_TILE_COUNT, NPCgirl_tiles);

    substate = SUB_LOOP;

    player.moveSpeed = PLAYER_SPEED;

    if (entityGrid[2][4] == 0xFFU)
        entityListAdd(1, 2, 4);

    // fadein();
    OBP0_REG = DMG_PALETTE(DMG_LITE_GRAY, DMG_WHITE, DMG_LITE_GRAY, DMG_BLACK);
}

static void phaseLoop(void)
{
    // shouldHidePlayer = FALSE;
    ++animTick;

    // Player movements and inputs
    if (player.state == ENTITY_WALKING)
        walkPlayer();

    handleRoutines();

    // Need to recheck player.state because the previous fn might have changed it
    if (player.state == ENTITY_IDLE)
        inputs();

    animatePlayer();
    if (roomId % 2U == 0U)  // Don't animate entities if we're in the mirror world
        animateEntities();

    if (redraw && player.state == ENTITY_WALKING)
    {
        // wait_vbl_done();
        drawNewBkg();
        redraw = FALSE;
    }
    // else
    //     wait_vbl_done();

    // set_win_tile_xy(18,0,player.xTile/10U);
    // set_win_tile_xy(19,0,player.xTile%10U);
    // set_win_tile_xy(18,1,player.yTile/10U);
    // set_win_tile_xy(19,1,player.yTile%10U);
}


/******************************** INPUT METHODS *********************************/
static void inputs(void)
{    
    if (player.state == ENTITY_IDLE)
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
            if (player.dir == DIR_RIGHT)
                player.dir = DIR_LEFT;
            else if (player.dir == DIR_LEFT)
                player.dir = DIR_RIGHT;
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
                        player.state = ENTITY_WALKING;
                    }
                }
                else  // Move camera
                {
                    new_camera_y -= 16;
                    player.state = ENTITY_WALKING;
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
                        player.state = ENTITY_WALKING;
                    }
                }
                else  // Move camera
                {
                    new_camera_y += 16;
                    player.state = ENTITY_WALKING;
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
                        player.state = ENTITY_WALKING;
                    }
                }
                else  // Move camera
                {
                    new_camera_x -= 16;
                    player.state = ENTITY_WALKING;
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
                        player.state = ENTITY_WALKING;
                    }
                }
                else  // Move camera
                {
                    new_camera_x += 16;
                    player.state = ENTITY_WALKING;
                    redraw = TRUE;
                }
            }
        }
    }
}


/******************************** HELPER METHODS *********************************/
static void checkUnderfootTile(void)
{
    player.state = ENTITY_IDLE;
}

static void commonInit(void)
{
    // Screen initializations
    init_bkg(0U);
    for (i = 0U; i != 39U; ++i)
        move_sprite(i, 0U, 0U);

    // Initializations
    animTick = 0U;
    player.state = ENTITY_IDLE;

    player.xSpr = player.xTile * 16U + 8U;
    player.ySpr = player.yTile * 16U + 16U;
    player.hpMax = 16U;
    player.hpCur = 16U;

    // Load graphics
    set_bkg_data(0x60U, 128U, HouseTiles);
    set_bkg_data(0x00U, 40U, fontTiles);
    set_bkg_data(0xF0U, HUD_tileset_size-1U, HUD_tileset + 16U);  // Aseprite exports annoyingly have a leading blank tile
    set_sprite_data(0U, MC_TILE_COUNT, MC_tiles);

    // HUD
    SHOW_WIN;
    move_win(7U, 128U);
    set_win_tiles(0U, 0U, 4U, 2U, hudMouthMap);
    displayHealthPips();
    displayHeadcount();
    headCount = 8U;

    // Check levelId, pull appropriate level
    camera_max_x = (((gridW - 20U) * 2U) + 20U) * 8U;
    camera_max_y = (((gridH - 18U) * 2U) + 18U) * 8U;

    roomId = 1U;
    gridW = getOwMapWidth(1U);
    gridH = getOwMapHeight(1U);
    playGridPtr = &playGridM;
    loadMapDataFromDatabase(&(playGridPtr[0][0]), roomId, gridW, gridH);
    roomId = 0U;
    gridW = getOwMapWidth(0U);
    gridH = getOwMapHeight(0U);
    playGridPtr = &playGrid;
    loadMapDataFromDatabase(&(playGridPtr[0][0]), roomId, gridW, gridH);

    loadRoom(0U);

    animatePlayer();
}

static UINT8 entityListAdd(UINT8 speciesId, UINT8 tileX, UINT8 tileY)
{
    // Find the first open slot
    k = 0U;
    for (i = 0U; i != 8U; ++i)
    {
        if (entityList[i].id == 0xFFU)
        {
            k = i;
            break;  // End loop faster
        }
    }

    // Init the new entity
    entityList[k].id = k;
    entityList[k].speciesId = speciesId;
    entityList[k].state = ENTITY_IDLE;
    if (speciesId == 2U) entityList[k].state = ENTITY_DEAD;  // TODO: Temp line to create stationary entities
    entityList[k].spriteId = (k + 4U);
    entityList[k].animTick = 0U;
    entityList[k].animFrame = 0U;
    entityList[k].xSpr = (tileX * 16U) + 8U;
    entityList[k].ySpr = (tileY * 16U) + 16U;
    entityList[k].xTile = tileX;
    entityList[k].yTile = tileY;
    entityList[k].dir = DIR_DOWN;
    entityList[k].moveSpeed = 1U;
    entityList[k].hpMax = 0U;
    entityList[k].hpCur = 0U;

    set_sprite_tile((k*2U) + 2U, 12);
    set_sprite_tile((k*2U) + 3U, 14);
    move_sprite((k*2U) + 2U, entityList[k].xSpr, entityList[k].ySpr - camera_y);
    move_sprite((k*2U) + 3U, entityList[k].xSpr + 8U, entityList[k].ySpr - camera_y);

    entityGrid[tileY][tileX] = k;

    return k;
}

static void handleRoutines(void)
{
    entityPtr = entityList;
    for (i = 0U; i != ENTITY_MAX; ++i)
    {
        if (entityList[i].id != 0xFF)
        {
            switch (entityList[i].state)
            {
                case ENTITY_WAITING:
                    if (entityPtr->actionTimer == 0U)
                        entityPtr->state = ENTITY_IDLE;
                    entityPtr->actionTimer--;
                    break;
                case ENTITY_WALKING:
                    if (entityPtr->actionTimer != 0U)
                    {
                        switch (entityPtr->dir)
                        {
                            case DIR_UP:    entityPtr->ySpr -= 1U; break;
                            case DIR_DOWN:  entityPtr->ySpr += 1U; break;
                            case DIR_LEFT:  entityPtr->xSpr -= 1U; break;
                            case DIR_RIGHT: entityPtr->xSpr += 1U; break;
                        }
                    }
                    else
                        entityPtr->state = ENTITY_IDLE;
                    entityPtr->actionTimer--;
                    
                    // entityPtr->animTick++;
                    // entityPtr->animFrame = entityPtr->animTick % 16U;
                    // entityPtr->animFrame /= 8U;
                    // if (entityPtr->animFrame == 3U)
                    //     entityPtr->animFrame = 1U;
                    // entityPtr->animFrame += (entityPtr->dir >> 2U);

                    entityPtr->animTick++;
                    entityPtr->animFrame = entityPtr->animTick % 32U;
                    entityPtr->animFrame /= 8U;
                    if (entityPtr->animFrame == 3U)
                        entityPtr->animFrame = 1U;
                    if (entityPtr->dir == DIR_RIGHT)
                        entityPtr->animFrame += (entityPtr->dir - 1U) * 3U;
                    else
                        entityPtr->animFrame += entityPtr->dir * 3U;

                    break;
            }

            // This goes after the switch statement to remove the 1 frame delay between completing an action and starting a new one
            if (entityPtr->state == ENTITY_IDLE)
            {
                    // Move to next action
                    k = (entityPtr->curActionIndex) % ROUTINE_LENGTH;  // TODO: NOTE: WARNING: ACHTUNG: Swap out ROUTINE_LENGTH for variable routine length
                    entityPtr->curActionIndex = k + 1U;

                    switch (routine0[k].action)
                    {
                        case ACT_WALK:
                            entityPtr->state = ENTITY_WALKING;
                            entityPtr->dir = routine0[k].direction;
                            entityPtr->actionTimer = 16U * routine0[k].magnitude;
                            break;
                        case ACT_WAIT:
                            entityPtr->state = ENTITY_WAITING;
                            entityPtr->actionTimer = routine0[k].magnitude;
                            entityPtr->dir = routine0[k].direction;

                            if (entityPtr->dir == DIR_RIGHT)
                                entityPtr->animFrame = (entityPtr->dir - 1U) * 3U;
                            else
                                entityPtr->animFrame = entityPtr->dir * 3U;

                            break;
                    }
            }
        }
        entityPtr += sizeof(EntityObject);
    }
}

static void loadRoom(UINT8 id)
{
    roomId = id;

    camera_max_x = (((gridW - 20U) * 2U) + 20U) * 8U;
    camera_max_y = (((gridH - 18U) * 2U) + 18U) * 8U;
  
    // Reset camera and player position
    if (player.xTile > 5)  // 5 is the x offset from left to center
    {
        // If on the far right side
        if (player.xTile > (gridW - 5U))  // 5 is the x offset from right to center
        {
            camera_x = camera_max_x;
            new_camera_x = camera_x;
            map_pos_x = (BYTE)(camera_x >> 3U);
            player.xSpr = PLAYER_X_RIGHT - ((gridW - player.xTile) * 16U) + 8U;  // Classic annoying padding
        }
        else
        {
            camera_x = (player.xTile-5U)*16U;
            if (camera_x > camera_max_x)
                camera_x = camera_max_x;
            new_camera_x = camera_x;
            map_pos_x = (BYTE)(camera_x >> 3U);
            player.xSpr = PLAYER_X_CENTER;
        }
    }
    else
    {
        map_pos_x = 0U;
        camera_x = 0U;
        new_camera_x = camera_x;
        player.xSpr = player.xTile % 20U * 16U + 8U;  // Classic annoying padding
    }
    if (player.yTile > 4)  // 4 is the y offset from top to center
    {
        // If on the far bottom
        if (player.yTile > (gridH - 5U))  // 4 is the y offset from bottom to center; - 1 extra for index adjustments
        {
            camera_y = camera_max_y;
            new_camera_y = camera_y;
            map_pos_y = (BYTE)(camera_y >> 3U);
            player.ySpr = PLAYER_Y_DOWN - ((gridH - player.yTile) * 16U) + 8U;  // Classic annoying padding
        }
        else
        {
            camera_y = (player.yTile-4U)*16U;
            if (camera_y > camera_max_y)
                camera_y = camera_max_y;
            new_camera_y = camera_y;
            map_pos_y = (BYTE)(camera_y >> 3U);
            player.ySpr = PLAYER_Y_CENTER;
        }
    }
    else
    {
        map_pos_y = 0U;
        camera_y = 0U;
        new_camera_y = camera_y;
        player.ySpr = player.yTile % 18U * 16U + 16U;  // Classic annoying padding
    }


    // Draw grid
    for (i = 0U; i != 10U; i++)
        for (j = 0U; j != 9U; j++)
            drawBkgTile((map_pos_x+(i<<1U))%32U, (map_pos_y+(j<<1U))%32U, (*playGridPtr)[(map_pos_y>>1U)+j][(map_pos_x>>1U)+i]);

    // Check player coords/dir, draw player appropriately
    SCX_REG = camera_x; SCY_REG = camera_y;
    oldTileX = player.xTile;
    oldTileY = player.yTile;
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
static void animateEntities(void)
{
    UINT8 upperBound = camera_y - 16U;
    UINT8 lowerBound = upperBound + 144U;
    entityPtr = entityList;
    for (i = 0U; i != ENTITY_MAX; ++i)
    {
        if (entityList[i].id != 0xFF)
        {
            // if (entityList[i].ySpr > upperBound || entityList[i].ySpr < lowerBound)
            //     entityList[i].isVisible = FALSE;
            // else
                entityList[i].isVisible = TRUE;
        }

        if (entityList[i].isVisible == TRUE)
        {
            if (entityPtr->dir == DIR_LEFT)
                move_metasprite_vflip(NPCgirl_metasprites[entityPtr->animFrame], 0x30U, entityPtr->spriteId,
                                entityList[i].xSpr - camera_x + 8U, entityList[i].ySpr - camera_y + 6U);
            else
                move_metasprite(NPCgirl_metasprites[entityPtr->animFrame], 0x30U, entityPtr->spriteId,
                                entityList[i].xSpr - camera_x + 8U, entityList[i].ySpr - camera_y + 6U);

        }
        entityPtr += sizeof(EntityObject);
    }
}

static void animatePlayer(void)
{
    // if (shouldHidePlayer == FALSE)
    // {
        player.animTick++;
        player.animFrame = player.animTick % 32U;
        player.animFrame /= 8U;
        if (player.animFrame == 3U)
            player.animFrame = 1U;
        if (player.dir == DIR_RIGHT)
            player.animFrame += (player.dir - 1U) * 3U;
        else
            player.animFrame += player.dir * 3U;

        if (player.dir == DIR_LEFT)
            move_metasprite_vflip(MC_metasprites[player.animFrame], 0U, 0U, player.xSpr + 8U, player.ySpr + 6U);
        else
            move_metasprite(MC_metasprites[player.animFrame], 0U, 0U, player.xSpr + 8U, player.ySpr + 6U);
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

static void drawBkgTile(UINT8 x, UINT8 y, UINT8 tileIndex)
{
    set_bkg_tiles(x, y, 2U, 2U, YaMetaTiles[tileIndex]);
    // set_bkg_tile_xy(x,y,x);
    // set_bkg_tile_xy(x+1,y,y);
    // set_bkg_tile_xy(x, y, tileIndex);
}
