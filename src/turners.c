#include "turners.h"

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

Turners turners_create(TextureManager* texture_manager) {
    Turners turners = {
        .texture = texture_manager_get_texture(texture_manager, "turners"),
        .frame = 0,
        .frame_count = 8,
        .frame_duration = 0.1f,
        .last_frame_ticks = 0,
        .x_0 = 32,
        .y_0 = 32,
        .width = 96,
        .height = 32,
        .frozen = true,
    };

    return turners;
}

void turners_update(Turners* turners, float delta_time) {
    if (turners->frozen) {
        return;
    }

    // Animate turners
    uint64_t elapsed = SDL_GetPerformanceCounter();
    float frame_delta_time = (float)(elapsed - turners->last_frame_ticks) /
                             SDL_GetPerformanceFrequency();

    if (frame_delta_time >= turners->frame_duration) {
        turners->frame = (turners->frame + 1) % turners->frame_count;
        turners->last_frame_ticks = elapsed;
    }
}

void turners_render(Turners* turners, Renderer* renderer) {
    renderer_blit_sprite(
        renderer, &turners->texture, turners->x_0, turners->y_0, turners->width,
        turners->height, turners->frame
    );
}

void turners_cleanup(Turners* turners) {}

uint16_t turners_get_z_index(Turners* turners) {
    return (turners->frame >= 0 && turners->frame < turners->frame_count / 2)
               ? 0
               : 1;
}
