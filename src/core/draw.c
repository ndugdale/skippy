#include "core/draw.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdint.h>

#include "core/font.h"
#include "core/log.h"
#include "core/renderer.h"
#include "core/texture.h"

void draw_sprite(
    Renderer* renderer, Texture* texture, int32_t x, int32_t y, uint16_t width,
    uint16_t height, uint16_t frame
) {
    uint32_t dst_x;
    uint32_t dst_y;
    uint32_t src_x;
    uint32_t src_y;
    uint32_t rect_w = 0;
    uint32_t rect_h = 0;

    if (x >= 0) {
        dst_x = x;
        src_x = 0;
        rect_w = width;
    } else if (x + (int32_t)width >= 0) {
        dst_x = 0;
        src_x = -x;
        rect_w = width + x;
    }

    if (y >= 0) {
        dst_y = y;
        src_y = 0;
        rect_h = height;
    } else if (y + (int32_t)height >= 0) {
        dst_y = 0;
        src_y = -y;
        rect_h = height + y;
    }

    if (rect_w > 0 && rect_h > 0) {
        const SDL_Rect src_rect = {
            frame * width + src_x, src_y, rect_w, rect_h
        };
        const SDL_Rect dest_rect = {dst_x, dst_y, rect_w, rect_h};

        ASSERT(
            SDL_RenderCopy(
                renderer->platform_renderer, texture->platform_texture,
                &src_rect, &dest_rect
            ) == 0,
            "Failed to render sprite with texture from path %s", texture->path
        );
    }
}

void draw_text(
    Renderer* renderer, Font* font, const char* text, Color color, int32_t x,
    int32_t y
) {
    const SDL_Color text_color = {
        .r = color.r, .g = color.g, .b = color.b, .a = color.a
    };
    SDL_Surface* text_surface =
        TTF_RenderText_Solid(font->platform_font, text, text_color);
    SDL_Texture* text_texture =
        SDL_CreateTextureFromSurface(renderer->platform_renderer, text_surface);

    const SDL_Rect dest_rect = {
        .x = x,
        .y = y,
        .w = text_surface->w,
        .h = text_surface->h,
    };

    ASSERT(
        SDL_RenderCopy(
            renderer->platform_renderer, text_texture, NULL, &dest_rect
        ) == 0,
        "Failed to render text '%s' using font from path %s with size %d", text,
        font->path, font->size
    );

    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text_surface);
}
