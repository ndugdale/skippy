#include "player.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <stdint.h>

Player player_create(SDL_Renderer* renderer) {
    Player player = {
        .texture = IMG_LoadTexture(renderer, "assets/sprites/player.png"),
        .x_0 = 32,
        .y_0 = 32,
        .width = 32,
        .height = 32,
        .y = 0.0f,
        .v_y = 0.0f,
        .v_jump = -40.0f,
        .a_gravity = 240.0f,
    };

    if (player.texture == NULL) {
        // error
    }

    return player;
}

void player_handle_input(Player* player, SDL_Event event) {
    switch (event.type) {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_SPACE:
            if (player->y >= 0.0f) {
                player->v_y = player->v_jump;
            }
        default:
            break;
        }
        break;
    default:
        break;
    }
}

void player_update(Player* player, double delta_time) {
    // Apply velocity and acceleration
    player->y += player->v_y * delta_time;
    player->v_y += player->a_gravity * delta_time;

    // Check if the player has landed and reset values
    if (player->y >= 1e-5) {
        player->y = 0.0;
        player->v_y = 0.0;
    }
}

void player_render(Player* player, SDL_Renderer* renderer) {
    SDL_Rect dest_rect = {
        player->x_0, (uint16_t)((float)player->y_0 + player->y), player->width,
        player->height
    };
    SDL_RenderCopy(renderer, player->texture, NULL, &dest_rect);
}

void player_cleanup(Player* player) { SDL_DestroyTexture(player->texture); }
