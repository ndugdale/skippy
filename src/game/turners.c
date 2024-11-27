#include "game/turners.h"

#include "core/dependencies.h"
#include "core/draw.h"
#include "core/entity.h"
#include "core/texture.h"
#include "core/timer.h"
#include "core/window.h"
#include "event/event.h"
#include "game/event.h"
#include "game/game_manager.h"
#include "game/scoreboard.h"

static void init_turners(void* context, void* dependencies);
static void handle_turners_event(
    void* context, void* dependencies, Event event
);
static void update_turners(void* context, void* dependencies, float delta_time);
static void render_turners(void* context, void* dependencies);
static void cleanup_turners(void* context, void* dependencies);

void create_turners(EntityManager* entity_manager, void* dependencies) {
    add_entity(
        entity_manager, dependencies,
        (EntityConfig){
            .id = TURNERS_ID,
            .init = init_turners,
            .handle_event = handle_turners_event,
            .update = update_turners,
            .render = render_turners,
            .cleanup = cleanup_turners,
            .size = sizeof(Turners),
            .z_index = TURNERS_Z_INDEX_BACK,
        }
    );
}

void init_turners(void* context, void* dependencies) {
    Turners* turners = (Turners*)context;
    Window* window = get_window(dependencies);
    Renderer* renderer = get_renderer(dependencies);

    turners->texture = load_texture(renderer, "assets/sprites/turners.png");
    turners->frame = 0;
    turners->frame_duration = TURNERS_MAX_FRAME_DURATION;
    turners->frames_since_rate_change = 0;
    turners->x = window->width / (2 * RENDERER_SCALE) - TURNERS_WIDTH / 2;
    turners->y = window->height / (2 * RENDERER_SCALE) - TURNERS_HEIGHT;

    start_timer(&turners->frame_rate_change_timer, TIMER_EXPIRED);
}

void handle_turners_event(void* context, void* dependencies, Event event) {
    Turners* turners = (Turners*)context;

    switch (event.type) {
        case WINDOW_RESIZE_EVENT:
            turners->x = event.window_resize.width / (2 * RENDERER_SCALE) -
                         TURNERS_WIDTH / 2;
            turners->y = event.window_resize.height / (2 * RENDERER_SCALE) -
                         TURNERS_HEIGHT;
            break;
        case PLAYER_JUMP_EVENT:
            if (turners->frame_duration > TURNERS_MIN_FRAME_DURATION) {
                turners->frame_duration -= TURNERS_DELTA_FRAME_DURATION;
                turners->frames_since_rate_change = 0;

                start_timer(
                    &turners->frame_rate_change_timer, turners->frame_duration
                );
            }
            break;
        case ROUND_START_EVENT:
            turners->frame++;
            turners->frame_duration = TURNERS_MAX_FRAME_DURATION;
            turners->frames_since_rate_change = 0;

            start_timer(
                &turners->frame_rate_change_timer, turners->frame_duration
            );
            break;
        default:
            break;
    }
}

void update_turners(void* context, void* dependencies, float delta_time) {
    Turners* turners = (Turners*)context;
    EntityManager* entity_manager = get_entity_manager(dependencies);
    GameManager* game_manager = get_entity(entity_manager, GAME_MANAGER_ID);
    Scoreboard* scoreboard = get_entity(entity_manager, SCOREBOARD_ID);

    if (!game_manager->running) {
        if (turners->frame != 0) {
            turners->frame = 0;
        }
        return;
    }

    // Animate turners
    if (get_timer_laps(&turners->frame_rate_change_timer) >
        turners->frames_since_rate_change) {
        turners->frame = (turners->frame + 1) % TURNERS_FRAME_COUNT;
        turners->frames_since_rate_change++;

        // Update z-index
        if (turners->frame == 0) {
            update_entity_z_index(
                entity_manager, TURNERS_ID, TURNERS_Z_INDEX_BACK
            );
        } else if (turners->frame == TURNERS_FRAME_COUNT / 2) {
            update_entity_z_index(
                entity_manager, TURNERS_ID, TURNERS_Z_INDEX_FRONT
            );
        }
        // Increment score
        else if (turners->frame == 1 &&
                 is_timer_expired(&game_manager->grace_timer)) {
            handle_entities_event(
                entity_manager, dependencies,
                (Event){.type = SCORE_INCREMENT_EVENT}
            );
        }
    }
}

void render_turners(void* context, void* dependencies) {
    Turners* turners = (Turners*)context;
    Renderer* renderer = get_renderer(dependencies);

    draw_sprite(
        renderer, &turners->texture, turners->x, turners->y, TURNERS_WIDTH,
        TURNERS_HEIGHT, turners->frame
    );
}

void cleanup_turners(void* context, void* dependencies) {
    Turners* turners = (Turners*)context;

    unload_texture(&turners->texture);
}
