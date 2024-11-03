#pragma once

#include <SDL2/SDL.h>
#include <stdint.h>

#include "core/texture.h"
#include "window.h"

typedef struct {
    void* platform_renderer;
} Renderer;

void renderer_init(Renderer* renderer, Window* window);
void renderer_clear(
    Renderer* renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a
);
void renderer_blit_sprite(
    Renderer* renderer, Texture* texture, uint16_t x, uint16_t y,
    uint16_t width, uint16_t height, uint16_t frame
);
void renderer_present(Renderer* renderer);
void renderer_destroy(Renderer* renderer);
