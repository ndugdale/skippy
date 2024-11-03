#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

#include "core/renderer.h"
#include "core/texture.h"
#include "core/texture_manager.h"

typedef struct {
    Texture texture;
    uint16_t frame;
    uint16_t frame_count;
    float frame_duration;
    uint64_t last_frame_ticks;
    uint16_t x_0;
    uint16_t y_0;
    uint16_t width;
    uint16_t height;
    bool frozen;
} Turners;

Turners turners_create(TextureManager* texture_manager);
void turners_update(Turners* turners, float delta_time);
void turners_render(Turners* turners, Renderer* renderer);
void turners_cleanup(Turners* turners);
uint16_t turners_get_z_index(Turners* turners);
