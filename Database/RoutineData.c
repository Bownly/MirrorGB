#include <gb/gb.h>

#include "../Engine/enums.h"
#include "../Objects/ActionObject.h"
#include "../Objects/RoutineObject.h"


// Tutorial
const ActionObject actionsTutWaiter[] = {
    { .action = ACT_WAIT, .direction = DIR_UP, .magnitude = 900U },
    { .action = ACT_WAIT, .direction = DIR_DOWN, .magnitude = 120U }
};
const ActionObject actionsTutWalker[] = {
    { .action = ACT_WAIT, .direction = DIR_UP, .magnitude = 240U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 3U },
    { .action = ACT_WAIT, .direction = DIR_UP, .magnitude = 240U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 3U }
};

// Church
const ActionObject actionsUsher[] = {
    { .action = ACT_WAIT, .direction = DIR_DOWN, .magnitude = 900U },
    { .action = ACT_WAIT, .direction = DIR_RAND, .magnitude = 30U },
    { .action = ACT_WAIT, .direction = DIR_RAND, .magnitude = 30U }
};
const ActionObject actionsFileCabinet[] = {
    { .action = ACT_WAIT, .direction = DIR_UP, .magnitude = 900U }
};
const ActionObject actionsChurchChecker[] = {
    { .action = ACT_WAIT, .direction = DIR_DOWN, .magnitude = 60U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 2U },
    { .action = ACT_WAIT, .direction = DIR_LEFT, .magnitude = 60U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 5U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 2U },
    { .action = ACT_WAIT, .direction = DIR_LEFT, .magnitude = 60U },

    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 7U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 8U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 1U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 9U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 1U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 8U },

    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 7U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 2U },
    { .action = ACT_WAIT, .direction = DIR_RIGHT, .magnitude = 60U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 5U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 2U },
    { .action = ACT_WAIT, .direction = DIR_RIGHT, .magnitude = 60U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 2U },
    { .action = ACT_WAIT, .direction = DIR_DOWN, .magnitude = 60U },

    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 14U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 8U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 1U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 9U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 1U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 8U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 14U }

};
const ActionObject actionsPriestCircle[] = {
    { .action = ACT_SPECIAL_ACTION, .direction = DIR_DOWN, .magnitude = 180U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 3U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 1U },
    { .action = ACT_SPECIAL_ACTION, .direction = DIR_DOWN, .magnitude = 180U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 3U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 1U },
    { .action = ACT_SWITCH_ROUTINE, .direction = 14U, .magnitude = 2U }
};
const ActionObject actionsPriestAudience[] = {
    { .action = ACT_SPECIAL_ACTION, .direction = DIR_DOWN, .magnitude = 180U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 4U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 4U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 1U },
    { .action = ACT_SPECIAL_ACTION, .direction = DIR_DOWN, .magnitude = 210U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 1U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 3U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 3U },
    { .action = ACT_SWITCH_ROUTINE, .direction = 14U, .magnitude = 0U }
};
const ActionObject actionsPew1Central[] = {
    { .action = ACT_WAIT, .direction = DIR_UP, .magnitude = 180U },
    { .action = ACT_SWITCH_ROUTINE, .direction = 16U, .magnitude = 5U }
};
const ActionObject actionsPew1Up[] = {
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 2U },
    { .action = ACT_WAIT, .direction = DIR_UP, .magnitude = 180U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 2U },
    { .action = ACT_SWITCH_ROUTINE, .direction = 16U, .magnitude = 0U }
};
const ActionObject actionsPew1Down[] = {
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 2U },
    { .action = ACT_WAIT, .direction = DIR_UP, .magnitude = 180U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 2U },
    { .action = ACT_SWITCH_ROUTINE, .direction = 16U, .magnitude = 0U }
};
const ActionObject actionsPew1Left[] = {
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 5U },
    { .action = ACT_WAIT, .direction = DIR_UP, .magnitude = 210U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 5U },
    { .action = ACT_SWITCH_ROUTINE, .direction = 16U, .magnitude = 0U }
};
const ActionObject actionsPew1Right[] = {
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 4U },
    { .action = ACT_WAIT, .direction = DIR_UP, .magnitude = 210U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 4U },
    { .action = ACT_SWITCH_ROUTINE, .direction = 16U, .magnitude = 0U }
};
const ActionObject actionsPew2Central[] = {
    { .action = ACT_WAIT, .direction = DIR_UP, .magnitude = 180U },
    { .action = ACT_SWITCH_ROUTINE, .direction = 22U, .magnitude = 2U }
};
const ActionObject actionsPew2Down[] = {
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 11U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 17U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 6U },
    { .action = ACT_SWITCH_ROUTINE, .direction = 21U, .magnitude = 0U }
};
const ActionObject actionsPew2Up[] = {
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 9U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 7U },
    { .action = ACT_SWITCH_ROUTINE, .direction = 21U, .magnitude = 0U }
};

// House
const ActionObject actionsBathroom[] = {
    { .action = ACT_WAIT, .direction = DIR_UP, .magnitude = 1000U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 1U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 1U },
    { .action = ACT_WAIT, .direction = DIR_UP, .magnitude = 120U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 1U },
    { .action = ACT_WAIT, .direction = DIR_DOWN, .magnitude = 120U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 1U }
};
const ActionObject actionsCouchman[] = {
    { .action = ACT_WAIT, .direction = DIR_UP, .magnitude = 120U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 5U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 6U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 11U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 3U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 2U },
    { .action = ACT_WAIT, .direction = DIR_DOWN, .magnitude = 180U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 1U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 4U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 7U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 10U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 8U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 4U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 3U },
    { .action = ACT_WAIT, .direction = DIR_UP, .magnitude = 180U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 3U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 1U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 1U },
    { .action = ACT_SPECIAL_ACTION, .direction = DIR_DOWN, .magnitude = 300U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 1U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 5U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 4U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 7U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 6U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 7U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 11U }
};
const ActionObject actionsWentToGetMilk[] = {
    { .action = ACT_TOGGLE_HIDING, .direction = DIR_DOWN, .magnitude = 0U },
    { .action = ACT_WAIT, .direction = DIR_DOWN, .magnitude = 360U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 1U },
    { .action = ACT_TOGGLE_HIDING, .direction = DIR_UP, .magnitude = 0U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 6U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 19U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 3U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 2U },
    { .action = ACT_WAIT, .direction = DIR_UP, .magnitude = 300U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 1U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 4U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 3U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 9U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 8U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 4U },
    { .action = ACT_WAIT, .direction = DIR_DOWN, .magnitude = 600U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 7U }
};
const ActionObject actionsHiki[] = {
    { ACT_WALK, DIR_RIGHT, 3U },
    { ACT_WALK, DIR_DOWN, 5U },
    { ACT_SPECIAL_ACTION, DIR_DOWN, 180U },
    { ACT_WALK, DIR_DOWN, 2U },
    { ACT_WALK, DIR_LEFT, 3U },
    { ACT_WALK, DIR_UP, 1U },
    { ACT_WALK, DIR_LEFT, 5U },
    { ACT_WALK, DIR_UP, 5U },
    { ACT_WAIT, DIR_UP, 90U },
    { ACT_WALK, DIR_DOWN, 2U },
    { ACT_WALK, DIR_RIGHT, 5U },
    { ACT_WALK, DIR_UP, 3U }
};
const ActionObject actionsWhateverDude[] = {
    { ACT_WAIT, DIR_UP, 60U },
    { ACT_WALK, DIR_RIGHT, 5U },
    { ACT_WALK, DIR_DOWN, 4U },
    { ACT_WALK, DIR_RIGHT, 11U },
    { ACT_WALK, DIR_DOWN, 2U },
    { ACT_WALK, DIR_RIGHT, 9U },
    { ACT_WALK, DIR_DOWN, 5U },
    { ACT_WAIT, DIR_UP, 300U },
    { ACT_WALK, DIR_LEFT, 5U },
    { ACT_WALK, DIR_DOWN, 2U },
    { ACT_WALK, DIR_RIGHT, 5U },
    { ACT_WAIT, DIR_RIGHT, 150U },
    { ACT_WAIT, DIR_LEFT, 60U },
    { ACT_WAIT, DIR_RIGHT, 60U },
    { ACT_WALK, DIR_LEFT, 9U },
    { ACT_WALK, DIR_UP, 10U },
    { ACT_WALK, DIR_LEFT, 10U },
    { ACT_WALK, DIR_UP, 3U },
    { ACT_WALK, DIR_LEFT, 6U }
};
const ActionObject actionsBather[] = {
    { ACT_WAIT, DIR_UP, 300U },
    { ACT_WALK, DIR_RIGHT, 8U },
    { ACT_WALK, DIR_UP, 1U },
    { ACT_WALK, DIR_RIGHT, 6U },
    { ACT_WALK, DIR_UP, 1U },
    { ACT_WALK, DIR_RIGHT, 1U },
    { ACT_SPECIAL_ACTION, DIR_DOWN, 300U },
    { ACT_WALK, DIR_LEFT, 3U },
    { ACT_WAIT, DIR_UP, 90U },
    { ACT_WALK, DIR_DOWN, 1U },
    { ACT_WALK, DIR_LEFT, 4U },
    { ACT_WALK, DIR_DOWN, 2U },
    { ACT_WALK, DIR_LEFT, 1U },
    { ACT_WALK, DIR_DOWN, 8U },
    { ACT_WALK, DIR_RIGHT, 7U },
    { ACT_WALK, DIR_DOWN, 11U },
    { ACT_TOGGLE_HIDING, DIR_DOWN, 0U },
    { ACT_WAIT, DIR_DOWN, 450U },
    { ACT_TOGGLE_HIDING, DIR_UP, 0U },
    { ACT_WALK, DIR_UP, 1U },
    { ACT_WALK, DIR_RIGHT, 1U },
    { ACT_WALK, DIR_UP, 5U },
    { ACT_WALK, DIR_RIGHT, 3U },
    { ACT_WALK, DIR_UP, 6U },
    { ACT_WALK, DIR_LEFT, 10U },
    { ACT_WALK, DIR_UP, 8U },
    { ACT_WALK, DIR_LEFT, 8U }
};

// Test
const ActionObject actionsCircle[] = {
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 2U },
    { .action = ACT_SWITCH_ROUTINE, .direction = 8U, .magnitude = 2U }
};
const ActionObject actionsLineAndBack[] = {
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 2U },
    { .action = ACT_SWITCH_ROUTINE, .direction = 8U, .magnitude = 0U }
};
const ActionObject actionsRandLook[] = {
    { .action = ACT_WAIT, .direction = DIR_RAND, .magnitude = 30U }
};

// School
const ActionObject actionsWaterHolder[] = {
    { .action = ACT_WAIT, .direction = DIR_DOWN, .magnitude = 200U },
    { .action = ACT_WAIT, .direction = DIR_UP, .magnitude = 60U }
};
const ActionObject actionsGymRunner[] = {
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 6U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 8U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 6U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 8U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 6U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 8U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 3U },
    { .action = ACT_WAIT, .direction = DIR_DOWN, .magnitude = 60U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 3U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 8U }
};
const ActionObject actionsHookieKid[] = {
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 5U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 4U },
    { .action = ACT_SPECIAL_ACTION, .direction = DIR_DOWN, .magnitude = 120U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 2U },
    { .action = ACT_SPECIAL_ACTION, .direction = DIR_DOWN, .magnitude = 120U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 4U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 3U },
    { .action = ACT_WAIT, .direction = DIR_RIGHT, .magnitude = 150U }
};
const ActionObject actionsTeachersLounger[] = {
    { .action = ACT_WAIT, .direction = DIR_UP, .magnitude = 30U },
    { .action = ACT_WAIT, .direction = DIR_RIGHT, .magnitude = 60U },
    { .action = ACT_WAIT, .direction = DIR_DOWN, .magnitude = 60U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 5U },
    { .action = ACT_WAIT, .direction = DIR_RAND, .magnitude = 15U },
    { .action = ACT_WAIT, .direction = DIR_RAND, .magnitude = 15U },
    { .action = ACT_WAIT, .direction = DIR_RAND, .magnitude = 15U },
    { .action = ACT_WAIT, .direction = DIR_RAND, .magnitude = 15U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 4U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 1U },
    { .action = ACT_WAIT, .direction = DIR_UP, .magnitude = 15U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 1U },
    { .action = ACT_WAIT, .direction = DIR_UP, .magnitude = 15U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 1U },
    { .action = ACT_WAIT, .direction = DIR_UP, .magnitude = 15U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 3U },
    { .action = ACT_WAIT, .direction = DIR_DOWN, .magnitude = 15U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 3U }
};
const ActionObject actionsBlackboardLoop[] = {
    { .action = ACT_SPECIAL_ACTION, .direction = DIR_UP, .magnitude = 120U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 4U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 3U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 4U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 3U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 8U },
    { .action = ACT_SWITCH_ROUTINE, .direction = 28U, .magnitude = 2U }
};
const ActionObject actionsBlackboardRead[] = {
    { .action = ACT_SPECIAL_ACTION, .direction = DIR_UP, .magnitude = 120U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 5U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 1U },
    { .action = ACT_WAIT, .direction = DIR_DOWN, .magnitude = 120U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 1U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 5U },
    { .action = ACT_SWITCH_ROUTINE, .direction = 28U, .magnitude = 2U }
};
const ActionObject actionsPrincipal[] = {
    { .action = ACT_WAIT, .direction = DIR_RAND, .magnitude = 15U },
    { .action = ACT_WAIT, .direction = DIR_RAND, .magnitude = 15U },
    { .action = ACT_WAIT, .direction = DIR_RAND, .magnitude = 15U },
    { .action = ACT_WAIT, .direction = DIR_RAND, .magnitude = 15U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 5U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 5U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 1U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 1U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 21U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 3U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 3U },
    { .action = ACT_WAIT, .direction = DIR_UP, .magnitude = 120U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 4U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 3U },
    { .action = ACT_WAIT, .direction = DIR_RAND, .magnitude = 15U },
    { .action = ACT_WAIT, .direction = DIR_RAND, .magnitude = 15U },
    { .action = ACT_WAIT, .direction = DIR_RAND, .magnitude = 15U },
    { .action = ACT_WAIT, .direction = DIR_RAND, .magnitude = 15U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 3U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 5U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 4U },
    { .action = ACT_WAIT, .direction = DIR_RAND, .magnitude = 15U },
    { .action = ACT_WAIT, .direction = DIR_RAND, .magnitude = 15U },
    { .action = ACT_WAIT, .direction = DIR_RAND, .magnitude = 15U },
    { .action = ACT_WAIT, .direction = DIR_RAND, .magnitude = 15U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 4U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 16U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 5U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 5U }
};


const RoutineObject routineDex[32U] =
{
    // House
    { .length =  7U, .actions = &actionsBathroom },
    { .length = 29U, .actions = &actionsCouchman },
    { .length = 23U, .actions = &actionsWentToGetMilk },
    { .length = 12U, .actions = &actionsHiki },
    { .length = 19U, .actions = &actionsWhateverDude },
    { .length = 27U, .actions = &actionsBather },  // 5

    // Tutorial
    { .length = 2U, .actions = &actionsTutWaiter },
    { .length = 4U, .actions = &actionsTutWalker },

    // Test
    { .length = 5U, .actions = &actionsCircle },
    { .length = 3U, .actions = &actionsLineAndBack },
    { .length = 1U, .actions = &actionsRandLook },  // 10

    // Church
    { .length = 3U, .actions = &actionsUsher },
    { .length = 1U, .actions = &actionsFileCabinet },
    { .length = 32U, .actions = &actionsChurchChecker },
    { .length = 9U, .actions = &actionsPriestCircle },
    { .length = 11U, .actions = &actionsPriestAudience },  // 15
    { .length = 2U, .actions = &actionsPew1Central },
    { .length = 8U, .actions = &actionsPew1Up },
    { .length = 8U, .actions = &actionsPew1Down },
    { .length = 4U, .actions = &actionsPew1Left },
    { .length = 4U, .actions = &actionsPew1Right },  // 20
    { .length = 2U, .actions = &actionsPew2Central },
    { .length = 6U, .actions = &actionsPew2Down },
    { .length = 6U, .actions = &actionsPew2Up },
    
    // School
    { .length = 2U, .actions = &actionsWaterHolder },
    { .length = 10U, .actions = &actionsGymRunner },  // 25
    { .length = 10U, .actions = &actionsHookieKid },
    { .length = 20U, .actions = &actionsTeachersLounger },
    { .length = 7U, .actions = &actionsBlackboardLoop },
    { .length = 7U, .actions = &actionsBlackboardRead },
    { .length = 30U, .actions = &actionsPrincipal }  // 30



};
