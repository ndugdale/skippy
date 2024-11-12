#pragma once

#include <stdint.h>

#include "core/entity.h"
#include "core/texture.h"
#include "core/timer.h"

#define TURNERS_ID "turners"
#define TURNERS_WIDTH 96
#define TURNERS_HEIGHT 32
#define TURNERS_FRAME_COUNT 8
#define TURNERS_Z_INDEX_BACK 0
#define TURNERS_Z_INDEX_FRONT 2

typedef struct {
    Texture texture;
    uint16_t frame;
    float frame_duration;
    Timer frame_timer;
    int32_t x;
    int32_t y;
} Turners;

void create_turners(EntityManager* entity_manager, void* dependencies);
