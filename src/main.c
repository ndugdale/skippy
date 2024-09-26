#include <SDL/SDL.h>
#include <SDL/SDL_timer.h>
#include <stdio.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

void main_loop() {}

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* screen = SDL_SetVideoMode(256, 256, 32, SDL_SWSURFACE);
    if (!screen) {
        fprintf(stderr, "Could not set video mode: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(main_loop, 0, 1);
#else
    while (1) {
        main_loop();
        SDL_Delay(16);
    }
#endif

    SDL_Quit();

    return 0;
}
