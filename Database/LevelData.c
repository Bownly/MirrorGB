#include <gb/gb.h>

// #include "../Engine/enums.h"
#include "../Objects/LevelObject.h"

#include "../Assets/Maps/Levels/HouseRMap.h"
#include "../Assets/Maps/Levels/HouseMMap.h"

const LevelObject levelDex[32U] = {
    { .map = HouseRMap_tilemap, .w = HouseRMap_tilemap_width, .h = HouseRMap_tilemap_height },
    { .map = HouseMMap_tilemap, .w = HouseMMap_tilemap_width, .h = HouseMMap_tilemap_height },
    { .map = HouseRMap_tilemap, .w = HouseRMap_tilemap_width, .h = HouseRMap_tilemap_height },
    { .map = HouseRMap_tilemap, .w = HouseRMap_tilemap_width, .h = HouseRMap_tilemap_height },
};
