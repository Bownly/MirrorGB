#include <gb/gb.h>

#include "../Engine/enums.h"
#include "../Objects/RoomObject.h"

#include "../Assets/Maps/Levels/TutorialRMap.h"
#include "../Assets/Maps/Levels/TutorialMMap.h"
#include "../Assets/Maps/Levels/HouseRMap.h"
#include "../Assets/Maps/Levels/HouseMMap.h"
#include "../Assets/Maps/Levels/ChurchRMap.h"
#include "../Assets/Maps/Levels/ChurchMMap.h"
#include "../Assets/Maps/Levels/SchoolRMap.h"
#include "../Assets/Maps/Levels/SchoolMMap.h"

const RoomObject roomDex[32U] = {
    { .map = TutorialRMap_tilemap, .w = TutorialRMap_tilemap_width, .h = TutorialRMap_tilemap_height, .tilesetId = 0U },
    { .map = TutorialMMap_tilemap, .w = TutorialMMap_tilemap_width, .h = TutorialMMap_tilemap_height, .tilesetId = 1U },
    { .map = ChurchRMap_tilemap, .w = ChurchRMap_tilemap_width, .h = ChurchRMap_tilemap_height, .tilesetId = 2U },
    { .map = ChurchMMap_tilemap, .w = ChurchMMap_tilemap_width, .h = ChurchMMap_tilemap_height, .tilesetId = 3U },
    { .map = HouseRMap_tilemap, .w = HouseRMap_tilemap_width, .h = HouseRMap_tilemap_height, .tilesetId = 2U },
    { .map = HouseMMap_tilemap, .w = HouseMMap_tilemap_width, .h = HouseMMap_tilemap_height, .tilesetId = 3U },
    { .map = SchoolRMap_tilemap, .w = SchoolRMap_tilemap_width, .h = SchoolRMap_tilemap_height, .tilesetId = 2U },
    { .map = SchoolMMap_tilemap, .w = SchoolMMap_tilemap_width, .h = SchoolMMap_tilemap_height, .tilesetId = 3U }
};


