#include "game/collision_manager.h"

#include "core/dependencies.h"
#include "core/entity.h"
#include "event/event.h"
#include "game/event.h"
#include "game/player.h"
#include "game/turners.h"

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
            .init = NULL,
            .handle_event = NULL,
            .update = update_collision_manager,
            .render = NULL,
            .cleanup = NULL,
        }
    );
}

void update_collision_manager(
    void* context, void* dependencies, float delta_time
) {
    EntityManager* entity_manager = get_entity_manager(dependencies);
    Player* player = get_entity(entity_manager, PLAYER_ID);
    Turners* turners = get_entity(entity_manager, TURNERS_ID);

    if (turners->frame == 0 && player->y_jump >= 0.0) {
        handle_entities_event(
            entity_manager, dependencies, (Event){.type = COLLISION_EVENT}
        );
    };
}
