#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "core/entity.h"
#include "core/font.h"
#include "core/renderer.h"

#define HIGHSCORE_ID "highscore"
#define HIGHSCORE_FONT_SIZE 16
#define HIGHSCORE_COLOR ((Color){.r = 170, .g = 157, .b = 246})
#define HIGHSCORE_Z_INDEX 0
#define HIGHSCORE_BUFFER_SIZE 24
#define HIGHSCORE_TEXT "Best"
#define HIGHSCORE_CENTER_X_OFFSET 0
#define HIGHSCORE_CENTER_Y_OFFSET -44

typedef struct {
    Font font;
    int32_t x;
    int32_t y;
    int16_t highscore;
    int16_t score;
    char text[HIGHSCORE_BUFFER_SIZE];
    bool hidden;
} Highscore;

void create_highscore(EntityManager* entity_manager, void* dependencies);
