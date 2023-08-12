#include <gb/gb.h>

#include "../Engine/enums.h"
#include "../Objects/RoomObject.h"

#include "../Assets/Maps/Levels/HouseRMap.h"
#include "../Assets/Maps/Levels/HouseMMap.h"

const RoomObject roomDex[32U] = {
    { .map = HouseRMap_tilemap, .w = HouseRMap_tilemap_width, .h = HouseRMap_tilemap_height, .tilesetId = 0U },
    { .map = HouseMMap_tilemap, .w = HouseMMap_tilemap_width, .h = HouseMMap_tilemap_height, .tilesetId = 1U },
    { .map = HouseRMap_tilemap, .w = HouseRMap_tilemap_width, .h = HouseRMap_tilemap_height, .tilesetId = 0U },
    { .map = HouseRMap_tilemap, .w = HouseRMap_tilemap_width, .h = HouseRMap_tilemap_height, .tilesetId = 1U },
};


