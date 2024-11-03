#include "player.h"

#include <SDL2/SDL.h>

#include "core/texture_manager.h"

Player player_create(TextureManager* texture_manager) {
    Player player = {
        .texture = texture_manager_get_texture(texture_manager, "player"),
        .x_0 = 64,
        .y_0 = 32,
        .width = 32,
        .height = 32,
        .y = 0.0f,
        .v_y = 0.0f,
        .v_jump = -40.0f,
        .a_gravity = 240.0f,
        .frozen = true,
    };

    return player;
}

void player_handle_input(Player* player, SDL_Event event) {
    if (player->frozen) {
        return;
    }

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

void player_update(Player* player, float delta_time) {
    if (player->frozen) {
        return;
    }

    // Apply velocity and acceleration
    player->y += player->v_y * delta_time;
    player->v_y += player->a_gravity * delta_time;

    // Check if the player has landed and reset values
    if (player->y >= 1e-5) {
        player->y = 0.0;
        player->v_y = 0.0;
    }
}

void player_render(Player* player, Renderer* renderer) {
    renderer_blit_sprite(
        renderer, &player->texture, player->x_0,
        (uint16_t)((float)player->y_0 + player->y), player->width,
        player->height, 0
    );
}

void player_cleanup(Player* player) {}
