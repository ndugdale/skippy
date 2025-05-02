#include "renderer/renderer.h"

#include <SDL2/SDL.h>

#include "core/log.h"
#include "core/window.h"

void renderer_init(Renderer* renderer, Window* window) {
    void* platform_renderer = SDL_CreateRenderer(
        window->platform_window, -1, SDL_RENDERER_ACCELERATED
    );
    ASSERT(platform_renderer != NULL, "Failed to create SDL_Renderer");
 
    int renderer_width;
    int renderer_height;
    SDL_GetRendererOutputSize(platform_renderer, &renderer_width, &renderer_height);
	
    float width_scale = (float)renderer_width / (float) window->width;
	float height_scale = (float)renderer_height / (float) window->height;
	SDL_RenderSetScale(platform_renderer, width_scale * RENDERER_SCALE, height_scale * RENDERER_SCALE);

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
