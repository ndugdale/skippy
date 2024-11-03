#include "core/texture_manager.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stddef.h>

#include "core/log.h"
#include "core/renderer.h"
#include "core/texture.h"

static void texture_manager_load_texture(
    TextureManager* texture_manager, Renderer* renderer, const char* id,
    const char* path
);

TextureManager texture_manager_create(Renderer* renderer) {
    TextureManager texture_manager;
    texture_manager.insert_index = 0;

    texture_manager_load_texture(
        &texture_manager, renderer, "player", "assets/sprites/player.png"
    );
    texture_manager_load_texture(
        &texture_manager, renderer, "turners", "assets/sprites/turners.png"
    );

    return texture_manager;
}

Texture texture_manager_get_texture(
    TextureManager* texture_manager, const char* id
) {
    for (size_t i = 0; i < texture_manager->insert_index; i++) {
        if (strcmp(texture_manager->textures[i].id, id) == 0) {
            return texture_manager->textures[i];
        }
    }

    ASSERT(false, "Failed to find texture with id %s", id);
}

void texture_manager_destroy(TextureManager* texture_manager) {
    for (size_t i = 0; i < texture_manager->insert_index; i++) {
        SDL_DestroyTexture(texture_manager->textures[i].platform_texture);
    }
}

void texture_manager_load_texture(
    TextureManager* texture_manager, Renderer* renderer, const char* id,
    const char* path
) {
    ASSERT(
        texture_manager->insert_index < MAX_NUM_TEXTURES - 1,
        "Failed to load texture with id %s because the maximum number of "
        "loaded textures has been reached",
        id
    );

    SDL_Texture* texture = IMG_LoadTexture(renderer->platform_renderer, path);
    ASSERT(texture != NULL, "Failed to load SDL_Texture with id %s", id);

    Texture insert_item = {
        .id = id,
        .platform_texture = texture,
    };

    texture_manager->textures[texture_manager->insert_index] = insert_item;
    texture_manager->insert_index++;
}
