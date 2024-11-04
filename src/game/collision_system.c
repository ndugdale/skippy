#include "game/collision_system.h"

#include "game/game_manager.h"
#include "game/player.h"
#include "game/turners.h"

void collision_system_init(
    CollisionSystem* collision_system, Player* player, Turners* turners
) {
    collision_system->player = player;
    collision_system->turners = turners;
}

void collision_system_update(
    CollisionSystem* collision_system, GameManager* game_manager,
    float delta_time
) {
    game_manager->running =
        !(collision_system->turners->frame == 0 &&
          collision_system->player->y >= 0.0);
}

void collision_system_cleanup(CollisionSystem* collision_system) {}
