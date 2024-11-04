#include "application.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stddef.h>

#include "core/clock.h"
#include "core/log.h"
#include "event/event.h"
#include "game/collision_system.h"
#include "game/player.h"
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
        "Failed to initialse SDL_image"
    );

    texture_manager_init(&application->texture_manager, &application->renderer);
    game_manager_init(&application->game_manager);
    clock_init(&application->clock);
    player_init(
        &application->player, &application->window,
        &application->texture_manager
    );
    turners_init(
        &application->turners, &application->window,
        &application->texture_manager
    );
    collision_system_init(
        &application->collision_system, &application->player,
        &application->turners
    );
    application->background = (Color){195, 193, 240, 255};
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

    player_handle_event(
        &application->player, &application->game_manager, event
    );
    turners_handle_event(
        &application->turners, &application->game_manager, event
    );
}

void application_update(Application* application) {
    float delta_time = clock_tick(&application->clock);
    player_update(&application->player, &application->game_manager, delta_time);
    turners_update(
        &application->turners, &application->game_manager, delta_time
    );
    collision_system_update(
        &application->collision_system, &application->game_manager, delta_time
    );
}

void application_render(Application* application) {
    renderer_clear(
        &application->renderer, application->background.r,
        application->background.g, application->background.b,
        application->background.a
    );

    if (turners_get_z_index(&application->turners) > 0) {
        player_render(&application->player, &application->renderer);
        turners_render(&application->turners, &application->renderer);
    } else {
        turners_render(&application->turners, &application->renderer);
        player_render(&application->player, &application->renderer);
    }

    renderer_present(&application->renderer);
}

void application_cleanup(Application* application) {
    player_cleanup(&application->player);
    turners_cleanup(&application->turners);
    renderer_destroy(&application->renderer);
    window_destroy(&application->window);
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
