#pragma once

#include <stdint.h>

#include "core/entity.h"
#include "core/texture.h"

#define PLAYER_ID "player"

typedef struct {
    Texture texture;
    int32_t x_0;
    int32_t y_0;
    uint16_t width;
    uint16_t height;
    float y;
    float v_y;
    float v_jump;     // pixels/s
    float a_gravity;  // pixels/s^2
} Player;

void create_player(EntityManager* entity_manager, void* dependencies);
