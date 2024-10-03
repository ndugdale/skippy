#include "player.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void player_init(Player* player, SDL_Renderer* renderer) {
    player->texture = IMG_LoadTexture(renderer, "assets/sprites/player.png");
    player->x = 32;
    player->y = 32;
    player->width = 32;
    player->height = 32;

    if (player->texture == NULL) {
        // error
    }
}

void player_handle_input(Player* player) {}

void player_update(Player* player) {}

void player_render(Player* player, SDL_Renderer* renderer) {
    SDL_Rect dest_rect = {player->x, player->y, player->width, player->height};
    SDL_RenderCopy(renderer, player->texture, NULL, &dest_rect);
}

void player_cleanup(Player* player) { SDL_DestroyTexture(player->texture); }
