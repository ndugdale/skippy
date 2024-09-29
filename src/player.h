#pragma once

#include <SDL2/SDL.h>
#include <stdint.h>

typedef struct {
    SDL_Texture* texture;
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
} Player;

void player_init(Player* player, SDL_Renderer* renderer);
void player_handle_input(Player* player);
void player_update(Player* player);
void player_render(Player* player, SDL_Renderer* renderer);
void player_cleanup(Player* player);
