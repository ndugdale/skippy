#include <stdint.h>

#include "core/font.h"
#include "renderer/renderer.h"
#include "renderer/texture.h"

void draw_sprite(
    Renderer* renderer, Texture* texture, int32_t x, int32_t y, uint16_t width,
    uint16_t height, uint16_t frame
);
void draw_text(
    Renderer* renderer, Font* font, const char* text, Color color, int32_t x,
    int32_t y
);
