#include <gb/gb.h>
#include <rand.h>
#include <string.h>

#include "../Engine/common.h"
#include "../Engine/enums.h"
#include "../Engine/fade.h"
// #include "../Engine/ram.h"
#include "../Engine/songPlayer.h"
#include "../Engine/ILoadMapTileData.h"
#include "../Engine/IShareLevelData.h"
#include "../Engine/IShareMapData.h"
#include "../Engine/IShareNPCData.h"
#include "../Engine/IShareNPCGraphics.h"
#include "../Engine/IShareroutineData.h"

#include "../Assets/Sprites/HUDTeeth.h"
#include "../Assets/Sprites/MC.h"
#include "../Assets/Sprites/NPCgirl.h"

#include "../Assets/Tiles/BloodstainTiles.h"
#include "../Assets/Tiles/ExclamationTiles.h"
#include "../Assets/Tiles/fontTiles.h"
#include "../Assets/Tiles/HUD.h"

#include "../Objects/ActionObject.h"
#include "../Objects/EntityObject.h"
#include "../Objects/LevelObject.h"
#include "../Objects/NPCObject.h"
#include "../Objects/RoutineObject.h"

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
extern UINT8 metaTiles[256U][4U];
extern UINT8 handyDandyString[19U];

extern ActionObject tempAction;
extern NPCObject tempNPC;

extern EntityObject player;
static UINT16 hungerTick;
#define HUNGER_THRESHOLD 100U
static EntityObject* entityPtr;
// static UINT8 entityGrid[32U][32U];  // Holds IDs of entities
static EntityObject entityList[8U];
#define ENTITY_MAX 7U
static UINT8 headCount;

static const UINT8 hudMouthMap[8U] = {0xF0, 0xF2, 0xF4, 0xF6, 0xF1, 0xF3, 0xF5, 0xF7};

#define STARTPOS 0U
#define STARTCAM 0U

static UINT8 roomId;
static UINT8 gridW;
static UINT8 gridH;
static UINT16 camera_max_x = 10U * 128U;
static UINT16 camera_max_y = 9U * 128U;
#define WALKABLE_TILE_COUNT 32U

// current and new positions of the camera in pixels
static WORD camera_x = STARTCAM, camera_y = STARTCAM, new_camera_x = STARTCAM, new_camera_y = STARTCAM;
// current and new position of the map in tiles
static UBYTE map_pos_x = STARTPOS, map_pos_y = STARTPOS, new_map_pos_x = STARTPOS, new_map_pos_y = STARTPOS;
static UBYTE oldTileX, oldTileY;
// redraw flag, indicates that camera position was changed
static UBYTE redraw;

#define PLAYER_X_LEFT_BOUND_PX    0U
#define PLAYER_X_CENTER_BOUND_PX 72U
#define PLAYER_X_RIGHT_BOUND_PX 160U
#define PLAYER_Y_UPPER_BOUND_PX   0U
#define PLAYER_Y_CENTER_BOUND_PX 64U
#define PLAYER_Y_LOWER_BOUND_PX 144U
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

#define SPOTTED_ANIM_DURATION 60U
#define EXCLAMATION_SPR_ID 4U
#define EXCLAMATION_SPR_INDEX 0xE8U
#define BLOOD_SPR_INDEX 0xECU

#define pxToSubpx(px) ((px) << 4U)
#define subPxToPx(subpx) ((subpx) >> 4U)

#define tileToPx(tile) ((tile) << 3U)
#define pxToTile(px) ((px) >> 3U)

#define metatileToPx(metatile) ((metatile) << 4U)
#define pxToMetatile(px) ((px) >> 4U)

/* SUBSTATE METHODS */
static void phaseInit(void);
static void phaseReinit(void);
static void phaseLoop(void);
static void phaseSpotted(void);

/* INPUT METHODS */
static void inputs(void);

/* HELPER METHODS */
static UINT8 checkForEntityCollision(UINT8, UINT8);
static void commonInit(void);
static void checkUnderfootTile(void);
static void entityKill(UINT8);
static void entityListAdd(UINT8);
static void handleRoutines(void);
static void killPlayer(void);
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
        case SUB_REINIT:
            phaseReinit();
            break;
        case SUB_LOOP:
            phaseLoop();
            break;
        case SUB_SPOTTED:
            phaseSpotted();
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
    // 1st time init stuff
    // Init entityList
    // Init player stats
    player.lives = 3U;
    // Init level flags
    // Load play grids
    // Load entity sprite data
    // Load player sprite data

    // Init entity stuff
    for (i = 0U; i != ENTITY_MAX; ++i)
        entityList[i].id = 0xFFU;

    for (i = 0U; i != 6U; ++i)
    {
        getNPCData(i);
        entityListAdd(i);
    }

    HIDE_WIN;
    SHOW_SPRITES;
    SPRITES_8x8;

    // // Check levelId, pull appropriate level
    // loadLevel();

    commonInit();
    playOutsideSong(SONG_HOUSE);

}

static void phaseReinit(void)
{

    // Reinit stuff
    // Relocate player and entities
    // Load appropriate teeth graphics

    // // Init entity stuff
    // for (i = 0U; i != 8U; ++i)
    //     entityList[i].id = 0xFFU;

    commonInit();

}

static void phaseLoop(void)
{
    // shouldHidePlayer = FALSE;
    ++animTick;

    // Hunger logic
    ++hungerTick;
    if (hungerTick == HUNGER_THRESHOLD)
    {
        player.hpCur--;
        displayHealthPips();
        hungerTick = 0U;

        if (player.hpCur == 0U)
        {
            killPlayer();
            return;
        }
    }

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
        drawNewBkg();
        redraw = FALSE;
    }

}

static void phaseSpotted(void)
{
    if (animTick == 0U)
    {
        set_win_tile_xy(0,0,0xFF);
        set_sprite_tile(EXCLAMATION_SPR_ID,      EXCLAMATION_SPR_INDEX);
        set_sprite_tile(EXCLAMATION_SPR_ID + 1U, EXCLAMATION_SPR_INDEX + 1U);
        set_sprite_tile(EXCLAMATION_SPR_ID + 2U, EXCLAMATION_SPR_INDEX);
        set_sprite_tile(EXCLAMATION_SPR_ID + 3U, EXCLAMATION_SPR_INDEX + 1U);
        set_sprite_prop(EXCLAMATION_SPR_ID + 2U, 0b00100000U);
        set_sprite_prop(EXCLAMATION_SPR_ID + 3U, 0b00100000U);

        UINT8 xPad = 0U;
        if (entityList[p].yTile == player.yTile + 1U)
            xPad = 1U;

        move_sprite(EXCLAMATION_SPR_ID,      entityList[p].xSpr - camera_x - xPad,      entityList[p].ySpr - camera_y - 18U);
        move_sprite(EXCLAMATION_SPR_ID + 1U, entityList[p].xSpr - camera_x - xPad,      entityList[p].ySpr - camera_y - 10U);
        move_sprite(EXCLAMATION_SPR_ID + 2U, entityList[p].xSpr - camera_x - xPad + 8U, entityList[p].ySpr - camera_y - 18U);
        move_sprite(EXCLAMATION_SPR_ID + 3U, entityList[p].xSpr - camera_x - xPad + 8U, entityList[p].ySpr - camera_y - 10U);
        p = 0xFFU;
    }
    else if (animTick == SPOTTED_ANIM_DURATION)
    {
        killPlayer();
    }
    ++animTick;
}


/******************************** INPUT METHODS *********************************/
static void inputs(void)
{    
    if (player.state == ENTITY_IDLE)
    {
        if (curJoypad & J_A && !(prevJoypad & J_A))
        {
            //////// Mirror check
            i = player.xTile;
            j = player.yTile;

            switch (player.dir)
            {
                case DIR_UP: j -= 2U; break;
                case DIR_DOWN: ++j; break;
                case DIR_LEFT: --i; break;
                case DIR_RIGHT: ++i; break;
                default: break;
            }

            if ((*playGridPtr)[j][i] == WALKABLE_TILE_COUNT)
            {
                fadeout();
                player.xTile = 31U - player.xTile;
                if (roomId % 2U == 0U)  // Normal world
                {
                    ++roomId;
                    playGridPtr = &playGridM;

                    for (i = 0U; i != ENTITY_MAX; ++i)
                        entityList[i].isVisible = FALSE;

                    hide_sprites_range(14U, 40U);
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
            
                fadein();
                return;
            }

            //////// NPC kill check
            // We look 2 tiles upwards for mirrors, but only 1 for other interactions
            if (player.dir == DIR_UP)
                ++j;

            // Check if tile in front is an npc
            entityPtr = entityList;
            for (k = 0U; k != ENTITY_MAX; ++k)
            {
                entityPtr = &entityList[k];
                if (entityPtr->state != ENTITY_DEAD && entityPtr->xTile == i && entityPtr->yTile == j)
                {
                    entityKill(entityPtr->id);
                    player.hpCur = player.hpMax;
                    displayHealthPips();
                    hungerTick = 0U;
                }
            }
        }

        if (curJoypad & J_UP)
        {
            player.dir = DIR_UP;

            if (player.ySpr != 0U && (*playGridPtr)[player.yTile-1U][player.xTile] < WALKABLE_TILE_COUNT 
                && checkForEntityCollision(player.xTile, player.yTile - 1U) == FALSE)
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

            if (player.ySpr != 0U && (*playGridPtr)[player.yTile+1U][player.xTile] < WALKABLE_TILE_COUNT
                && checkForEntityCollision(player.xTile, player.yTile + 1U) == FALSE)
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

            if (player.ySpr != 0U && (*playGridPtr)[player.yTile][player.xTile-1U] < WALKABLE_TILE_COUNT
                && checkForEntityCollision(player.xTile - 1U, player.yTile) == FALSE)
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

            if (player.ySpr != 0U && (*playGridPtr)[player.yTile][player.xTile+1U] < WALKABLE_TILE_COUNT
                && checkForEntityCollision(player.xTile + 1U, player.yTile) == FALSE)
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
static UINT8 checkForEntityCollision(UINT8 x, UINT8 y)
{
    // Check if tile in front is an npc
    entityPtr = entityList;
    for (k = 0U; k != ENTITY_MAX; ++k)
    {
        entityPtr = &entityList[k];
        switch (entityPtr->state)
        {
            case ENTITY_IDLE:
            case ENTITY_WAITING:
                if (entityPtr->xTile == x && entityPtr->yTile == y)
                    return TRUE;
                break;
        }
    }
    return FALSE;
}

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

    // // Init entity grid
    // for (i = 0U; i != 32U; ++i)
    //     for (j = 0U; j != 32U; ++j)
    //         entityGrid[j][i] = 0xFFU;

    // Initializations
    animTick = 0U;
    player.state = ENTITY_IDLE;
    player.hpMax = 16U;
    player.hpCur = 16U;
    player.xTile = 12U;
    player.yTile = 14U;
    player.xSpr = player.xTile * 16U + 8U;
    player.ySpr = player.yTile * 16U + 16U;
    player.xSpr = 88U;
    player.ySpr = 88U;
    player.dir - DIR_DOWN;
    hungerTick = 0U;
    camera_x = STARTCAM, camera_y = STARTCAM, new_camera_x = STARTCAM, new_camera_y = STARTCAM;
    map_pos_x = STARTPOS, map_pos_y = STARTPOS, new_map_pos_x = STARTPOS, new_map_pos_y = STARTPOS;
    playGridPtr = &playGridM;

    // Load graphics
    set_bkg_data(0x00U, 10U, fontTiles);
    set_bkg_data(0xF0U, HUD_tileset_size-1U, HUD_tileset + 16U);  // Aseprite exports annoyingly have a leading blank tile
    set_sprite_data(0U, MC_TILE_COUNT, MC_tiles);
    set_bkg_data(0xF0U, 8U, HUDTeeth_tiles + ((3U - player.lives) * 128));
    set_sprite_data(BLOOD_SPR_INDEX, 4U, BloodstainTiles);
    set_sprite_data(EXCLAMATION_SPR_INDEX, 2U, ExclamationTiles);

    // HUD sprites meant to hide NPCs when walking N and S
    for (i = 4U; i != 14U; i++)
    {
        set_sprite_tile(i, 0xA5U);
        move_sprite(i, 0U, 144U);
    }

    // HUD
    SHOW_WIN;
    move_win(7U, 128U);
    set_win_tiles(0U, 0U, 4U, 2U, hudMouthMap);
    displayHealthPips();


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

    UINT8 junkvar = 0x30U;
    loadLevelNPCSpeciesList(roomId);
    for (i = 0U; i != 8U; ++i)  // Note: 8U is the size of a LevelObject's npcSpecies list
    {
        if (handyDandyString[i] != 0xFF)
            junkvar += loadNPCSpriteTiles(handyDandyString[i], junkvar);
    }
    
    headCount = 0U;
    for (i = 0U; i != ENTITY_MAX; ++i)
    {
        if (entityList[i].id != 0xFF)
        {
            if (entityList[i].state != ENTITY_DEAD)
            {
                getNPCData(i);
                entityListAdd(i);
            }
        }
    }

    displayHeadcount();

    substate = SUB_LOOP;

    player.moveSpeed = PLAYER_SPEED;

    fadein();
    OBP0_REG = DMG_PALETTE(DMG_LITE_GRAY, DMG_WHITE, DMG_LITE_GRAY, DMG_BLACK);
    substate = SUB_LOOP;
}

static void entityKill(UINT8 entityId)
{
    entityList[entityId].state = ENTITY_DEAD;
    set_sprite_tile(entityList[entityId].spriteId,      BLOOD_SPR_INDEX);
    set_sprite_tile(entityList[entityId].spriteId + 1U, BLOOD_SPR_INDEX + 1U);
    set_sprite_tile(entityList[entityId].spriteId + 2U, BLOOD_SPR_INDEX + 2U);
    set_sprite_tile(entityList[entityId].spriteId + 3U, BLOOD_SPR_INDEX + 3U);
    set_sprite_prop(entityList[entityId].spriteId,      0b00011000U);
    set_sprite_prop(entityList[entityId].spriteId + 1U, 0b00011000U);
    set_sprite_prop(entityList[entityId].spriteId + 2U, 0b00011000U);
    set_sprite_prop(entityList[entityId].spriteId + 3U, 0b00011000U);

    --headCount;
    displayHeadcount();
}

static void entityListAdd(UINT8 id)
{
    // Init the new entity
    entityList[id].id = id;
    entityList[id].speciesId = tempNPC.speciesId;
    entityList[id].state = ENTITY_IDLE;
    entityList[id].spriteId = ((id + 1U) * 4U) + 10U;  // The 10 padding is for the HUD sprites
    entityList[id].animTick = 0U;
    entityList[id].animFrame = 0U;
    entityList[id].actionTimer = 0U;
    entityList[id].curActionIndex = 0U;
    entityList[id].curRoutineIndex = tempNPC.routineId;
    entityList[id].xTile = tempNPC.xTile;
    entityList[id].yTile = tempNPC.yTile;
    entityList[id].xSpr = (tempNPC.xTile * 16U) + 8U;
    entityList[id].ySpr = (tempNPC.yTile * 16U) + 16U;
    entityList[id].dir = DIR_DOWN;
    entityList[id].moveSpeed = 1U;
    entityList[id].visionDistance = 3U;
    entityList[id].hpMax = 0U;
    entityList[id].hpCur = 0U;

    ++headCount;
}

static void handleRoutines(void)
{
    entityPtr = entityList;
    for (k = 0U; k != ENTITY_MAX; ++k)
    {
        entityPtr = &entityList[k];
        if (entityPtr->id != 0xFF)
        {
            // Run action logic
            switch (entityPtr->state)
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
                        entityPtr->xTile = (entityPtr->xSpr - 8U) >> 4U;
                        entityPtr->yTile = (entityPtr->ySpr - 16U) >> 4U;
                    }
                    else
                        entityPtr->state = ENTITY_IDLE;
                    entityPtr->actionTimer--;
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
                case ENTITY_TOGGLING_HIDE:
                    entityPtr->isHiding = entityPtr->isHiding == TRUE ? FALSE : TRUE; 
                    entityPtr->state = ENTITY_IDLE;
                    break;
                default:
                    break;
            }

            // Pick up a new action if just finished an action
            if (entityPtr->state == ENTITY_IDLE)
            {
                // Get next action
                entityPtr->curActionIndex = getAction(entityPtr->curRoutineIndex, entityPtr->curActionIndex);

                switch (tempAction.action)
                {
                    case ACT_WALK:
                        entityPtr->state = ENTITY_WALKING;
                        entityPtr->dir = tempAction.direction;
                        entityPtr->actionTimer = 16U * tempAction.magnitude;

                        if (entityPtr->dir == DIR_RIGHT)
                            entityPtr->animFrame = (entityPtr->dir - 1U) * 3U;
                        else
                            entityPtr->animFrame = entityPtr->dir * 3U;
                        break;
                    case ACT_WAIT:
                        entityPtr->state = ENTITY_WAITING;
                        entityPtr->actionTimer = tempAction.magnitude;
                        entityPtr->dir = tempAction.direction;

                        if (entityPtr->dir == DIR_RIGHT)
                            entityPtr->animFrame = (entityPtr->dir - 1U) * 3U;
                        else
                            entityPtr->animFrame = entityPtr->dir * 3U;
                        break;
                    case ACT_TOGGLE_HIDING:
                        entityPtr->state = ENTITY_TOGGLING_HIDE;
                        entityPtr->dir = tempAction.direction;
                        break;
                }
            }

            // Look around
            i = entityPtr->xTile;
            j = entityPtr->yTile;

            if (entityPtr->isVisible == TRUE && entityPtr->state != ENTITY_DEAD)
            {
                for (m = 0U; m != entityPtr->visionDistance; ++m)
                {
                    switch (entityPtr->dir)
                    {
                        case DIR_UP:    j -= 1U; break;
                        case DIR_DOWN:  j += 1U; break;
                        case DIR_LEFT:  i -= 1U; break;
                        case DIR_RIGHT: i += 1U; break;
                    }
                    if (playGrid[j][i] >= WALKABLE_TILE_COUNT)
                        m = entityPtr->visionDistance - 1U;
                    else 
                    if (i == player.xTile && j == player.yTile)  // Spotted player
                    {
                        entityPtr->state = ENTITY_IDLE;
                        substate = SUB_SPOTTED;
                        animTick = 0U;
                        p = entityPtr->id;
                        return;
                    }
                }
            }
        }
    }
}

static void killPlayer(void)
{
    fadeout();
    player.lives--;
    substate = SUB_REINIT;
    animTick = 0U;
}

static void loadRoom(UINT8 id)
{
    roomId = id;

    loadMapTileData(roomId);

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
    UINT16 rightBound = camera_x + 160U;
    UINT16 bottomBound = camera_y + 138U;
   
    entityPtr = entityList;
    for (i = 0U; i != ENTITY_MAX; ++i)
    {
        entityPtr = &entityList[i];
        if (entityPtr->id != 0xFF)
        // if (entityPtr->id != 0xFF && roomId % 2U == 0U)
        {
            if (entityPtr->isHiding == TRUE)
                entityPtr->isVisible = FALSE;
            else if ((entityPtr->xSpr < camera_x || entityPtr->ySpr < camera_y)
                || (entityPtr->xSpr > rightBound || entityPtr->ySpr > bottomBound))
                entityPtr->isVisible = FALSE;
            else
                entityPtr->isVisible = TRUE;

            if (entityPtr->isVisible == TRUE)
            {
                if (entityPtr->state == ENTITY_DEAD)
                {
                    move_sprite(entityPtr->spriteId,      entityPtr->xSpr - camera_x ,     entityPtr->ySpr - camera_y);
                    move_sprite(entityPtr->spriteId + 1U, entityPtr->xSpr - camera_x ,     entityPtr->ySpr - camera_y + 8U);
                    move_sprite(entityPtr->spriteId + 2U, entityPtr->xSpr - camera_x + 8U, entityPtr->ySpr - camera_y);
                    move_sprite(entityPtr->spriteId + 3U, entityPtr->xSpr - camera_x + 8U, entityPtr->ySpr - camera_y + 8U);
                }
                else
                {
                    moveNPCSprite(entityPtr->speciesId, entityPtr->animFrame, 0x30U, entityPtr->spriteId,
                                  entityPtr->xSpr - camera_x + 8U, entityPtr->ySpr - camera_y + 6U,
                                   entityPtr->dir == DIR_LEFT ? TRUE : FALSE);
                }
            }
            else
            {
                hide_sprites_range(entityPtr->spriteId, entityPtr->spriteId + 4U);
            }
        }
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
    if (roomId == 0U)
        set_bkg_tiles(x, y, 2U, 2U, metaTiles[tileIndex]);
    else
        set_bkg_tiles(x, y, 2U, 2U, metaTiles[tileIndex]);
    // set_bkg_tile_xy(x,y,x);
    // set_bkg_tile_xy(x+1,y,y);
    // set_bkg_tile_xy(x, y, tileIndex);
}
