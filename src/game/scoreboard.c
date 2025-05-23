#include "game/scoreboard.h"

#include <stdint.h>
#include <stdio.h>

#include "core/dependencies.h"
#include "core/entity.h"
#include "core/utils.h"
#include "core/window.h"
#include "event/event.h"
#include "game/event.h"
#include "renderer/draw.h"
#include "renderer/renderer.h"

static void init_scoreboard(void* context, void* dependencies);
static void handle_scoreboard_event(
    void* context, void* dependencies, Event event
);
static void render_scoreboard(void* context, void* dependencies);
static void cleanup_scoreboard(void* context, void* dependencies);
static uint16_t get_scoreboard_width(Scoreboard* scoreboard);
static uint16_t get_scoreboard_height(Scoreboard* scoreboard);
static void reposition_scoreboard(
    Scoreboard* scoreboard, uint16_t window_width, uint16_t window_height
);

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
    reposition_scoreboard(scoreboard, window->width, window->height);
}

void handle_scoreboard_event(void* context, void* dependencies, Event event) {
    Scoreboard* scoreboard = (Scoreboard*)context;
    Window* window = get_window(dependencies);

    switch (event.type) {
        case SCORE_INCREMENT_EVENT:
            scoreboard->score++;
            reposition_scoreboard(scoreboard, window->width, window->height);
            break;
        case ROUND_START_EVENT:
            scoreboard->score = 0;
            reposition_scoreboard(scoreboard, window->width, window->height);
            break;
        case WINDOW_RESIZE_EVENT:
            reposition_scoreboard(
                scoreboard, event.window_resize.width,
                event.window_resize.height
            );
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
    UNUSED(dependencies);
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

void reposition_scoreboard(
    Scoreboard* scoreboard, uint16_t window_width, uint16_t window_height
) {
    scoreboard->x = window_width / (2.0f * RENDERER_SCALE) -
                    get_scoreboard_width(scoreboard) / 2.0f -
                    SCOREBOARD_CENTER_X_OFFSET;
    scoreboard->y = window_height / (2.0f * RENDERER_SCALE) -
                    get_scoreboard_height(scoreboard) / 2.0f -
                    SCOREBOARD_CENTER_Y_OFFSET;
}
