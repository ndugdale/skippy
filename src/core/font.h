#pragma once

#include <stdint.h>

typedef struct {
    const char* path;
    uint16_t size;
    void* platform_font;
} Font;

Font load_font(const char* path, uint16_t size);
uint16_t get_text_width(Font* font, const char* text);
uint16_t get_text_height(Font* font, const char* text);
void unload_font(Font* font);
