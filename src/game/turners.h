#pragma once

#include <stdint.h>

#include "core/renderer.h"
#include "core/texture.h"
#include "core/texture_manager.h"
#include "core/window.h"
#include "event/event.h"
#include "game/game_manager.h"

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

void turners_init(
    Turners* turners, Window* window, TextureManager* texture_manager
);
void turners_handle_event(
    Turners* turners, GameManager* game_manager, Event event
);
void turners_update(
    Turners* turners, GameManager* game_manager, float delta_time
);
void turners_render(Turners* turners, Renderer* renderer);
void turners_cleanup(Turners* turners);
uint16_t turners_get_z_index(Turners* turners);
