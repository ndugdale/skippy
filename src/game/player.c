#include "game/player.h"

#include "core/audio.h"
#include "core/dependencies.h"
#include "core/draw.h"
#include "core/entity.h"
#include "core/renderer.h"
#include "core/texture.h"
#include "core/utils.h"
#include "core/window.h"
#include "event/event.h"
#include "game/event.h"

static void init_player(void* context, void* dependencies);
static void handle_player_event(void* context, void* dependencies, Event event);
static void update_player(void* context, void* dependencies, float delta_time);
static void render_player(void* context, void* dependencies);
static void cleanup_player(void* context, void* dependencies);

void create_player(EntityManager* entity_manager, void* dependencies) {
    add_entity(
        entity_manager, dependencies,
        (EntityConfig){
            .id = PLAYER_ID,
            .init = init_player,
            .handle_event = handle_player_event,
            .update = update_player,
            .render = render_player,
            .cleanup = cleanup_player,
            .size = sizeof(Player),
            .z_index = PLAYER_Z_INDEX,
        }
    );
}

void init_player(void* context, void* dependencies) {
    Player* player = (Player*)context;
    Window* window = get_window(dependencies);
    Renderer* renderer = get_renderer(dependencies);

    player->texture = load_texture(renderer, "assets/sprites/player.png");
    player->jump_audio_effect = load_audio_effect("assets/audio/jump.wav");
    player->x = window->width / (2.0f * RENDERER_SCALE) - PLAYER_WIDTH / 2.0f;
    player->y = window->height / (2.0f * RENDERER_SCALE) -
                PLAYER_HEIGHT / 2.0f - PLAYER_CENTER_Y_OFFSET;
    player->y_jump = 0.0f;
    player->v_y = 0.0f;
}

void handle_player_event(void* context, void* dependencies, Event event) {
    UNUSED(dependencies);
    Player* player = (Player*)context;

    switch (event.type) {
        case PLAYER_JUMP_EVENT:
            if (player->y_jump >= 0.0f) {
                player->v_y = PLAYER_JUMP_VELOCITY;
                play_audio_effect(&player->jump_audio_effect);
            }
            break;
        case WINDOW_RESIZE_EVENT:
            player->x = event.window_resize.width / (2.0f * RENDERER_SCALE) -
                        PLAYER_WIDTH / 2.0f;
            player->y = event.window_resize.height / (2.0f * RENDERER_SCALE) -
                        PLAYER_HEIGHT / 2.0f - PLAYER_CENTER_Y_OFFSET;
            break;
        default:
            break;
    }
}

void update_player(void* context, void* dependencies, float delta_time) {
    UNUSED(dependencies);
    Player* player = (Player*)context;

    // Apply velocity and acceleration
    player->y_jump += player->v_y * delta_time;
    player->v_y += PLAYER_GRAVITY_ACCELERATION * delta_time;

    // Check if the player has landed and reset values
    if (player->y_jump > 0.0) {
        player->y_jump = 0.0;
        player->v_y = 0.0;
    }
}

void render_player(void* context, void* dependencies) {
    Player* player = (Player*)context;
    Renderer* renderer = get_renderer(dependencies);

    draw_sprite(
        renderer, &player->texture, player->x,
        (int32_t)((float)player->y + player->y_jump), PLAYER_WIDTH,
        PLAYER_HEIGHT, 0
    );
}

void cleanup_player(void* context, void* dependencies) {
    UNUSED(dependencies);
    Player* player = (Player*)context;

    unload_texture(&player->texture);
}
