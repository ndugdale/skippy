#include "game/game_manager.h"

#include <stdbool.h>

#include "core/audio.h"
#include "core/dependencies.h"
#include "core/entity.h"
#include "core/timer.h"
#include "core/utils.h"
#include "event/event.h"
#include "game/event.h"

static void init_game_manager(void* context, void* dependencies);
static void handle_game_manager_event(
    void* context, void* dependencies, Event event
);
static void cleanup_game_manager(void* context, void* dependencies);

void create_game_manager(EntityManager* entity_manager, void* dependencies) {
    add_entity(
        entity_manager, dependencies,
        (EntityConfig){
            .id = GAME_MANAGER_ID,
            .init = init_game_manager,
            .handle_event = handle_game_manager_event,
            .update = NULL,
            .render = NULL,
            .cleanup = cleanup_game_manager,
            .size = sizeof(GameManager),
        }
    );
}

void init_game_manager(void* context, void* dependencies) {
    UNUSED(dependencies);
    GameManager* game_manager = (GameManager*)context;

    game_manager->running = false;
    game_manager->round_end_audio_effect =
        load_audio_effect("assets/audio/round_end.wav");
    start_timer(&game_manager->grace_timer, TIMER_EXPIRED);
    start_timer(&game_manager->restart_timer, TIMER_EXPIRED);
}

void handle_game_manager_event(void* context, void* dependencies, Event event) {
    GameManager* game_manager = (GameManager*)context;
    EntityManager* entity_manager = get_entity_manager(dependencies);

    switch (event.type) {
        case KEY_PRESS_EVENT:
            if (event.key_press.keycode == KEYCODE_SPACE) {
                if (!game_manager->running &&
                    is_timer_expired(&game_manager->restart_timer)) {
                    handle_entities_event(
                        entity_manager, dependencies,
                        (Event){.type = ROUND_START_EVENT}
                    );
                    break;
                }
                if (game_manager->running &&
                    is_timer_expired(&game_manager->grace_timer)) {
                    handle_entities_event(
                        entity_manager, dependencies,
                        (Event){.type = PLAYER_JUMP_EVENT}
                    );
                    break;
                }
                break;
            }
            break;
        case ROUND_START_EVENT:
            game_manager->running = true;
            start_timer(
                &game_manager->grace_timer, GAME_MANAGER_GRACE_PERIOD_DURATION
            );
            break;
        case ROUND_END_EVENT:
            game_manager->running = false;
            play_audio_effect(&game_manager->round_end_audio_effect);
            start_timer(
                &game_manager->restart_timer,
                GAME_MANAGER_RESTART_PERIOD_DURATION
            );
            break;
        case COLLISION_EVENT:
            if (game_manager->running &&
                is_timer_expired(&game_manager->grace_timer)) {
                handle_entities_event(
                    entity_manager, dependencies,
                    (Event){.type = ROUND_END_EVENT}
                );
            }
            break;
        default:
            break;
    }
}

void cleanup_game_manager(void* context, void* dependencies) {
    UNUSED(dependencies);
    GameManager* game_manager = (GameManager*)context;

    unload_audio_effect(&game_manager->round_end_audio_effect);
}
