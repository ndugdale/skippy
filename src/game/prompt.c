#include "game/prompt.h"

#include <stdbool.h>
#include <stdint.h>

#include "core/dependencies.h"
#include "core/draw.h"
#include "core/entity.h"
#include "core/renderer.h"
#include "core/utils.h"
#include "core/window.h"
#include "event/event.h"
#include "game/event.h"

static void init_prompt(void* context, void* dependencies);
static void handle_prompt_event(void* context, void* dependencies, Event event);
static void render_prompt(void* context, void* dependencies);
static void cleanup_prompt(void* context, void* dependencies);
static void reposition_prompt(
    Prompt* prompt, uint16_t window_width, uint16_t window_height
);

void create_prompt(EntityManager* entity_manager, void* dependencies) {
    add_entity(
        entity_manager, dependencies,
        (EntityConfig){
            .id = PROMPT_ID,
            .init = init_prompt,
            .handle_event = handle_prompt_event,
            .update = NULL,
            .render = render_prompt,
            .cleanup = cleanup_prompt,
            .size = sizeof(Prompt),
            .z_index = PROMPT_Z_INDEX,
        }
    );
}

void init_prompt(void* context, void* dependencies) {
    Prompt* prompt = (Prompt*)context;
    Window* window = get_window(dependencies);

    prompt->font = load_font("assets/fonts/monogram.ttf", PROMPT_FONT_SIZE);
    prompt->hidden = false;
    reposition_prompt(prompt, window->width, window->height);
}

void handle_prompt_event(void* context, void* dependencies, Event event) {
    UNUSED(dependencies);
    Prompt* prompt = (Prompt*)context;

    switch (event.type) {
        case ROUND_START_EVENT:
            prompt->hidden = true;
            break;
        case ROUND_END_EVENT:
            prompt->hidden = false;
            break;
        case WINDOW_RESIZE_EVENT:
            reposition_prompt(
                prompt, event.window_resize.width, event.window_resize.height
            );
            break;
        default:
            break;
    }
}

void render_prompt(void* context, void* dependencies) {
    Prompt* prompt = (Prompt*)context;
    Renderer* renderer = get_renderer(dependencies);

    if (prompt->hidden) return;

    draw_text(
        renderer, &prompt->font, PROMPT_TEXT, PROMPT_COLOR, prompt->x, prompt->y
    );
}

void cleanup_prompt(void* context, void* dependencies) {
    UNUSED(dependencies);
    Prompt* prompt = (Prompt*)context;

    unload_font(&prompt->font);
}

void reposition_prompt(
    Prompt* prompt, uint16_t window_width, uint16_t window_height
) {
    prompt->x = window_width / (2.0f * RENDERER_SCALE) -
                get_text_width(&prompt->font, PROMPT_TEXT) / 2.0f -
                PROMPT_CENTER_X_OFFSET;
    prompt->y = window_height / (2.0f * RENDERER_SCALE) -
                get_text_height(&prompt->font, PROMPT_TEXT) / 2.0f -
                PROMPT_CENTER_Y_OFFSET;
}
