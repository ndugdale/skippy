#include "game/player.h"

#include "core/texture_manager.h"
#include "event/event.h"
#include "game/game_manager.h"

void player_init(Player* player, TextureManager* texture_manager) {
    player->texture = texture_manager_get_texture(texture_manager, "player");
    player->x_0 = 64;
    player->y_0 = 32;
    player->width = 32;
    player->height = 32;
    player->y = 0.0f;
    player->v_y = 0.0f;
    player->v_jump = -40.0f;
    player->a_gravity = 240.0f;
}

void player_handle_event(
    Player* player, GameManager* game_manager, Event event
) {
    switch (event.type) {
        case KEY_PRESS_EVENT:
            if (event.key_press.keycode == KEYCODE_SPACE &&
                game_manager->running) {
                if (player->y >= 0.0f) {
                    player->v_y = player->v_jump;
                }
            }
            break;
        default:
            break;
    }
}

void player_update(
    Player* player, GameManager* game_manager, float delta_time
) {
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
