#pragma once

#include <stdbool.h>

#include "core/audio.h"
#include "core/entity.h"
#include "core/timer.h"

#define GAME_MANAGER_ID "game_manager"
#define GAME_MANAGER_GRACE_PERIOD_DURATION 0.1
#define GAME_MANAGER_RESTART_PERIOD_DURATION 0.5

typedef struct {
    bool running;
    AudioEffect round_end_audio_effect;
    Timer grace_timer;
    Timer restart_timer;
} GameManager;

void create_game_manager(EntityManager* entity_manager, void* dependencies);
