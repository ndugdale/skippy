#pragma once

#include <stdint.h>

#include "core/window.h"

#define RENDERER_SCALE 8.0f

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} Color;

typedef struct {
    void* platform_renderer;
} Renderer;

void renderer_init(Renderer* renderer, Window* window);
void renderer_clear(
    Renderer* renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a
);
void renderer_present(Renderer* renderer);
void renderer_cleanup(Renderer* renderer);
