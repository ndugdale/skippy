#pragma once

#include <stdint.h>

#include "core/entity.h"
#include "core/texture.h"

#define TURNERS_ID "turners"

typedef struct {
    Texture texture;
    uint16_t frame;
    uint16_t frame_count;
    float frame_duration;
    uint64_t last_frame_ticks;
    int32_t x_0;
    int32_t y_0;
    uint16_t width;
    uint16_t height;
} Turners;

void create_turners(EntityManager* entity_manager, void* dependencies);
