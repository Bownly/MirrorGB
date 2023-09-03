#include <gb/gb.h>

#include "../Engine/enums.h"
#include "../Objects/NPCObject.h"


const UINT8 HouseRMetaTiles[][4] = {
    // Wooden floor
    { 0x1E, 0x1E, 0x1E, 0x1E },
    { 0x1E, 0x1E, 0x1E, 0x2D },
    { 0x1E, 0x1E, 0x2D, 0x2D },
    { 0x1E, 0x1E, 0x2D, 0x1E },
    { 0x1E, 0x2D, 0x1E, 0x1E },
    { 0x2D, 0x2D, 0x1E, 0x1E },
    { 0x2D, 0x1E, 0x1E, 0x1E },

    { 0x17, 0x18, 0x25, 0x26 },  // Carpet

    // Tile floor
    { 0x2D, 0x2E, 0x2E, 0x04 },
    { 0x2D, 0x04, 0x2E, 0x04 },
    { 0x04, 0x2E, 0x04, 0x2D },
    { 0x2D, 0x2E, 0x2E, 0x2D },
    { 0x2D, 0x2E, 0x04, 0xD2 },

    // Carpeted wooden floor
    { 0x59, 0x59, 0x59, 0x59 },
    { 0x1E, 0x1E, 0x59, 0x59 },
    { 0x1E, 0x1E, 0x59, 0x1E },
    { 0x59, 0x59, 0x1E, 0x1E },
    { 0x59, 0x1E, 0x59, 0x1E },
    { 0x59, 0x1E, 0x1E, 0x1E },

    // Empty walkable tiles
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0x49, 0x49, 0x25, 0x26 },  // Carpeted doorway
    { 0xFF, 0xFF, 0xFF, 0xFF },  // Empty walkable tile

    { 6U, 7U, 11U, 12U },  // Mirror
    { 0xFF, 0xFF, 0xFF, 0xFF },  // Empty tile

    // Bathtub
    { 47U, 48U, 54U, 55U },
    { 58U, 59U, 63U, 64U },

    // Walls
    { 4U, 4U, 4U, 4U },
    { 2U, 3U, 2U, 3U },
    { 80U, 73U, 2U, 4U },
    { 73U, 73U, 4U, 3U },
    { 73U, 73U, 4U, 4U },
    { 73U, 73U, 2U, 3U },
    { 73U, 82U, 2U, 3U },
    { 73U, 73U, 2U, 4U },
    { 73U, 73U, 83U, 84U },
    { 73U, 82U, 4U, 3U },
    { 2U, 4U, 81U, 10U },  //Floor boards
    { 4U, 4U, 10U, 10U },
    { 4U, 3U, 10U, 87U },
    { 4U, 4U, 10U, 8U },
    { 4U, 4U, 9U, 10U },
    { 4U, 4U, 13U, 14U },
    { 4U, 4U, 14U, 14U },
    { 4U, 4U, 15U, 10U },
    { 5U, 5U, 5U, 5U },  // Window
    { 85U, 86U, 43U, 44U },  // Door bottom
    { 8U, 9U, 16U, 17U },  // Dresser top
    { 8U, 9U, 18U, 19U },  // Fridge top
    { 28U, 29U, 35U, 36U },  // Sink
    { 20U, 22U, 35U, 36U },  // Solo counter
    { 23U, 16U, 37U, 39U },  // Carpet dressers
    { 17U, 24U, 40U, 38U },
    { 20U, 21U, 35U, 36U },  // L and R counters
    { 21U, 22U, 35U, 36U },
    { 25U, 26U, 2U, 4U },  // Some bed tiles
    { 26U, 26U, 4U, 4U },
    { 27U, 24U, 3U, 38U },
    { 16U, 17U, 39U, 40U },  // Dresser bottom
    { 33U, 34U, 43U, 44U },  // Fridge bottom
    { 31U, 32U, 41U, 42U },  // Chair
    { 45U, 45U, 45U, 45U },  // Dark carpet
    { 2U, 4U, 2U, 4U },  // Couple more beds
    { 3U, 24U, 3U, 38U },
    { 68U, 69U, 2U, 3U },  // Top upsidedown U wall
    { 49U, 50U, 56U, 4U },  // Some table tops
    { 50U, 51U, 4U, 57U },
    { 2U, 4U, 60U, 61U },  // Some bed bottoms
    { 4U, 4U, 61U, 61U },
    { 3U, 24U, 62U, 38U },
    { 0xFF, 0xFF, 0xFF, 0xFF },  // Unused
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },  // Also unused
    { 2U, 3U, 52U, 53U },  // Bottom U wall
    { 56U, 4U, 65U, 66U },  // Some table bottoms
    { 4U, 57U, 66U, 67U },
    { 0xFF, 0xFF, 0xFF, 0xFF },  // Also unused
    { 70U, 71U, 74U, 75U },  // Couch
    { 71U, 71U, 75U, 75U },
    { 71U, 72U, 75U, 76U },
    { 0xFF, 0xFF, 0xFF, 0xFF },  // Also unused
    { 0xFF, 0xFF, 0xFF, 0xFF },  // Also unused
    { 68U, 90U, 2U, 4U },  // Some walls
    { 90U, 90U, 4U, 4U },
    { 73U, 73U, 88U, 88U },  // TVs?
    { 1U, 1U, 10U, 10U },
    { 4U, 4U, 8U, 9U },  // A dresser top
    { 4U, 4U, 10U, 13U },  // Some bed tops
    { 4U, 4U, 14U, 15U },
    { 4U, 3U, 4U, 3U },  // A wall
    { 23U, 25U, 37U, 2U },  // Some bed tiles
    { 26U, 27U, 4U, 3U },
    { 23U, 2U, 37U, 2U },
    { 30U, 30U, 49U, 50U },  // Some table tops
    { 30U, 30U, 51U, 30U },
    { 23U, 60U, 37U, 38U },  // Some bed bottoms
    { 61U, 62U, 37U, 38U },
    { 57U, 30U, 67U, 30U },  // A table leg
    { 90U, 69U, 4U, 3U },  // A corner wall
    { 89U, 8U, 30U, 2U },  // Carpet wall things
    { 9U, 89U, 3U, 30U },
    { 91U, 91U, 92U, 92U },  // Exit thing
    { 1U, 1U, 1U, 1U },  // Black tile
    { 30U, 30U, 77U, 30U },  // Chairs
    { 78U, 79U, 30U, 30U }


};

const UINT8 HouseMMetaTiles[][4] = {
    { 28U, 29U, 34U, 35U },  // Floor tiles
    { 28U, 29U, 46U, 47U },
    { 47U, 29U, 40U, 35U },
    { 34U, 35U, 35U, 28U },
    { 34U, 35U, 28U, 29U },
    { 34U, 35U, 35U, 35U },
    { 46U, 47U, 56U, 40U },
    { 34U, 29U, 28U, 29U },
    { 34U, 34U, 34U, 35U },
    { 29U, 29U, 34U, 35U },
    { 56U, 40U, 34U, 35U },
    { 35U, 28U, 34U, 29U },
    { 28U, 29U, 34U, 46U },
    { 28U, 29U, 47U, 35U },
    { 28U, 29U, 35U, 28U },
    { 40U, 28U, 35U, 34U },
    { 34U, 35U, 46U, 47U },
    { 34U, 29U, 46U, 47U },
    { 34U, 29U, 34U, 35U },
    { 56U, 40U, 28U, 29U },
    { 34U, 35U, 28U, 34U },
    { 47U, 35U, 40U, 29U },
    { 56U, 40U, 34U, 46U },
    { 28U, 56U, 34U, 35U },
    { 40U, 29U, 34U, 35U },
    { 56U, 28U, 40U, 46U },
    { 0xFF, 0xFF, 0xFF, 0xFF },  // Unused walkable tiles
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 5U, 6U, 12U, 13U },  // Mirror
    { 0xFF, 0xFF, 0xFF, 0xFF },  // Unused
    { 44U, 45U, 54U, 55U },  // Bathtub x2 
    { 57U, 58U, 62U, 63U },
    { 4U, 4U, 4U, 4U },  // Window
    { 67U, 68U, 2U, 3U },  // n, | |, U wall segments
    { 2U, 3U, 2U, 3U },
    { 2U, 3U, 50U, 51U },
    { 2U, 3U, 79U, 77U },  // Floor boards
    { 2U, 1U, 79U, 11U },
    { 1U, 1U, 11U, 11U },
    { 1U, 3U, 11U, 77U },
    { 11U, 18U, 28U, 2U },
    { 19U, 19U, 1U, 1U },
    { 19U, 20U, 1U, 3U },
    { 1U, 1U, 11U, 9U },
    { 1U, 1U, 10U, 11U },
    { 1U, 1U, 18U, 19U },
    { 1U, 1U, 20U, 11U },
    { 21U, 22U, 30U, 31U },  // Counters
    { 22U, 23U, 30U, 31U },
    { 26U, 27U, 30U, 31U },
    { 21U, 23U, 30U, 31U },
    { 7U, 8U, 14U, 15U },  // Fridge x2
    { 24U, 25U, 32U, 33U },
    { 1U, 1U, 9U, 10U },  // Dressers x5
    { 9U, 10U, 16U, 17U },
    { 16U, 17U, 36U, 37U },
    { 28U, 16U, 34U, 36U },
    { 17U, 29U, 37U, 35U },
    { 29U, 80U, 35U, 2U },  // Beds x8
    { 81U, 81U, 1U, 1U },
    { 28U, 2U, 34U, 64U },
    { 1U, 1U, 65U, 65U },
    { 1U, 3U, 65U, 66U },
    { 2U, 1U, 64U, 65U },
    { 3U, 39U, 66U, 49U },
    { 3U, 35U, 66U, 29U },
    { 38U, 39U, 48U, 49U },  // Cinnabon swirl
    { 42U, 43U, 1U, 3U },  // Bed?
    { 41U, 42U, 52U, 1U },  // Table x4
    { 42U, 43U, 1U, 53U },
    { 52U, 1U, 59U, 60U },
    { 1U, 53U, 60U, 61U },
    { 80U, 81U, 2U, 1U },  // 2 more beds
    { 82U, 29U, 3U, 35U },
    { 34U, 34U, 35U, 41U },  // 3 more tables
    { 34U, 35U, 42U, 43U },
    { 28U, 52U, 34U, 59U },
    // { 1U, 53U, 60U, 61U },
    { 70U, 71U, 73U, 74U },  // Couch x3
    { 71U, 71U, 74U, 74U },
    { 71U, 72U, 74U, 75U },
    { 78U, 69U, 2U, 3U },  // Lotta walls
    { 69U, 69U, 2U, 1U },
    { 69U, 69U, 1U, 3U },
    { 69U, 69U, 1U, 1U },
    { 69U, 69U, 2U, 3U },
    { 69U, 76U, 1U, 3U },
    { 78U, 69U, 2U, 1U },
    { 2U, 1U, 9U, 10U },
    { 67U, 22U, 2U, 1U },
    { 22U, 22U, 1U, 1U },
    { 22U, 68U, 1U, 3U },
    { 2U, 1U, 2U, 1U },
    { 1U, 3U, 1U, 3U },
    { 3U, 49U, 3U, 39U },  // Bed edges x3
    { 3U, 29U, 3U, 35U },
    { 28U, 2U, 34U, 2U },
    { 83U, 83U, 84U, 84U },  // Exit carpet thing
    { 1U, 1U, 1U, 1U }  // Black
};

const UINT8 LabRMetaTiles[][4] = {
    { 13U, 13U, 13U, 13U }, // Floors
    { 13U, 14U, 21U, 22U },
    { 0xFF, 0xFF, 0xFF, 0xFF },  // Unused walkable tiles
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },

    { 4U, 5U, 7U, 8U },  // Mirror
    { 2U, 9U, 44U, 12U },  // Computers
    { 9U, 9U, 11U, 12U },
    { 9U, 9U, 47U, 10U },
    { 15U, 16U, 23U, 24U },
    { 17U, 18U, 25U, 26U },
    { 19U, 20U, 27U, 28U },  // Cabinets
    { 37U, 38U, 41U, 42U },
    { 45U, 46U, 27U, 28U },
    { 29U, 30U, 33U, 34U },
    { 35U, 36U, 39U, 40U },
    { 2U, 3U, 2U, 3U },  // Walls
    { 9U, 9U, 9U, 9U },
    { 31U, 32U, 2U, 3U },
    { 31U, 6U, 2U, 9U },
    { 6U, 6U, 9U, 9U },
    { 6U, 32U, 9U, 3U },
    { 9U, 9U, 10U, 10U },
    { 9U, 3U, 10U, 43U },
    { 1U, 1U, 1U, 1U }  // Black square
};

const UINT8 LabMMetaTiles[][4] = {
    { 12U, 12U, 12U, 12U },  // Floor tiles
    { 11U, 12U, 21U, 22U },
    { 0xFF, 0xFF, 0xFF, 0xFF },  // Unused walkable tiles
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },
    { 0xFF, 0xFF, 0xFF, 0xFF },

    { 4U, 5U, 6U, 7U },  // Mirror
    { 19U, 20U, 29U, 30U },  // Spiral floor thing
    { 1U, 3U, 9U, 36U },  // Computers
    { 1U, 1U, 9U, 10U },
    { 13U, 14U, 23U, 24U },
    { 15U, 16U, 25U, 26U },
    { 17U, 18U, 27U, 28U },  // Cabinets
    { 34U, 35U, 38U, 39U },
    { 41U, 42U, 27U, 28U },
    { 43U, 44U, 45U, 46U },  // Door
    { 47U, 48U, 49U, 50U },
    { 2U, 3U, 2U, 3U },  // Walls
    { 33U, 31U, 2U, 1U },
    { 31U, 31U, 1U, 1U },
    { 31U, 32U, 1U, 3U },
    { 33U, 32U, 2U, 3U },
    { 2U, 1U, 37U, 8U },
    { 1U, 3U, 8U, 40U },
    { 1U, 1U, 8U, 8U },
    { 1U, 1U, 8U, 52U },
    { 1U, 1U, 1U, 1U }  // Black tile
};



const UINT8* metatilesDex[] =
    // House map
    {
        &LabRMetaTiles[0U][0U],
        &LabMMetaTiles[0U][0U],
        &HouseRMetaTiles[0U][0U],
        &HouseMMetaTiles[0U][0U],
    };
