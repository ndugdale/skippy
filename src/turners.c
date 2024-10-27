#include "turners.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdint.h>

Turners turners_create(SDL_Renderer* renderer) {
    Turners turners = {
        .texture = IMG_LoadTexture(renderer, "assets/sprites/turners.png"),
        .frame = 0,
        .frame_count = 8,
        .frame_duration = 0.1f,
        .last_frame_ticks = 0,
        .x_0 = 32,
        .y_0 = 32,
        .width = 96,
        .height = 32,
    };

    if (turners.texture == NULL) {
        // error
    }

    return turners;
}

void turners_update(Turners* turners, float delta_time) {
    // Animate turners
    uint64_t elapsed = SDL_GetPerformanceCounter();
    float frame_delta_time = (float)(elapsed - turners->last_frame_ticks) /
                             SDL_GetPerformanceFrequency();

    if (frame_delta_time >= turners->frame_duration) {
        turners->frame = (turners->frame + 1) % turners->frame_count;
        turners->last_frame_ticks = elapsed;
    }
}

void turners_render(Turners* turners, SDL_Renderer* renderer) {
    SDL_Rect src_rect = {
        turners->frame * turners->width, 0, turners->width, turners->height
    };
    SDL_Rect dest_rect = {
        turners->x_0, turners->y_0, turners->width, turners->height
    };
    SDL_RenderCopy(renderer, turners->texture, &src_rect, &dest_rect);
}

void turners_cleanup(Turners* turners) { SDL_DestroyTexture(turners->texture); }
