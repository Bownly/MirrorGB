#include <gb/gb.h>

// #include "../Engine/enums.h"
#include "../Objects/LevelObject.h"

#include "../Assets/Maps/Levels/HouseRMap.h"
#include "../Assets/Maps/Levels/Level1mMap.h"

const LevelObject levelDex[32U] = {
    { .map = HouseRMap_tilemap, .w = HouseRMap_tilemap_width, .h = HouseRMap_tilemap_height },
    { .map = Level1MMap, .w = Level1MMapWidth, .h = Level1MMapHeight },
    { .map = HouseRMap_tilemap, .w = HouseRMap_tilemap_width, .h = HouseRMap_tilemap_height },
    { .map = HouseRMap_tilemap, .w = HouseRMap_tilemap_width, .h = HouseRMap_tilemap_height },
};
