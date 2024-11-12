#include "game/game_manager.h"

#include <stdbool.h>

#include "core/dependencies.h"
#include "core/entity.h"
#include "core/timer.h"
#include "event/event.h"
#include "game/collision_manager.h"

static void init_game_manager(void* context, void* dependencies);
static void handle_game_manager_event(
    void* context, void* dependencies, Event event
);
static void update_game_manager(
    void* context, void* dependencies, float delta_time
);

void create_game_manager(EntityManager* entity_manager, void* dependencies) {
    add_entity(
        entity_manager, dependencies,
        (EntityConfig
        ){.id = GAME_MANAGER_ID,
          .init = init_game_manager,
          .handle_event = handle_game_manager_event,
          .update = update_game_manager,
          .render = NULL,
          .cleanup = NULL,
          .size = sizeof(GameManager)}
    );
}

void init_game_manager(void* context, void* dependencies) {
    GameManager* game_manager = (GameManager*)context;

    game_manager->running = false;
    start_timer(&game_manager->grace_timer, TIMER_EXPIRED);
}

void handle_game_manager_event(void* context, void* dependencies, Event event) {
    GameManager* game_manager = (GameManager*)context;

    switch (event.type) {
        case KEY_PRESS_EVENT:
            if (event.key_press.keycode == KEYCODE_SPACE &&
                !game_manager->running) {
                game_manager->running = true;
                start_timer(
                    &game_manager->grace_timer,
                    GAME_MANAGER_GRACE_PERIOD_DURATION
                );
            }
            break;
        default:
            break;
    }
}

void update_game_manager(void* context, void* dependencies, float delta_time) {
    GameManager* game_manager = (GameManager*)context;
    EntityManager* entity_manager = get_entity_manager(dependencies);
    CollisionManager* collision_manager =
        get_entity(entity_manager, dependencies, COLLISION_MANAGER_ID);

    if (is_timer_expired(&game_manager->grace_timer) &&
        collision_manager->collision) {
        game_manager->running = false;
    }
}
