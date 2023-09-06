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
static UINT16 i16;
static UINT16 j16;

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
extern LevelObject tempLevel;
extern NPCObject tempNPC;

extern EntityObject player;
static UINT16 hungerTick;
#define HUNGER_THRESHOLD 100U
static EntityObject* entityPtr;
// static UINT8 entityGrid[32U][32U];  // Holds IDs of entities
static EntityObject entityList[8U];
static UINT8 entitySpriteIndexList[8U];  // Awful code, but whatever. 8 = number of unique NPC spritesheets
#define ENTITY_MAX 7U
static UINT8 headCount;

static const UINT8 hudMouthMap[8U] = {0xF0, 0xF2, 0xF4, 0xF6, 0xF1, 0xF3, 0xF5, 0xF7};

#define STARTPOS 0U
#define STARTCAM 0U

extern UINT8 roomId;
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

#define SPOTTED_ANIM_DURATION 30U
#define EXCLAMATION_SPR_ID 4U
#define EXCLAMATION_SPR_INDEX 0xE8U
#define BLOOD_SPR_INDEX 0xECU

#define pxToSubpx(px) ((px) << 4U)
#define subPxToPx(subpx) ((subpx) >> 4U)

#define tileToPx(tile) ((tile) << 3U)
#define pxToTile(px) ((px) >> 3U)

#define metatileToPx(metatile) ((metatile) << 4U)
#define pxToMetatile(px) ((px) >> 4U)

static const unsigned char reverseByteTable[] = {
        0x00, 0x80, 0x40, 0xc0, 0x20, 0xa0, 0x60, 0xe0,
        0x10, 0x90, 0x50, 0xd0, 0x30, 0xb0, 0x70, 0xf0,
        0x08, 0x88, 0x48, 0xc8, 0x28, 0xa8, 0x68, 0xe8,
        0x18, 0x98, 0x58, 0xd8, 0x38, 0xb8, 0x78, 0xf8,
        0x04, 0x84, 0x44, 0xc4, 0x24, 0xa4, 0x64, 0xe4,
        0x14, 0x94, 0x54, 0xd4, 0x34, 0xb4, 0x74, 0xf4,
        0x0c, 0x8c, 0x4c, 0xcc, 0x2c, 0xac, 0x6c, 0xec,
        0x1c, 0x9c, 0x5c, 0xdc, 0x3c, 0xbc, 0x7c, 0xfc,
        0x02, 0x82, 0x42, 0xc2, 0x22, 0xa2, 0x62, 0xe2,
        0x12, 0x92, 0x52, 0xd2, 0x32, 0xb2, 0x72, 0xf2,
        0x0a, 0x8a, 0x4a, 0xca, 0x2a, 0xaa, 0x6a, 0xea,
        0x1a, 0x9a, 0x5a, 0xda, 0x3a, 0xba, 0x7a, 0xfa,
        0x06, 0x86, 0x46, 0xc6, 0x26, 0xa6, 0x66, 0xe6,
        0x16, 0x96, 0x56, 0xd6, 0x36, 0xb6, 0x76, 0xf6,
        0x0e, 0x8e, 0x4e, 0xce, 0x2e, 0xae, 0x6e, 0xee,
        0x1e, 0x9e, 0x5e, 0xde, 0x3e, 0xbe, 0x7e, 0xfe,
        0x01, 0x81, 0x41, 0xc1, 0x21, 0xa1, 0x61, 0xe1,
        0x11, 0x91, 0x51, 0xd1, 0x31, 0xb1, 0x71, 0xf1,
        0x09, 0x89, 0x49, 0xc9, 0x29, 0xa9, 0x69, 0xe9,
        0x19, 0x99, 0x59, 0xd9, 0x39, 0xb9, 0x79, 0xf9,
        0x05, 0x85, 0x45, 0xc5, 0x25, 0xa5, 0x65, 0xe5,
        0x15, 0x95, 0x55, 0xd5, 0x35, 0xb5, 0x75, 0xf5,
        0x0d, 0x8d, 0x4d, 0xcd, 0x2d, 0xad, 0x6d, 0xed,
        0x1d, 0x9d, 0x5d, 0xdd, 0x3d, 0xbd, 0x7d, 0xfd,
        0x03, 0x83, 0x43, 0xc3, 0x23, 0xa3, 0x63, 0xe3,
        0x13, 0x93, 0x53, 0xd3, 0x33, 0xb3, 0x73, 0xf3,
        0x0b, 0x8b, 0x4b, 0xcb, 0x2b, 0xab, 0x6b, 0xeb,
        0x1b, 0x9b, 0x5b, 0xdb, 0x3b, 0xbb, 0x7b, 0xfb,
        0x07, 0x87, 0x47, 0xc7, 0x27, 0xa7, 0x67, 0xe7,
        0x17, 0x97, 0x57, 0xd7, 0x37, 0xb7, 0x77, 0xf7,
        0x0f, 0x8f, 0x4f, 0xcf, 0x2f, 0xaf, 0x6f, 0xef,
        0x1f, 0x9f, 0x5f, 0xdf, 0x3f, 0xbf, 0x7f, 0xff,
    };

        unsigned char tempColumn[360U];

/* SUBSTATE METHODS */
static void phaseInit(void);
static void phaseReinit(void);
static void phaseLoop(void);
static void phaseMirrorINg(void);
static void phaseMirrorOUTing(void);
static void phaseSpotted(void);
static void phaseKillPlayer(void);

/* INPUT METHODS */
static void inputs(void);

/* HELPER METHODS */
static void addChaseActionToChasers(UINT8);
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
        case SUB_MIRRORING:
            phaseMirrorINg();
            break;
        case SUB_MIRROROUTING:
            phaseMirrorOUTing();
            break;
        case SUB_SPOTTED:
            phaseSpotted();
            break;
        case SUB_KILL_PLAYER:
            phaseKillPlayer();
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
    headCount = 0U;

    // Init entity stuff
    for (i = 0U; i != ENTITY_MAX; ++i)
        entityList[i].id = 0xFFU;

    loadLevelObject(roomId / 2U);
    for (i = 0U; i != tempLevel.npcCount; ++i)
    {
        if (tempLevel.npcIds[i] != 0xFFU)
        {
            getNPCData(tempLevel.npcIds[i]);
            entityListAdd(i);
        }
    }

    HIDE_WIN;
    SHOW_SPRITES;
    SPRITES_8x8;

    commonInit();

    switch (roomId / 2U)
    {
        default:
        case 0U: playOutsideSong(SONG_LEVEL01); break;  // Tutorial
        case 1U: playOutsideSong(SONG_LEVEL02); break;  // House
        case 2U: playOutsideSong(SONG_LEVEL03); break;  // Church
        case 3U: playOutsideSong(SONG_MAINMENU); break;  // School
    }

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
    if (roomId % 2U == 0U)
    {
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
    }

    // Player movements and inputs
    if (player.state == ENTITY_WALKING)
        walkPlayer();

    handleRoutines();
    // if (substate == SUB_SPOTTED)
    //   return;

    // Need to recheck player.state because the previous fn might have changed it
    if (substate == SUB_LOOP && player.state == ENTITY_IDLE)
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

static void phaseMirrorINg(void)
{
    // if (animTick == 0U)
    // {
    //     wait_vbl_done();

    //     // unsigned char tempTile[16U];
    //     // for (i = 0U; i != 80U; ++i)
    //     // {
    //     //     get_bkg_data(i, 1, tempTile);
    //     //     for (j = 0U; j != 16U; ++j)
    //     //     {
    //     //         tempTile[j] = reverseByteTable[tempTile[j]];
    //     //     }
    //     //     set_bkg_data(i, 1, tempTile);
    //     // }


    //     // // Swap out tiles on screen
    //     // get_bkg_tiles(map_pos_x, map_pos_y, 20U, 18U, tempColumn);
    //     // for (i = 0U; i != 20U; ++i)
    //     // {
    //     //     for (j = 0U; j != 20U; ++j)
    //     //     // set_bkg_tiles(map_pos_x + i, map_pos_y, 1U, 18U, tempColumn + (18*i));
    //     //     set_bkg_tile_xy(map_pos_x + i, map_pos_y + j, tempColumn[i + (20*j)]);
    //     // }
    // }
    // else 
    if (animTick < 8U)
    {
        i = player.dir == DIR_UP ? 4U : 2U;
        switch (player.dir)
        {
            case DIR_UP: player.ySpr -= 4U; break;
            case DIR_LEFT: player.xSpr -= i; break;
            case DIR_RIGHT: player.xSpr += i; break;
        }
        animatePlayer();
    }
    else if (animTick == 8U)
    {
        fadeout();
        substate = SUB_MIRROROUTING;
        playSfx(SFX_7);

        player.xTile = gridW - 1U - player.xTile;
        if (roomId % 2U == 0U)  // From real world to mirror world
        {
            ++roomId;
            playGridPtr = &playGridM;

            for (i = 0U; i != ENTITY_MAX; ++i)
            {
                entityList[i].isVisible = FALSE;
                if (entityList[i].isChasing == TRUE)  // Reset chasers
                {
                    entityList[i].isChasing = FALSE;
                    entityList[i].chasingActionsCount = 0U;
                    entityList[i].state = entityList[i].oldState;
                    entityList[i].dir = entityList[i].oldDir;
                    entityList[i].xSpr = entityList[i].oldXSpr;
                    entityList[i].ySpr = entityList[i].oldYSpr;
                    entityList[i].xTile = entityList[i].oldXTile;
                    entityList[i].yTile = entityList[i].oldYTile;
                    entityList[i].actionTimer = entityList[i].oldActionTimer;
                    entityList[i].curActionIndex = entityList[i].oldActionIndex;
                    entityList[i].curRoutineIndex = entityList[i].oldRoutineIndex;
                }
            }

            hide_sprites_range(14U, 40U);
        }
        else  // From mirror world to real world
        {
            --roomId;
            playGridPtr = &playGrid;

            // for (i = 0U; i != ENTITY_MAX; ++i)
            // {
            //     entityPtr = &entityList[i];
            //     if (entityPtr->id != 0xFF)
            //     {
            //         set_win_tile_xy(i, 0, entityPtr->dir);
            //         set_win_tile_xy(i, 1, entityPtr->isVisible);
            //     }
            // }
            // // This is to reset NPCs' dir post-chase
            // if (roomId % 2U == 0U)  // Don't animate entities if we're entering the mirror world
            //     animateEntities();

        }
        loadRoom(roomId);
        if (player.dir == DIR_UP)
            player.dir = DIR_DOWN;

        animTick = 0U;
        return;
    }
    
    ++animTick;
}

static void phaseMirrorOUTing(void)
{
    if (animTick == 0U)
    {
        switch (player.dir)
        {
            case DIR_DOWN: player.ySpr -= 32U; break;
            case DIR_LEFT: player.xSpr += 16U; break;
            case DIR_RIGHT: player.xSpr -= 16U; break;
        }

        fadein();
    }

    if (animTick < 8U)
    {
        i = player.dir == DIR_DOWN ? 4U : 2U;
        switch (player.dir)
        {
            case DIR_DOWN: player.ySpr += 4U; break;
            case DIR_LEFT: player.xSpr -= i; break;
            case DIR_RIGHT: player.xSpr += i; break;
        }
        animatePlayer();
    }
    else if (animTick == 8U)
    {
        substate = SUB_LOOP;
        animTick = 0U;
        return;
    }
    
    ++animTick;
}

static void phaseSpotted(void)
{
    if (animTick == 0U)
    {
        set_sprite_tile(EXCLAMATION_SPR_ID,      EXCLAMATION_SPR_INDEX);
        set_sprite_tile(EXCLAMATION_SPR_ID + 1U, EXCLAMATION_SPR_INDEX + 1U);
        set_sprite_tile(EXCLAMATION_SPR_ID + 2U, EXCLAMATION_SPR_INDEX);
        set_sprite_tile(EXCLAMATION_SPR_ID + 3U, EXCLAMATION_SPR_INDEX + 1U);
        set_sprite_prop(EXCLAMATION_SPR_ID + 2U, 0b00100000U);
        set_sprite_prop(EXCLAMATION_SPR_ID + 3U, 0b00100000U);

        entityPtr = &entityList[p];
        p = 0xFFU;

        UINT8 xPad = 0U;
        if (entityPtr->yTile == player.yTile + 1U)
            xPad = 1U;

        move_sprite(EXCLAMATION_SPR_ID,      entityPtr->xSpr - camera_x - xPad,      entityPtr->ySpr - camera_y - 18U);
        move_sprite(EXCLAMATION_SPR_ID + 1U, entityPtr->xSpr - camera_x - xPad,      entityPtr->ySpr - camera_y - 10U);
        move_sprite(EXCLAMATION_SPR_ID + 2U, entityPtr->xSpr - camera_x - xPad + 8U, entityPtr->ySpr - camera_y - 18U);
        move_sprite(EXCLAMATION_SPR_ID + 3U, entityPtr->xSpr - camera_x - xPad + 8U, entityPtr->ySpr - camera_y - 10U);
    }
    else if (animTick == SPOTTED_ANIM_DURATION)
    {
        for (i = 0U; i != 4U; ++i)
        {
            set_sprite_tile(EXCLAMATION_SPR_ID + i, 0xA5U);
            move_sprite(EXCLAMATION_SPR_ID + i, 0U, 144U);
        }

        entityPtr->oldState = entityPtr->state;
        entityPtr->oldDir = entityPtr->dir;
        entityPtr->oldXSpr = entityPtr->xSpr;
        entityPtr->oldYSpr = entityPtr->ySpr;
        entityPtr->oldXTile = entityPtr->xTile;
        entityPtr->oldYTile = entityPtr->yTile;
        entityPtr->oldActionTimer = entityPtr->actionTimer;
        entityPtr->oldActionIndex = entityPtr->curActionIndex;
        entityPtr->oldRoutineIndex = entityPtr->curRoutineIndex;
        entityPtr->isChasing = TRUE;
        entityPtr->state = ENTITY_IDLE;
        entityPtr->actionTimer = 0U;

        substate = SUB_LOOP;
    }
    ++animTick;
}

static void phaseKillPlayer(void)
{
    if (animTick == 1U)
    {
        playSfx(SFX_8);
        p = 0xFFU;
        // Turn player sprite into bloodstain
        player.state = ENTITY_DEAD;
        set_sprite_tile(player.spriteId,      BLOOD_SPR_INDEX);
        set_sprite_tile(player.spriteId + 1U, BLOOD_SPR_INDEX + 1U);
        set_sprite_tile(player.spriteId + 2U, BLOOD_SPR_INDEX + 2U);
        set_sprite_tile(player.spriteId + 3U, BLOOD_SPR_INDEX + 3U);
        set_sprite_prop(player.spriteId,      0b00011000U);
        set_sprite_prop(player.spriteId + 1U, 0b00011000U);
        set_sprite_prop(player.spriteId + 2U, 0b00011000U);
        set_sprite_prop(player.spriteId + 3U, 0b00011000U);

        // NOTE: Temp line until we add a kill animation
        animateEntities();
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

            if ((*playGridPtr)[j][i] == WALKABLE_TILE_COUNT && player.dir != DIR_DOWN)
            {
                substate = SUB_MIRRORING;
                animTick = 0U;
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
                if (entityPtr->state != ENTITY_DEAD && entityPtr->state != ENTITY_WALKING && entityPtr->isHiding == FALSE && entityPtr->xTile == i && entityPtr->yTile == j)
                {
                    entityKill(entityPtr->id);
                    player.hpCur = player.hpMax;
                    displayHealthPips();
                    hungerTick = 0U;
                }
            }
        }

        if (curJoypad & J_B && !(prevJoypad & J_B))
        {
            headCount = 1U;
            entityKill(0U);
        }

        if (curJoypad & J_UP)
        {
            player.dir = DIR_UP;

            if (player.ySpr != 0U && (*playGridPtr)[player.yTile-1U][player.xTile] < WALKABLE_TILE_COUNT)
            {
                if (roomId % 2U == 1U || (roomId % 2U == 0U && checkForEntityCollision(player.xTile, player.yTile - 1U) == FALSE))
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

                    addChaseActionToChasers(player.dir);
                }
            }
        }
        else if (curJoypad & J_DOWN)
        {
            player.dir = DIR_DOWN;

            if (player.ySpr != 0U && (*playGridPtr)[player.yTile+1U][player.xTile] < WALKABLE_TILE_COUNT)
            {
                if (roomId % 2U == 1U || (roomId % 2U == 0U && checkForEntityCollision(player.xTile, player.yTile + 1U) == FALSE))
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
                    addChaseActionToChasers(player.dir);
                }

            }
        }
        else if (curJoypad & J_LEFT)
        {
            player.dir = DIR_LEFT;

            if (player.ySpr != 0U && (*playGridPtr)[player.yTile][player.xTile-1U] < WALKABLE_TILE_COUNT)
            {
                if (roomId % 2U == 1U || (roomId % 2U == 0U && checkForEntityCollision(player.xTile - 1U, player.yTile) == FALSE))
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

                    addChaseActionToChasers(player.dir);
                }
            }
        }
        else if (curJoypad & J_RIGHT)
        {
            player.dir = DIR_RIGHT;

            if (player.ySpr != 0U && (*playGridPtr)[player.yTile][player.xTile+1U] < WALKABLE_TILE_COUNT)
            {
                if (roomId % 2U == 1U || (roomId % 2U == 0U && checkForEntityCollision(player.xTile + 1U, player.yTile) == FALSE))
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

                    addChaseActionToChasers(player.dir);
                }
            }
        }
    }
}


/******************************** HELPER METHODS *********************************/
static void addChaseActionToChasers(UINT8 dir)
{
    for (i = 0U; i != ENTITY_MAX; ++i)
    {
        if (entityList[i].isChasing == TRUE)
        {
            entityList[i].chasingActions[entityList[i].chasingActionsCount].action = ACT_WALK;
            entityList[i].chasingActions[entityList[i].chasingActionsCount].direction = dir;
            entityList[i].chasingActions[entityList[i].chasingActionsCount].magnitude = 1U;
            entityList[i].chasingActionsCount++;
        }
    }
}

static UINT8 checkForEntityCollision(UINT8 x, UINT8 y)
{
    // Check if tile in front is an npc
    entityPtr = entityList;
    for (k = 0U; k != ENTITY_MAX; ++k)
    {
        entityPtr = &entityList[k];
        if (entityPtr->state != ENTITY_DEAD)
            if (entityPtr->xTile == x && entityPtr->yTile == y)
                return TRUE;
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
    player.spriteId = 0U;
    player.state = ENTITY_IDLE;
    player.hpMax = 16U;
    player.hpCur = 16U;
    switch (roomId / 2U)
    {
        default:
        case 0U: player.xTile =  3U; player.yTile = 12U; player.dir = DIR_UP;   break;
        case 1U: player.xTile = 29U; player.yTile = 15U; player.dir = DIR_DOWN; break;
        case 2U: player.xTile =  5U; player.yTile =  5U; player.dir = DIR_DOWN; break;
        case 3U: player.xTile = 15U; player.yTile = 24U; player.dir = DIR_DOWN; break;
    }
    player.xSpr = player.xTile * 16U + 8U;
    player.ySpr = player.yTile * 16U + 16U;
    hungerTick = 0U;
    camera_x = STARTCAM, camera_y = STARTCAM, new_camera_x = STARTCAM, new_camera_y = STARTCAM;
    map_pos_x = STARTPOS, map_pos_y = STARTPOS, new_map_pos_x = STARTPOS, new_map_pos_y = STARTPOS;
    playGridPtr = &playGridM;

    // Load graphics
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

    gridW = getOwMapWidth(roomId + 1U);
    gridH = getOwMapHeight(roomId + 1U);
    playGridPtr = &playGridM;
    loadMapDataFromDatabase(&(playGridPtr[0][0]), roomId + 1U, gridW, gridH);
    gridW = getOwMapWidth(roomId);
    gridH = getOwMapHeight(roomId);
    playGridPtr = &playGrid;
    loadMapDataFromDatabase(&(playGridPtr[0][0]), roomId, gridW, gridH);

    // Check levelId, pull appropriate level
    camera_max_x = (((gridW - 20U) * 2U) + 20U) * 8U;
    camera_max_y = (((gridH - 18U) * 2U) + 18U) * 8U;

    loadRoom(roomId);

    animatePlayer();

    k = 0x30U;
    loadLevelNPCSpeciesList(roomId / 2U);
    for (i = 0U; i != 8U; ++i)  // Note: 8U is the size of a LevelObject's npcSpecies list
    {
        if (handyDandyString[i] != 0xFF)
        {
            entitySpriteIndexList[handyDandyString[i]] = k;
            k += loadNPCSpriteTiles(handyDandyString[i], k);
        }
    }

    headCount = 0U;
    loadLevelObject(roomId >> 1Ul);
    for (i = 0U; i != ENTITY_MAX; ++i)
    {
        if (entityList[i].id != 0xFF)
        {
            if (entityList[i].state != ENTITY_DEAD)
            {
                if (tempLevel.npcIds[i] != 0xFF)
                {
                    getNPCData(tempLevel.npcIds[i]);
                    entityListAdd(i);
                }
            }
        }
    }
    displayHeadcount();

    substate = SUB_LOOP;
    player.moveSpeed = PLAYER_SPEED;

    // Test line
    // set_bkg_data(0x00U, 27U, fontTiles);

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
    playSfx(SFX_8);

    if (headCount == 0U)
    {
        if (roomId / 2U == 3U)  // AKA, Level 4
            gamestate = STATE_BEAT_GAME;
        else
            gamestate = STATE_BEAT_LEVEL;
        substate = SUB_INIT;
        fadeout();
        stopSong();
    }
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
    entityList[id].oldState = entityList[id].state;
    entityList[id].oldDir = entityList[id].dir;
    entityList[id].oldXSpr = entityList[id].xSpr;
    entityList[id].oldYSpr = entityList[id].ySpr;
    entityList[id].oldXTile = tempNPC.xTile;
    entityList[id].oldYTile = tempNPC.yTile;
    entityList[id].oldActionTimer = 0U;
    entityList[id].oldActionIndex = 0U;
    entityList[id].oldRoutineIndex = 0U;
    entityList[id].isChasing = FALSE;

    ++headCount;
    // headCount = 1U;  // Test line
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
                    if (entityPtr->actionTimer == 0U)
                        entityPtr->state = ENTITY_IDLE;

                    m = entityPtr->isChasing == TRUE ? 2U : 1U;
                    entityPtr->actionTimer -= m;

                    entityPtr->xTile = (entityPtr->xSpr) >> 4U;
                    entityPtr->yTile = (entityPtr->ySpr - 8U) >> 4U;
                    switch (entityPtr->dir)
                    {
                        case DIR_UP:    entityPtr->ySpr -= m; break;
                        case DIR_DOWN:  entityPtr->ySpr += m; break;
                        case DIR_LEFT:  entityPtr->xSpr -= m; break;
                        case DIR_RIGHT: entityPtr->xSpr += m; break;
                    }
                    if (entityPtr->actionTimer == 0U)
                        entityPtr->state = ENTITY_IDLE;

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
                if (entityPtr->isChasing == FALSE)
                    entityPtr->curActionIndex = getAction(entityPtr->curRoutineIndex, entityPtr->curActionIndex);
                else
                {
                    if (entityPtr->chasingActionsCount == 0U)  // This should never happen, but you never know.
                    {
                        tempAction.action = ACT_WAIT;
                        tempAction.direction = DIR_DOWN;
                        tempAction.magnitude = 0U;
                    }
                    else
                    {
                        i16 = entityPtr->xSpr;
                        j16 = entityPtr->ySpr;
                        switch (entityPtr->chasingActions[0U].direction)
                        {
                            case DIR_UP:    j16 -= 16U; break;
                            case DIR_DOWN:  j16 += 16U; break;
                            case DIR_LEFT:  i16 -= 16U; break;
                            case DIR_RIGHT: i16 += 16U; break;
                        }
                        i = (i16) >> 4U;
                        j = (j16- 8U) >> 4U;

                        if (player.xTile == i && player.yTile == j)
                        {
                            substate = SUB_KILL_PLAYER;
                            animTick = 0U;
                            p = entityPtr->id;
                            entityPtr->dir = entityPtr->chasingActions[0U].direction;

                            // NOTE: Temp lines until we add a kill animation
                            if (entityPtr->dir == DIR_RIGHT)
                                entityPtr->animFrame = (entityPtr->dir - 1U) * 3U;
                            else
                                entityPtr->animFrame = entityPtr->dir * 3U;
                            return;
                        }

                        tempAction.action = entityPtr->chasingActions[0U].action;
                        tempAction.direction = entityPtr->chasingActions[0U].direction;
                        tempAction.magnitude = entityPtr->chasingActions[0U].magnitude;

                        // Shift everything up the list... or is it down the list? Left the list.
                        for (i = 0U; i != entityPtr->chasingActionsCount - 1U; ++i)
                        {
                            entityPtr->chasingActions[i].action = entityPtr->chasingActions[i+1U].action;
                            entityPtr->chasingActions[i].direction = entityPtr->chasingActions[i+1U].direction;
                            entityPtr->chasingActions[i].magnitude = entityPtr->chasingActions[i+1U].magnitude;
                        }
                        entityPtr->chasingActionsCount--;
                    }
                }

                switch (tempAction.action)
                {
                    case ACT_WALK:
                        entityPtr->state = ENTITY_WALKING;
                        entityPtr->dir = tempAction.direction;
                        entityPtr->actionTimer = (16U * tempAction.magnitude);

                        if (entityPtr->dir == DIR_RIGHT)
                            entityPtr->animFrame = (entityPtr->dir - 1U) * 3U;
                        else
                            entityPtr->animFrame = entityPtr->dir * 3U;
                        break;
                    case ACT_FINISHING_WALK:
                            entityPtr->actionTimer = tempAction.magnitude;
                            entityPtr->state = ENTITY_WALKING;
                            set_win_tile_xy(entityPtr->id,1,entityPtr->actionTimer % 16U);
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
            i = (entityPtr->xSpr) >> 4U;
            j = (entityPtr->ySpr - 8U) >> 4U;

            if (entityPtr->isVisible == TRUE && entityPtr->state != ENTITY_DEAD && entityPtr->isChasing == FALSE)
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
                    else if (i == player.xTile && j == player.yTile)  // Spotted player
                    {
                        substate = SUB_SPOTTED;
                        animTick = 0U;
                        p = entityPtr->id;

                        playSfx(SFX_A);

                        // Fill out chasingAction array
                        entityPtr->chasingActionsCount = m + 1U;
                        n = 0U;
                        if (entityPtr->state == ENTITY_WALKING)
                        {
                            // Since actionTimer is so closely tied to position and speed, we need to make sure the NPC isn't starting in a literally odd spot
                            if (entityPtr->actionTimer % 2U == 1U)
                            {
                                switch (entityPtr->dir)
                                {
                                    case DIR_UP:    entityPtr->ySpr++; break;
                                    case DIR_DOWN:  entityPtr->ySpr--; break;
                                    case DIR_LEFT:  entityPtr->xSpr++; break;
                                    case DIR_RIGHT: entityPtr->xSpr--; break;
                                }
                                entityPtr->actionTimer = (entityPtr->actionTimer >> 1U) << 1U;
                            }

                            if (entityPtr->actionTimer != 0U)
                            {
                                n = 1U;
                                entityPtr->chasingActions[0U].action = ACT_FINISHING_WALK;
                                entityPtr->chasingActions[0U].direction = entityPtr->dir;
                                entityPtr->chasingActions[0U].magnitude = entityPtr->actionTimer % 16U;
                                entityPtr->chasingActionsCount++;
                            }
                        }
                        for (; n != entityPtr->chasingActionsCount + 1U; ++n)
                        {
                            entityPtr->chasingActions[n].action = ACT_WALK;
                            entityPtr->chasingActions[n].direction = entityPtr->dir;
                            entityPtr->chasingActions[n].magnitude = 1U;
                        }
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
    if (player.lives == 0U)
    {
        gamestate = STATE_GAMEOVER;
        substate = SUB_INIT;
        stopSong();
    }
    else
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
    if (player.xTile > 5U)  // 5 is the x offset from left to center
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
                checkUnderfootTile();
            }
        }
        else
        {
            camera_y -= PLAYER_SPEED;
            if (camera_y % 16U == 0U)
            {
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
                checkUnderfootTile();
            }
        }
        else
        {
            camera_y += PLAYER_SPEED;
            if (camera_y % 16U == 0U)
            {
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
                checkUnderfootTile();
            }
        }
        else
        {
            camera_x -= PLAYER_SPEED;
            if (camera_x % 16U == 0U)
            {
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
                checkUnderfootTile();
            }
        }
        else
        {
            camera_x += PLAYER_SPEED;
            if (camera_x % 16U == 0U)
            {
                checkUnderfootTile();
            }
        }
    }
    player.xTile = (player.xSpr + camera_x) >> 4U;
    player.yTile = (player.ySpr + camera_y - 8U) >> 4U;

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
                    moveNPCSprite(entityPtr->speciesId, entityPtr->animFrame, entitySpriteIndexList[entityPtr->speciesId], entityPtr->spriteId,
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
    set_bkg_tiles(x, y, 2U, 2U, metaTiles[tileIndex]);
}
