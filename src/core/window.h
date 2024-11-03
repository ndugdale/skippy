#pragma once

#include "SDL2/SDL.h"

typedef struct {
    void* platform_window;
} Window;

Window window_create(const char* title);
void window_destroy(Window* window);
