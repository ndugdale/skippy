#pragma once

#include <stdint.h>

#include "core/entity.h"
#include "core/timer.h"
#include "renderer/texture.h"

#define TURNERS_ID "turners"
#define TURNERS_WIDTH 96
#define TURNERS_HEIGHT 32
#define TURNERS_FRAME_COUNT 8
#define TURNERS_Z_INDEX_BACK 0
#define TURNERS_Z_INDEX_FRONT 2
#define TURNERS_MAX_FRAME_DURATION 0.1f
#define TURNERS_MIN_FRAME_DURATION 0.06f
#define TURNERS_DELTA_FRAME_DURATION 0.001f
#define TURNERS_CENTER_Y_OFFSET 4

typedef struct {
    Texture texture;
    uint16_t frame;
    float frame_duration;
    Timer frame_rate_change_timer;
    uint16_t frames_since_rate_change;
    int32_t x;
    int32_t y;
} Turners;

void create_turners(EntityManager* entity_manager, void* dependencies);
