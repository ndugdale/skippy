#include "core/clock.h"

#include <SDL2/SDL.h>
#include <stdint.h>

void clock_init(Clock* clock) {
    clock->elapsed_ticks = 0;
    clock->delta_time = 0.0f;
}

float clock_tick(Clock* clock) {
    uint64_t elapsed = SDL_GetPerformanceCounter();
    clock->delta_time =
        (float)(elapsed - clock->elapsed_ticks) / SDL_GetPerformanceFrequency();
    clock->elapsed_ticks = elapsed;

    return clock->delta_time;
}
