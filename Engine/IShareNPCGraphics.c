#include <gb/gb.h>
#include <stdio.h>
#include <string.h>
#include <gbdk/metasprites.h>

#include "../Assets/Sprites/NPCgirl.h"
#include "../Assets/Sprites/NPCScientist.h"


#define DATA_BANK 5U
static UINT8 nextBank;


static const UINT8 tileCounts[] = 
{
    NPCScientist_TILE_COUNT,
    NPCgirl_TILE_COUNT
};

static const UINT8* tilePtrs[] = 
{
    NPCScientist_tiles,
    NPCgirl_tiles
};

static const metasprite_t** npcMetasprites[] = 
{
    NPCScientist_metasprites,
    NPCgirl_metasprites
};


UINT8 loadNPCSpriteTiles(UINT8 speciesId, UINT8 spriteTileIndex)
{
    nextBank = CURRENT_BANK;
    SWITCH_ROM(DATA_BANK);

    set_sprite_data(spriteTileIndex, tileCounts[speciesId], tilePtrs[speciesId]);

    SWITCH_ROM(nextBank);
    return tileCounts[speciesId];
}

void moveNPCSprite(UINT8 speciesId, UINT8 frameId, UINT8 baseTile, UINT8 baseSprite, UINT8 x, UINT8 y, UINT8 isVflipped)
{
    nextBank = CURRENT_BANK;
    SWITCH_ROM(DATA_BANK);
    if (isVflipped == FALSE)
        move_metasprite(npcMetasprites[speciesId][frameId], baseTile, baseSprite, x, y);
    else
        move_metasprite_vflip(npcMetasprites[speciesId][frameId], baseTile, baseSprite, x, y);
    SWITCH_ROM(nextBank);
}
