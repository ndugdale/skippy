#include "renderer.h"

#include <SDL2/SDL.h>

#include "core/log.h"
#include "texture.h"
#include "window.h"

void renderer_init(Renderer* renderer, Window* window) {
    void* platform_renderer = SDL_CreateRenderer(
        window->platform_window, -1, SDL_RENDERER_ACCELERATED
    );
    ASSERT(platform_renderer != NULL, "Failed to create SDL_Renderer");

    SDL_RenderSetScale(platform_renderer, 8.0, 8.0);
    renderer->platform_renderer = platform_renderer;
}

void renderer_clear(
    Renderer* renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a
) {
    SDL_SetRenderDrawColor(renderer->platform_renderer, r, g, b, a);
    SDL_RenderClear(renderer->platform_renderer);
}

void renderer_blit_sprite(
    Renderer* renderer, Texture* texture, uint16_t x, uint16_t y,
    uint16_t width, uint16_t height, uint16_t frame
) {
    SDL_Rect src_rect = {frame * width, 0, width, height};
    SDL_Rect dest_rect = {x, y, width, height};
    SDL_RenderCopy(
        renderer->platform_renderer, texture->platform_texture, &src_rect,
        &dest_rect
    );
}

void renderer_present(Renderer* renderer) {
    SDL_RenderPresent(renderer->platform_renderer);
}

void renderer_destroy(Renderer* renderer) {
    SDL_DestroyRenderer(renderer->platform_renderer);
}
