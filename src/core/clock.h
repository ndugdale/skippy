#pragma once

#include <stdint.h>

typedef struct {
    uint64_t elapsed_ticks;
    float delta_time;
} Clock;

Clock clock_create();
float clock_tick(Clock* clock);
