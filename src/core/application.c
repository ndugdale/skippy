#include "application.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stddef.h>

#include "core/log.h"
#include "core/renderer.h"
#include "core/timer.h"
#include "event/event.h"
#include "game/collision_manager.h"
#include "game/game_manager.h"
#include "game/player.h"
#include "game/prompt.h"
#include "game/scoreboard.h"
#include "game/turners.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

#ifdef __EMSCRIPTEN__
void application_emit_window_resize_event(Application* application);
#endif

void application_init(Application* application) {
    ASSERT(SDL_Init(SDL_INIT_VIDEO) == 0, "Failed to initialise SDL");

    window_init(&application->window, "Skippy");
    renderer_init(&application->renderer, &application->window);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

    ASSERT(
        (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == IMG_INIT_PNG,
        "Failed to initialise SDL_image"
    );

    ASSERT(TTF_Init() == 0, "Failed to initialise SDL_ttf");

    ASSERT(
        Mix_OpenAudio(
            MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS,
            AUDIO_EFFECT_CHUNK_SIZE
        ) == 0,
        "Failed to initialise SDL_mixer"
    );

    init_entities(&application->entity_manager, application);
    start_timer(&application->clock, TIMER_INFINITE);
    application->background = (Color){195, 193, 240, 255};

    create_game_manager(&application->entity_manager, application);
    create_collision_manager(&application->entity_manager, application);
    create_player(&application->entity_manager, application);
    create_turners(&application->entity_manager, application);
    create_scoreboard(&application->entity_manager, application);
    create_prompt(&application->entity_manager, application);
}

void application_dispatch_events(Application* application) {
#ifdef __EMSCRIPTEN__
    application_emit_window_resize_event(application);
#endif

    SDL_Event platform_event;
    while (SDL_PollEvent(&platform_event)) {
        Event event = {.type = UNKNOWN_EVENT};

        switch (platform_event.type) {
            case SDL_WINDOWEVENT:
                if (platform_event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    event.type = WINDOW_RESIZE_EVENT;
                    event.window_resize.width = platform_event.window.data1;
                    event.window_resize.height = platform_event.window.data2;
                }
                break;
            case SDL_QUIT:
                event.type = WINDOW_CLOSE_EVENT;
                break;
            case SDL_KEYDOWN:
                event.type = KEY_PRESS_EVENT;
                event.key_press.keycode = platform_event.key.keysym.sym;
                break;
            default:
                break;
        }

        if (event.type != UNKNOWN_EVENT) {
            application_handle_event(application, event);
        }
    }
}

void application_handle_event(Application* application, Event event) {
    switch (event.type) {
        case WINDOW_RESIZE_EVENT:
            window_resize(
                &application->window, event.window_resize.width,
                event.window_resize.height
            );
            break;
        case WINDOW_CLOSE_EVENT:
#ifdef __EMSCRIPTEN__
            emscripten_cancel_main_loop();
#else
            window_close(&application->window);
#endif
            break;
        default:
            break;
    }

    handle_entities_event(&application->entity_manager, application, event);
}

void application_update(Application* application) {
    float delta_time = get_elapsed_time(&application->clock);
    start_timer(&application->clock, TIMER_INFINITE);
    update_entities(&application->entity_manager, application, delta_time);
}

void application_render(Application* application) {
    renderer_clear(
        &application->renderer, application->background.r,
        application->background.g, application->background.b,
        application->background.a
    );
    render_entities(&application->entity_manager, application);
    renderer_present(&application->renderer);
}

void application_cleanup(Application* application) {
    cleanup_entities(&application->entity_manager, application);
    renderer_cleanup(&application->renderer);
    window_cleanup(&application->window);
    SDL_Quit();
}

#ifdef __EMSCRIPTEN__
void application_emit_window_resize_event(Application* application) {
    int32_t window_width;
    int32_t window_height;
    SDL_GetWindowSize(
        application->window.platform_window, &window_width, &window_height
    );

    double w;
    double h;
    emscripten_get_element_css_size("#canvas", &w, &h);
    int32_t canvas_width = (int32_t)w;
    int32_t canvas_height = (int32_t)h;

    if (window_width != (int32_t)canvas_width ||
        window_height != (int32_t)canvas_height) {
        Event event =
            {.type = WINDOW_RESIZE_EVENT,
             .window_resize = {
                 .width = canvas_width,
                 .height = canvas_height,
             }};
        application_handle_event(application, event);
    }
}
#endif
