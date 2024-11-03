#pragma once

#include <stdint.h>

typedef struct {
    uint64_t elapsed_ticks;
    float delta_time;
} Clock;

void clock_init(Clock* clock);
float clock_tick(Clock* clock);
