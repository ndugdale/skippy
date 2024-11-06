#include "renderer.h"

#include <SDL2/SDL.h>

#include "core/log.h"
#include "window.h"

void renderer_init(Renderer* renderer, Window* window) {
    void* platform_renderer = SDL_CreateRenderer(
        window->platform_window, -1, SDL_RENDERER_ACCELERATED
    );
    ASSERT(platform_renderer != NULL, "Failed to create SDL_Renderer");

    SDL_RenderSetScale(platform_renderer, RENDERER_SCALE, RENDERER_SCALE);
    renderer->platform_renderer = platform_renderer;
}

void renderer_clear(
    Renderer* renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a
) {
    SDL_SetRenderDrawColor(renderer->platform_renderer, r, g, b, a);
    SDL_RenderClear(renderer->platform_renderer);
}

void renderer_present(Renderer* renderer) {
    SDL_RenderPresent(renderer->platform_renderer);
}

void renderer_cleanup(Renderer* renderer) {
    SDL_DestroyRenderer(renderer->platform_renderer);
}
