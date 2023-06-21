#include <gb/gb.h>

// #include "../Engine/enums.h"
#include "../Objects/LevelObject.h"

#include "../Assets/Maps/Levels/Level1Map.h"


const LevelObject levelDex[32U] = {
    { .map = Level1Map, .w = Level1MapWidth, .h = Level1MapHeight },
    { .map = Level1Map, .w = Level1MapWidth, .h = Level1MapHeight },
    { .map = Level1Map, .w = Level1MapWidth, .h = Level1MapHeight },
    { .map = Level1Map, .w = Level1MapWidth, .h = Level1MapHeight },
};
