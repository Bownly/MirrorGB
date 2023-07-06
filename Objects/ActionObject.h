#include <gb/gb.h>
#include "../Engine/enums.h"

#ifndef ACTIONOBJECT_H
#define ACTIONOBJECT_H

typedef struct ActionObject {
    ACTION action;
    UINT8 arg;
} ActionObject;

#endif