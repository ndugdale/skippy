#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

#include "core/renderer.h"
#include "core/texture.h"
#include "core/texture_manager.h"

typedef struct {
    Texture texture;
    uint16_t x_0;
    uint16_t y_0;
    uint16_t width;
    uint16_t height;
    float y;
    float v_y;
    float v_jump;     // pixels/s
    float a_gravity;  // pixels/s^2
    bool frozen;
} Player;

Player player_create(TextureManager* texture_manager);
void player_handle_input(Player* player, SDL_Event event);
void player_update(Player* player, float delta_time);
void player_render(Player* player, Renderer* renderer);
void player_cleanup(Player* player);
