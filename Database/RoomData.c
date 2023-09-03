#include <gb/gb.h>

#include "../Engine/enums.h"
#include "../Objects/RoomObject.h"

#include "../Assets/Maps/Levels/TutorialRMap.h"
#include "../Assets/Maps/Levels/TutorialMMap.h"
#include "../Assets/Maps/Levels/HouseRMap.h"
#include "../Assets/Maps/Levels/HouseMMap.h"

const RoomObject roomDex[32U] = {
    { .map = TutorialRMap_tilemap, .w = TutorialRMap_tilemap_width, .h = TutorialRMap_tilemap_height, .tilesetId = 0U },
    { .map = TutorialMMap_tilemap, .w = TutorialMMap_tilemap_width, .h = TutorialMMap_tilemap_height, .tilesetId = 1U },
    { .map = HouseRMap_tilemap, .w = HouseRMap_tilemap_width, .h = HouseRMap_tilemap_height, .tilesetId = 2U },
    { .map = HouseMMap_tilemap, .w = HouseMMap_tilemap_width, .h = HouseMMap_tilemap_height, .tilesetId = 3U },
};


