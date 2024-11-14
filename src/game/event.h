#pragma once

#include "event/event.h"

typedef enum {
    ROUND_START_EVENT = CUSTOM_EVENT,
    ROUND_END_EVENT,
    PLAYER_JUMP_EVENT,
    SCORE_INCREMENT_EVENT,
    COLLISION_EVENT,
} GameEventType;

typedef struct {
    GameEventType type;
} GameEvent;
