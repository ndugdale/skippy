#pragma once

#include "game/game_manager.h"
#include "game/player.h"
#include "game/turners.h"

typedef struct {
    Player* player;
    Turners* turners;
} CollisionSystem;

void collision_system_init(
    CollisionSystem* collision_system, Player* player, Turners* turners
);
void collision_system_update(
    CollisionSystem* collision_system, GameManager* game_manager,
    float delta_time
);
void collision_system_cleanup(CollisionSystem* collision_system);
