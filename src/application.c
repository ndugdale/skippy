#include "application.h"
#include "player.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stddef.h>

void application_init(Application* application) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        // error
    }

    application->window = SDL_CreateWindow(
        "Skippy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600,
        SDL_WINDOW_SHOWN
    );
    if (application->window == NULL) {
        // error
    }

    application->renderer =
        SDL_CreateRenderer(application->window, -1, SDL_RENDERER_ACCELERATED);
    if (application->renderer == NULL) {
        // error
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        // error
    }

    player_init(&application->player, application->renderer);
    application->background = (SDL_Color){253, 253, 150, 255};
}

void application_handle_input(Application* application) {
    player_handle_input(&application->player);
}

void application_update(Application* application) {
    player_update(&application->player);
}

void application_render(Application* application) {
    SDL_SetRenderDrawColor(
        application->renderer, application->background.r,
        application->background.g, application->background.b,
        application->background.a
    );
    SDL_RenderClear(application->renderer);
    player_render(&application->player, application->renderer);
    SDL_RenderPresent(application->renderer);
}

void application_cleanup(Application* application) {
    SDL_DestroyRenderer(application->renderer);
    SDL_DestroyWindow(application->window);
    SDL_Quit();
}
