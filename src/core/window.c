#include "window.h"

#include <SDL2/SDL.h>

#include "core/log.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

Window window_create(const char* title) {
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

    Window window = {
        .platform_window = platform_window,
    };

    return window;
}

void window_destroy(Window* window) {
    SDL_DestroyWindow(window->platform_window);
}
