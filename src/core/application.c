#include "application.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stddef.h>

#include "core/clock.h"
#include "core/log.h"
#include "player.h"
#include "turners.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

#ifdef __EMSCRIPTEN__
void _emit_window_resize_event(SDL_Window* window, SDL_Event* event);
#endif

void application_init(Application* application) {
    ASSERT(SDL_Init(SDL_INIT_VIDEO) == 0, "Failed to initialise SDL");

    application->window = window_create("Skippy");
    application->renderer = renderer_create(&application->window);
    application->texture_manager =
        texture_manager_create(&application->renderer);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

    ASSERT(
        (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == IMG_INIT_PNG,
        "Failed to initialse SDL_image"
    );

    application->clock = clock_create();
    application->player = player_create(&application->texture_manager);
    application->turners = turners_create(&application->texture_manager);
    application->background = (SDL_Color){195, 193, 240, 255};
    application->round_in_progress = false;
}

void application_handle_input(Application* application) {
#ifdef __EMSCRIPTEN__
    SDL_Event window_resize_event;
    // TODO: create abstraction
    _emit_window_resize_event(
        application->window.platform_window, &window_resize_event
    );
#endif

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        player_handle_input(&application->player, event);

        switch (event.type) {
            case SDL_QUIT:
#ifdef __EMSCRIPTEN__
                emscripten_cancel_main_loop();
#else
                // TODO
#endif
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_SPACE:
                        application->round_in_progress = true;
                        application->player.frozen = false;
                        application->turners.frozen = false;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    // TODO: create abstraction
                    SDL_SetWindowSize(
                        application->window.platform_window, event.window.data1,
                        event.window.data2
                    );
                }
                break;
            default:
                break;
        }
    }
}

void application_update(Application* application) {
    float delta_time = clock_tick(&application->clock);
    player_update(&application->player, delta_time);
    turners_update(&application->turners, delta_time);
}

void application_render(Application* application) {
    renderer_clear(
        &application->renderer, application->background.r,
        application->background.g, application->background.b,
        application->background.a
    );
    // TODO: create abstraction
    SDL_RenderClear(application->renderer.platform_renderer);

    if (turners_get_z_index(&application->turners) > 0) {
        player_render(&application->player, &application->renderer);
        turners_render(&application->turners, &application->renderer);
    } else {
        turners_render(&application->turners, &application->renderer);
        player_render(&application->player, &application->renderer);
    }

    // TODO: create abstraction
    SDL_RenderPresent(application->renderer.platform_renderer);
}

void application_cleanup(Application* application) {
    player_cleanup(&application->player);
    turners_cleanup(&application->turners);
    renderer_destroy(&application->renderer);
    window_destroy(&application->window);
    SDL_Quit();
}

#ifdef __EMSCRIPTEN__
void _emit_window_resize_event(SDL_Window* window, SDL_Event* event) {
    int32_t window_width;
    int32_t window_height;
    SDL_GetWindowSize(window, &window_width, &window_height);

    double w;
    double h;
    emscripten_get_element_css_size("#canvas", &w, &h);
    int32_t canvas_width = (int32_t)w;
    int32_t canvas_height = (int32_t)h;

    if (window_width != (int32_t)canvas_width ||
        window_height != (int32_t)canvas_height) {
        event->type = SDL_WINDOWEVENT;
        event->window.event = SDL_WINDOWEVENT_RESIZED;
        event->window.data1 = canvas_width;
        event->window.data2 = canvas_height;

        SDL_PushEvent(event);
    }
}
#endif
