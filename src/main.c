#include <SDL2/SDL.h>

#include "core/application.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

Application application;

void main_loop(void) {
    application_dispatch_events(&application);
    application_update(&application);
    application_render(&application);
}

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    application_init(&application);

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(main_loop, 0, 1);
#else
    while (1) {
        main_loop();
        // TODO: remove SDL api
        SDL_Delay(16);
    }
#endif

    application_cleanup(&application);

    return 0;
}
