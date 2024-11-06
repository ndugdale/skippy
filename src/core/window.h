#pragma once

#include <stdint.h>

typedef struct {
    uint16_t width;
    uint16_t height;
    void* platform_window;
} Window;

void window_init(Window* window, const char* title);
void window_resize(Window* window, uint16_t width, uint16_t height);
void window_close(Window* window);
void window_cleanup(Window* window);
