#pragma once

#include <stdint.h>

typedef struct {
    uint64_t elapsed_count;
    float delta_time;
} Clock;

Clock clock_create();
float clock_tick(Clock* clock);
