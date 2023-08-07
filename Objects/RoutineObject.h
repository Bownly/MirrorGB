#include <gb/gb.h>
#include "../Engine/enums.h"
#include "ActionObject.h"

#ifndef ROUTINEOBJECT_H
#define ROUTINEOBJECT_H

typedef struct RoutineObject {
    UINT8 length;
    ActionObject (*actions)[];
} RoutineObject;

#endif