#pragma once

#include <SDL2/SDL.h>
#include <stdint.h>

typedef struct {
    SDL_Texture* texture;
    uint16_t frame;
    uint16_t frame_count;
    float frame_duration;
    uint64_t last_frame_ticks;
    uint16_t x_0;
    uint16_t y_0;
    uint16_t width;
    uint16_t height;
} Turners;

Turners turners_create(SDL_Renderer* renderer);
void turners_update(Turners* turners, float delta_time);
void turners_render(Turners* turners, SDL_Renderer* renderer);
void turners_cleanup(Turners* turners);
uint16_t turners_get_z_index(Turners* turners);
