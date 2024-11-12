#include "game/turners.h"

#include <stdint.h>

#include "core/dependencies.h"
#include "core/draw.h"
#include "core/entity.h"
#include "core/texture.h"
#include "core/timer.h"
#include "core/window.h"
#include "event/event.h"
#include "game/game_manager.h"

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
        (EntityConfig
        ){.id = TURNERS_ID,
          .init = init_turners,
          .handle_event = handle_turners_event,
          .update = update_turners,
          .render = render_turners,
          .cleanup = cleanup_turners,
          .size = sizeof(Turners)}
    );
}

void init_turners(void* context, void* dependencies) {
    Turners* turners = (Turners*)context;
    Window* window = get_window(dependencies);
    Renderer* renderer = get_renderer(dependencies);

    turners->texture = load_texture(renderer, "assets/sprites/turners.png");
    turners->frame = 0;
    turners->frame_duration = 0.1f;
    turners->x = window->width / (2 * RENDERER_SCALE) - TURNERS_WIDTH / 2;
    turners->y = window->height / (2 * RENDERER_SCALE) - TURNERS_HEIGHT;

    start_timer(&turners->frame_timer, TIMER_EXPIRED);
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
        default:
            break;
    }
}

void update_turners(void* context, void* dependencies, float delta_time) {
    Turners* turners = (Turners*)context;
    EntityManager* entity_manager = get_entity_manager(dependencies);
    GameManager* game_manager =
        get_entity(entity_manager, dependencies, GAME_MANAGER_ID);

    if (!game_manager->running) {
        if (turners->frame != 0) {
            turners->frame = 0;
        }
        return;
    }

    // Animate turners
    if (is_timer_expired(&turners->frame_timer)) {
        turners->frame = (turners->frame + 1) % TURNERS_FRAME_COUNT;
        start_timer(&turners->frame_timer, turners->frame_duration);
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

uint16_t turners_get_z_index(Turners* turners) {
    return (turners->frame >= 0 && turners->frame < TURNERS_FRAME_COUNT / 2)
               ? 0
               : 1;
}
