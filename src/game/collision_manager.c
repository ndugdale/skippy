#include "game/collision_manager.h"

#include "core/dependencies.h"
#include "core/entity.h"
#include "game/player.h"
#include "game/turners.h"

static void init_collision_manager(void* context, void* dependencies);
static void update_collision_manager(
    void* context, void* dependencies, float delta_time
);

void create_collision_manager(
    EntityManager* entity_manager, void* dependencies
) {
    add_entity(
        entity_manager, dependencies,
        (EntityConfig){
            .id = COLLISION_MANAGER_ID,
            .init = init_collision_manager,
            .handle_event = NULL,
            .update = update_collision_manager,
            .render = NULL,
            .cleanup = NULL,
        }
    );
}

void init_collision_manager(void* context, void* dependencies) {
    CollisionManager* collision_manager = (CollisionManager*)context;

    collision_manager->collision = false;
}

void update_collision_manager(
    void* context, void* dependencies, float delta_time
) {
    CollisionManager* collision_manager = (CollisionManager*)context;
    EntityManager* entity_manager = get_entity_manager(dependencies);
    Player* player = get_entity(entity_manager, dependencies, PLAYER_ID);
    Turners* turners = get_entity(entity_manager, dependencies, TURNERS_ID);

    collision_manager->collision = turners->frame == 0 && player->y >= 0.0;
}
