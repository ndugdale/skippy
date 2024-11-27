#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "core/entity.h"
#include "core/font.h"
#include "core/renderer.h"

#define PROMPT_ID "prompt"
#define PROMPT_FONT_SIZE 16
#define PROMPT_COLOR ((Color){.r = 170, .g = 157, .b = 246})
#define PROMPT_Z_INDEX 0
#define PROMPT_TEXT "Press space to jump"
#define PROMPT_CENTER_X_OFFSET -2
#define PROMPT_CENTER_Y_OFFSET -28

typedef struct {
    Font font;
    int32_t x;
    int32_t y;
    bool hidden;
} Prompt;

void create_prompt(EntityManager* entity_manager, void* dependencies);
