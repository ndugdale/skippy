#include "game/game_manager.h"

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "core/dependencies.h"
#include "core/entity.h"
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
    game_manager->in_round_start_grace_period = false;
    game_manager->round_start_ticks = 0;
    game_manager->round_start_grace_period_duration = 0.1f;
}

void handle_game_manager_event(void* context, void* dependencies, Event event) {
    GameManager* game_manager = (GameManager*)context;

    switch (event.type) {
        case KEY_PRESS_EVENT:
            if (event.key_press.keycode == KEYCODE_SPACE &&
                !game_manager->running) {
                game_manager->running = true;
                // TODO: remove SDL api
                game_manager->round_start_ticks = SDL_GetPerformanceCounter();
                game_manager->in_round_start_grace_period = true;
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

    // TODO: remove SDL api
    uint64_t elapsed = SDL_GetPerformanceCounter();
    float round_duration = (float)(elapsed - game_manager->round_start_ticks) /
                           SDL_GetPerformanceFrequency();

    game_manager->in_round_start_grace_period =
        game_manager->running &&
        round_duration <= game_manager->round_start_grace_period_duration;

    if (!game_manager->in_round_start_grace_period &&
        collision_manager->collision) {
        game_manager->running = false;
    }
}
