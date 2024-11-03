#include "window.h"

#include <SDL2/SDL.h>
#include <stdint.h>

#include "core/log.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

void window_init(Window* window, const char* title) {
#ifdef __EMSCRIPTEN__
    double w;
    double h;
    emscripten_get_element_css_size("#canvas", &w, &h);
    int32_t width = (int32_t)w;
    int32_t height = (int32_t)h;
#else
    SDL_DisplayMode display_mode;
    ASSERT(
        SDL_GetDesktopDisplayMode(0, &display_mode) == 0,
        "Failed to get desktop display mode"
    );

    int32_t width = display_mode.w;
    int32_t height = display_mode.h;
#endif

    void* platform_window = SDL_CreateWindow(
        title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
        SDL_WINDOW_SHOWN
    );
    ASSERT(platform_window != NULL, "Failed to create SDL_Window");

    window->platform_window = platform_window;
}

void window_resize(Window* window, uint16_t width, uint16_t height) {
    SDL_SetWindowSize(window->platform_window, width, height);
}

void window_close(Window* window) {
    // TODO: change to stop loop
    exit(0);
}

void window_destroy(Window* window) {
    SDL_DestroyWindow(window->platform_window);
}
