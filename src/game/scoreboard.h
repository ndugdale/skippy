#pragma once

#include <stdint.h>

#include "core/entity.h"
#include "core/font.h"

#define SCOREBOARD_ID "scoreboard"
#define SCOREBOARD_FONT_SIZE 64
#define SCOREBOARD_COLOR ((Color){.r = 170, .g = 157, .b = 246})
#define SCOREBOARD_Z_INDEX 0
#define SCOREBOARD_BUFFER_SIZE 8
#define SCOREBOARD_CENTER_X_OFFSET -2
#define SCOREBOARD_CENTER_Y_OFFSET 36

typedef struct {
    uint16_t score;
    Font font;
    int32_t x;
    int32_t y;
} Scoreboard;

void create_scoreboard(EntityManager* entity_manager, void* dependencies);
