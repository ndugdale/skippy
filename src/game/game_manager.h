#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "core/entity.h"

#define GAME_MANAGER_ID "game_manager"

typedef struct {
    bool running;
    bool in_round_start_grace_period;
    uint64_t round_start_ticks;
    float round_start_grace_period_duration;
} GameManager;

void create_game_manager(EntityManager* entity_manager, void* dependencies);
