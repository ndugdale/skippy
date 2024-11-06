#pragma once

#include <SDL2/SDL.h>
#include <stdint.h>

#include "core/font.h"
#include "core/texture.h"
#include "window.h"

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
void renderer_blit_sprite(
    Renderer* renderer, Texture* texture, int32_t x, int32_t y, uint16_t width,
    uint16_t height, uint16_t frame
);
void renderer_blit_text(
    Renderer* renderer, Font* font, const char* text, Color color, int32_t x,
    int32_t y
);
void renderer_present(Renderer* renderer);
void renderer_destroy(Renderer* renderer);
