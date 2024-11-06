#include "core/texture.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "core/log.h"
#include "core/renderer.h"

Texture load_texture(Renderer* renderer, const char* path) {
    SDL_Texture* platform_texture =
        IMG_LoadTexture(renderer->platform_renderer, path);
    ASSERT(
        platform_texture != NULL, "Failed to load SDL_Texture from path %s",
        path
    );

    Texture texture = {
        .path = path,
        .platform_texture = platform_texture,
    };

    return texture;
}

void unload_texture(Texture* texture) {
    SDL_DestroyTexture(texture->platform_texture);
}
