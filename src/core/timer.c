#include "core/timer.h"

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

void start_timer(Timer* timer, float duration) {
    timer->start_ticks = SDL_GetPerformanceCounter();
    timer->duration = duration;
}

float get_elapsed_time(Timer* timer) {
    uint64_t current_ticks = SDL_GetPerformanceCounter();
    float delta_time = (float)(current_ticks - timer->start_ticks) /
                       SDL_GetPerformanceFrequency();

    return delta_time;
}

bool is_timer_expired(Timer* timer) {
    if (timer->duration == TIMER_INFINITE) {
        return false;
    }
    return get_elapsed_time(timer) >= timer->duration;
}

uint16_t get_timer_laps(Timer* timer) {
    return (uint16_t)(get_elapsed_time(timer) / timer->duration);
}
