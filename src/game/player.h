#pragma once

#include <stdint.h>

#include "core/renderer.h"
#include "core/texture.h"
#include "core/texture_manager.h"
#include "event/event.h"
#include "game/game_manager.h"

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
} Player;

void player_init(Player* player, TextureManager* texture_manager);
void player_handle_event(
    Player* player, GameManager* game_manager, Event event
);
void player_update(Player* player, GameManager* game_manager, float delta_time);
void player_render(Player* player, Renderer* renderer);
void player_cleanup(Player* player);
