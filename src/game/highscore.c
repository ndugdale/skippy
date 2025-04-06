#include "game/highscore.h"

#include <stdint.h>
#include <stdio.h>

#include "core/dependencies.h"
#include "core/draw.h"
#include "core/entity.h"
#include "core/font.h"
#include "core/renderer.h"
#include "core/window.h"
#include "event/event.h"
#include "game/event.h"

static void init_highscore(void* context, void* dependencies);
static void handle_highscore_event(
    void* context, void* dependencies, Event event
);
static void render_highscore(void* context, void* dependencies);
static void cleanup_highscore(void* context, void* dependencies);
static void reposition_highscore(
    Highscore* highscore, uint16_t window_width, uint16_t window_height
);

void create_highscore(EntityManager* entity_manager, void* dependencies) {
    add_entity(
        entity_manager, dependencies,
        (EntityConfig){
            .id = HIGHSCORE_ID,
            .init = init_highscore,
            .handle_event = handle_highscore_event,
            .update = NULL,
            .render = render_highscore,
            .cleanup = cleanup_highscore,
            .size = sizeof(Highscore),
            .z_index = HIGHSCORE_Z_INDEX,
        }
    );
}

void init_highscore(void* context, void* dependencies) {
    Highscore* highscore = (Highscore*)context;
    Window* window = get_window(dependencies);

    highscore->font =
        load_font("assets/fonts/monogram.ttf", HIGHSCORE_FONT_SIZE);
    highscore->highscore = 0;
    highscore->score = 0;
    highscore->hidden = true;
    snprintf(
        highscore->text, sizeof(highscore->text), "%s %u", HIGHSCORE_TEXT,
        highscore->highscore
    );
    reposition_highscore(highscore, window->width, window->height);
}

void handle_highscore_event(void* context, void* dependencies, Event event) {
    Highscore* highscore = (Highscore*)context;
    Window* window = get_window(dependencies);

    switch (event.type) {
        case ROUND_START_EVENT:
            highscore->hidden = true;
            break;
        case SCORE_INCREMENT_EVENT:
            highscore->score++;
            break;
        case ROUND_END_EVENT:
            if (highscore->score > highscore->highscore) {
                highscore->highscore = highscore->score;
                snprintf(
                    highscore->text, sizeof(highscore->text), "%s %u",
                    HIGHSCORE_TEXT, highscore->highscore
                );
                reposition_highscore(highscore, window->width, window->height);
            }

            highscore->score = 0;
            highscore->hidden = false;
            break;
        case WINDOW_RESIZE_EVENT:
            reposition_highscore(
                highscore, event.window_resize.width, event.window_resize.height
            );
            break;
        default:
            break;
    }
}

void render_highscore(void* context, void* dependencies) {
    Highscore* highscore = (Highscore*)context;
    Renderer* renderer = get_renderer(dependencies);

    if (highscore->hidden) return;

    draw_text(
        renderer, &highscore->font, highscore->text, HIGHSCORE_COLOR,
        highscore->x, highscore->y
    );
}

void cleanup_highscore(void* context, void* dependencies) {
    Highscore* highscore = (Highscore*)context;

    unload_font(&highscore->font);
}

void reposition_highscore(
    Highscore* highscore, uint16_t window_width, uint16_t window_height
) {
    highscore->x = window_width / (2 * RENDERER_SCALE) -
                   get_text_width(&highscore->font, highscore->text) / 2 -
                   HIGHSCORE_CENTER_X_OFFSET;
    highscore->y = window_height / (2 * RENDERER_SCALE) -
                   get_text_height(&highscore->font, highscore->text) / 2 -
                   HIGHSCORE_CENTER_Y_OFFSET;
}
