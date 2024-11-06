#pragma once

#include "core/renderer.h"

typedef struct {
    const char* path;
    void* platform_texture;
} Texture;

Texture load_texture(Renderer* renderer, const char* path);
void unload_texture(Texture* texture);
