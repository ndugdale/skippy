#pragma once

#include <stdint.h>

#include "core/audio.h"
#include "core/entity.h"
#include "core/texture.h"

#define PLAYER_ID "player"
#define PLAYER_WIDTH 32
#define PLAYER_HEIGHT 32
#define PLAYER_JUMP_VELOCITY -40.0f         // pixels/s
#define PLAYER_GRAVITY_ACCELERATION 240.0f  // pixels/s^2
#define PLAYER_Z_INDEX 1

typedef struct {
    Texture texture;
    AudioEffect jump_audio_effect;
    int32_t x;
    int32_t y;
    float y_jump;
    float v_y;
} Player;

void create_player(EntityManager* entity_manager, void* dependencies);
