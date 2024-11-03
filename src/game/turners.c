#include "game/turners.h"

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

#include "event/event.h"
#include "game/game_manager.h"

void turners_init(Turners* turners, TextureManager* texture_manager) {
    turners->texture = texture_manager_get_texture(texture_manager, "turners");
    turners->frame = 0;
    turners->frame_count = 8;
    turners->frame_duration = 0.1f;
    turners->last_frame_ticks = 0;
    turners->x_0 = 32;
    turners->y_0 = 32;
    turners->width = 96;
    turners->height = 32;
}

void turners_handle_event(
    Turners* turners, GameManager* game_manager, Event event
) {
    switch (event.type) {
        case KEY_PRESS_EVENT:
            if (event.key_press.keycode == KEYCODE_SPACE &&
                !game_manager->running) {
                game_manager->running = true;
            }
            break;
        default:
            break;
    }
}

void turners_update(
    Turners* turners, GameManager* game_manager, float delta_time
) {
    if (!game_manager->running) {
        return;
    }

    // Animate turners
    // TODO: remove SDL api
    uint64_t elapsed = SDL_GetPerformanceCounter();
    float frame_delta_time = (float)(elapsed - turners->last_frame_ticks) /
                             SDL_GetPerformanceFrequency();

    if (frame_delta_time >= turners->frame_duration) {
        turners->frame = (turners->frame + 1) % turners->frame_count;
        turners->last_frame_ticks = elapsed;
    }
}

void turners_render(Turners* turners, Renderer* renderer) {
    renderer_blit_sprite(
        renderer, &turners->texture, turners->x_0, turners->y_0, turners->width,
        turners->height, turners->frame
    );
}

void turners_cleanup(Turners* turners) {}

uint16_t turners_get_z_index(Turners* turners) {
    return (turners->frame >= 0 && turners->frame < turners->frame_count / 2)
               ? 0
               : 1;
}
