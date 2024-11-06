#include "core/font.h"

#include <SDL2/SDL_ttf.h>

#include "core/log.h"

Font load_font(const char* path, uint16_t size) {
    TTF_Font* platform_font = TTF_OpenFont(path, size);
    ASSERT(
        platform_font != NULL,
        "Failed to load TTF_Font from path %s with size %d", path, size
    );

    Font font = {
        .path = path,
        .size = size,
        .platform_font = platform_font,
    };

    return font;
}

uint16_t get_text_width(Font* font, const char* text) {
    int32_t width;
    TTF_SizeText(font->platform_font, text, &width, NULL);

    return (uint16_t)width;
}

uint16_t get_text_height(Font* font, const char* text) {
    int32_t height;
    TTF_SizeText(font->platform_font, text, NULL, &height);

    return (uint16_t)height;
}

void unload_font(Font* font) { TTF_CloseFont(font->platform_font); }
