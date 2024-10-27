#include "application.h"
#include "clock.h"
#include "player.h"
#include "turners.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stddef.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

#ifdef __EMSCRIPTEN__
void _emit_window_resize_event(SDL_Window* window, SDL_Event* event);
#endif

void application_init(Application* application) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        // TODO: error
    }

#ifdef __EMSCRIPTEN__
    double w;
    double h;
    emscripten_get_element_css_size("#canvas", &w, &h);
    int32_t width = (int32_t)w;
    int32_t height = (int32_t)h;
#else
    SDL_DisplayMode display_mode;
    if (SDL_GetDesktopDisplayMode(0, &display_mode) != 0) {
        // TODO: error
    }
    int32_t width = display_mode.w;
    int32_t height = display_mode.h;
#endif

    application->window = SDL_CreateWindow(
        "Skippy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,
        height, SDL_WINDOW_SHOWN
    );
    if (application->window == NULL) {
        // TODO: error
    }

    application->renderer =
        SDL_CreateRenderer(application->window, -1, SDL_RENDERER_ACCELERATED);
    if (application->renderer == NULL) {
        // TODO: error
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
    SDL_RenderSetScale(application->renderer, 8.0, 8.0);

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        // TODO: error
    }

    application->clock = clock_create();
    application->player = player_create(application->renderer);
    application->turners = turners_create(application->renderer);
    application->background = (SDL_Color){253, 253, 150, 255};
}

void application_handle_input(Application* application) {
#ifdef __EMSCRIPTEN__
    SDL_Event window_resize_event;
    _emit_window_resize_event(application->window, &window_resize_event);
#endif

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
#ifdef __EMSCRIPTEN__
            emscripten_cancel_main_loop();
#else
            // TODO
#endif
            break;
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                SDL_SetWindowSize(
                    application->window, event.window.data1, event.window.data2
                );
            }
            break;
        default:
            break;
        }
        player_handle_input(&application->player, event);
    }
}

void application_update(Application* application) {
    float delta_time = clock_tick(&application->clock);
    player_update(&application->player, delta_time);
    turners_update(&application->turners, delta_time);
}

void application_render(Application* application) {
    SDL_SetRenderDrawColor(
        application->renderer, application->background.r,
        application->background.g, application->background.b,
        application->background.a
    );
    SDL_RenderClear(application->renderer);
    player_render(&application->player, application->renderer);
    turners_render(&application->turners, application->renderer);
    SDL_RenderPresent(application->renderer);
}

void application_cleanup(Application* application) {
    player_cleanup(&application->player);
    turners_cleanup(&application->turners);
    SDL_DestroyRenderer(application->renderer);
    SDL_DestroyWindow(application->window);
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
