#pragma once

#include <stdbool.h>
#include <stdint.h>

#define TIMER_INFINITE -1.0f
#define TIMER_EXPIRED 0.0f

typedef struct {
    uint64_t start_ticks;
    float duration;
} Timer;

void start_timer(Timer* timer, float duration);
float get_elapsed_time(Timer* timer);
bool is_timer_expired(Timer* timer);
