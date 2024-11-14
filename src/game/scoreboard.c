#include "game/scoreboard.h"

#include <stdint.h>
#include <stdio.h>

#include "core/dependencies.h"
#include "core/draw.h"
#include "core/entity.h"
#include "core/renderer.h"
#include "core/window.h"
#include "event/event.h"

static void init_scoreboard(void* context, void* dependencies);
static void handle_scoreboard_event(
    void* context, void* dependencies, Event event
);
static void render_scoreboard(void* context, void* dependencies);
static void cleanup_scoreboard(void* context, void* dependencies);
static uint16_t get_scoreboard_width(Scoreboard* scoreboard);
static uint16_t get_scoreboard_height(Scoreboard* scoreboard);

void create_scoreboard(EntityManager* entity_manager, void* dependencies) {
    add_entity(
        entity_manager, dependencies,
        (EntityConfig){
            .id = SCOREBOARD_ID,
            .init = init_scoreboard,
            .handle_event = handle_scoreboard_event,
            .update = NULL,
            .render = render_scoreboard,
            .cleanup = cleanup_scoreboard,
            .size = sizeof(Scoreboard),
            .z_index = SCOREBOARD_Z_INDEX,
        }
    );
}

void init_scoreboard(void* context, void* dependencies) {
    Scoreboard* scoreboard = (Scoreboard*)context;
    Window* window = get_window(dependencies);

    scoreboard->score = 0;
    scoreboard->font =
        load_font("assets/fonts/monogram.ttf", SCOREBOARD_FONT_SIZE);
    scoreboard->x = window->width / (2 * RENDERER_SCALE) -
                    get_scoreboard_width(scoreboard) / 2;
    scoreboard->y = window->height / (2 * RENDERER_SCALE) -
                    get_scoreboard_height(scoreboard);
}

void handle_scoreboard_event(void* context, void* dependencies, Event event) {
    Scoreboard* scoreboard = (Scoreboard*)context;

    switch (event.type) {
        case WINDOW_RESIZE_EVENT:
            scoreboard->x = event.window_resize.width / (2 * RENDERER_SCALE) -
                            get_scoreboard_width(scoreboard) / 2;
            scoreboard->y = event.window_resize.height / (2 * RENDERER_SCALE) -
                            get_scoreboard_height(scoreboard);
            break;
        default:
            break;
    }
}

void render_scoreboard(void* context, void* dependencies) {
    Scoreboard* scoreboard = (Scoreboard*)context;
    Renderer* renderer = get_renderer(dependencies);

    char buffer[SCOREBOARD_BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), "%u", scoreboard->score);
    draw_text(
        renderer, &scoreboard->font, buffer, SCOREBOARD_COLOR, scoreboard->x,
        scoreboard->y
    );
}

void cleanup_scoreboard(void* context, void* dependencies) {
    Scoreboard* scoreboard = (Scoreboard*)context;

    unload_font(&scoreboard->font);
}

uint16_t get_scoreboard_width(Scoreboard* scoreboard) {
    char buffer[SCOREBOARD_BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), "%u", scoreboard->score);

    return get_text_width(&scoreboard->font, buffer);
}

uint16_t get_scoreboard_height(Scoreboard* scoreboard) {
    char buffer[SCOREBOARD_BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), "%u", scoreboard->score);

    return get_text_height(&scoreboard->font, buffer);
}
