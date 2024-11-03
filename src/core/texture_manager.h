#pragma once

#include <stdint.h>

#include "core/renderer.h"
#include "core/texture.h"
#include "core/texture_manager.h"

#define MAX_NUM_TEXTURES 255

typedef struct {
    Texture textures[MAX_NUM_TEXTURES];
    uint16_t insert_index;
} TextureManager;

TextureManager texture_manager_create(Renderer* renderer);
Texture texture_manager_get_texture(
    TextureManager* texture_manager, const char* id
);
void texture_manager_destroy(TextureManager* texture_manager);
