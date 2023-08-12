#include <gb/gb.h>

#include "../Engine/enums.h"
#include "../Objects/ActionObject.h"
#include "../Objects/RoutineObject.h"



const ActionObject actionsGreen[] = {
    { .action = ACT_WAIT, .direction = DIR_UP, .magnitude = 1200U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 1U },
    { .action = ACT_WAIT, .direction = DIR_UP, .magnitude = 30U },
    { .action = ACT_WAIT, .direction = DIR_LEFT, .magnitude = 30U },
    { .action = ACT_WAIT, .direction = DIR_RIGHT, .magnitude = 30U },
    { .action = ACT_WAIT, .direction = DIR_DOWN, .magnitude = 90U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 1U }
};
const ActionObject actionsYellow[] = {
    { .action = ACT_WAIT, .direction = DIR_UP, .magnitude = 1200U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 5U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 6U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 11U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 2U },
    { .action = ACT_WALK, .direction = DIR_UP, .magnitude = 3U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 2U },
    { .action = ACT_WAIT, .direction = DIR_DOWN, .magnitude = 300U },
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
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 4U },
    { .action = ACT_WAIT, .direction = DIR_DOWN, .magnitude = 600U },
    { .action = ACT_WALK, .direction = DIR_LEFT, .magnitude = 1U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 4U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 4U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 7U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 6U },
    { .action = ACT_WALK, .direction = DIR_DOWN, .magnitude = 7U },
    { .action = ACT_WALK, .direction = DIR_RIGHT, .magnitude = 11U }
};
const ActionObject actionsRed[] = {
    { .action = ACT_TOGGLE_HIDING, .direction = DIR_DOWN, .magnitude = 0U },
    { .action = ACT_WAIT, .direction = DIR_DOWN, .magnitude = 1200U },
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
const ActionObject actionsCyan[] = {
    { ACT_WALK, DIR_RIGHT, 3U },
    { ACT_WALK, DIR_DOWN, 5U },
    { ACT_WAIT, DIR_LEFT, 300U },
    { ACT_WALK, DIR_DOWN, 2U },
    { ACT_WALK, DIR_LEFT, 3U },
    { ACT_WALK, DIR_UP, 1U },
    { ACT_WALK, DIR_LEFT, 5U },
    { ACT_WALK, DIR_UP, 5U },
    { ACT_WAIT, DIR_UP, 180U },
    { ACT_WALK, DIR_DOWN, 2U },
    { ACT_WALK, DIR_RIGHT, 5U },
    { ACT_WALK, DIR_UP, 3U }
};
const ActionObject actionsBlue[] = {
    { ACT_WAIT, DIR_UP, 1200U },
    { ACT_WALK, DIR_RIGHT, 5U },
    { ACT_WALK, DIR_DOWN, 4U },
    { ACT_WALK, DIR_RIGHT, 11U },
    { ACT_WALK, DIR_DOWN, 2U },
    { ACT_WALK, DIR_RIGHT, 9U },
    { ACT_WALK, DIR_DOWN, 5U },
    { ACT_WAIT, DIR_UP, 600U },
    { ACT_WALK, DIR_LEFT, 5U },
    { ACT_WALK, DIR_DOWN, 2U },
    { ACT_WALK, DIR_RIGHT, 5U },
    { ACT_WAIT, DIR_RIGHT, 300U },
    { ACT_WAIT, DIR_LEFT, 120U },
    { ACT_WAIT, DIR_RIGHT, 120U },
    { ACT_WALK, DIR_LEFT, 9U },
    { ACT_WALK, DIR_UP, 10U },
    { ACT_WALK, DIR_LEFT, 10U },
    { ACT_WALK, DIR_UP, 3U },
    { ACT_WALK, DIR_LEFT, 6U }
};
const ActionObject actionsMagenta[] = {
    { ACT_WAIT, DIR_UP, 1200U },
    { ACT_WALK, DIR_RIGHT, 8U },
    { ACT_WALK, DIR_UP, 1U },
    { ACT_WALK, DIR_RIGHT, 7U },
    { ACT_WAIT, DIR_LEFT, 1200U },
    { ACT_WALK, DIR_LEFT, 3U },
    { ACT_WALK, DIR_UP, 1U },
    { ACT_WAIT, DIR_UP, 180U },
    { ACT_WALK, DIR_DOWN, 1U },
    { ACT_WALK, DIR_LEFT, 4U },
    { ACT_WALK, DIR_DOWN, 2U },
    { ACT_WALK, DIR_LEFT, 1U },
    { ACT_WALK, DIR_DOWN, 8U },
    { ACT_WALK, DIR_RIGHT, 7U },
    { ACT_WALK, DIR_DOWN, 10U },
    { ACT_TOGGLE_HIDING, DIR_DOWN, 0U },
    { ACT_WAIT, DIR_DOWN, 1200U },
    { ACT_TOGGLE_HIDING, DIR_UP, 0U },
    { ACT_WALK, DIR_RIGHT, 1U },
    { ACT_WALK, DIR_UP, 5U },
    { ACT_WALK, DIR_RIGHT, 3U },
    { ACT_WALK, DIR_UP, 6U },
    { ACT_WALK, DIR_LEFT, 10U },
    { ACT_WALK, DIR_UP, 8U },
    { ACT_WALK, DIR_LEFT, 8U }
};



const RoutineObject routineDex[6U] =
    // House map
    {
        // House green
        {
            .length = 7U,
            .actions = &actionsGreen
        },
        // House yellow
        {
            .length = 27U,
            .actions = &actionsYellow
        },
        // House red
        {
            .length = 22U,
            .actions = &actionsRed
        },
        // House cyan
        {
            .length = 12U,
            .actions = &actionsCyan
        },
        // House blue
        {
            .length = 19U,
            .actions = &actionsBlue
        },
        // House magenta
        {
            .length = 25U,
            .actions = &actionsMagenta
        }

    };
