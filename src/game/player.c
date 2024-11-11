#include "game/player.h"

#include "core/dependencies.h"
#include "core/draw.h"
#include "core/entity.h"
#include "core/renderer.h"
#include "core/texture.h"
#include "core/window.h"
#include "event/event.h"
#include "game/game_manager.h"

static void init_player(void* context, void* dependencies);
static void handle_player_event(void* context, void* dependencies, Event event);
static void update_player(void* context, void* dependencies, float delta_time);
static void render_player(void* context, void* dependencies);
static void cleanup_player(void* context, void* dependencies);

void create_player(EntityManager* entity_manager, void* dependencies) {
    add_entity(
        entity_manager, dependencies,
        (EntityConfig
        ){.id = PLAYER_ID,
          .init = init_player,
          .handle_event = handle_player_event,
          .update = update_player,
          .render = render_player,
          .cleanup = cleanup_player,
          .size = sizeof(Player)}
    );
}

void init_player(void* context, void* dependencies) {
    Player* player = (Player*)context;
    Window* window = get_window(dependencies);
    Renderer* renderer = get_renderer(dependencies);

    player->texture = load_texture(renderer, "assets/sprites/player.png");
    player->width = 32;
    player->height = 32;
    player->x_0 = window->width / (2 * RENDERER_SCALE) - player->width / 2;
    player->y_0 = window->height / (2 * RENDERER_SCALE) - player->height;
    player->y = 0.0f;
    player->v_y = 0.0f;
    player->v_jump = -40.0f;
    player->a_gravity = 240.0f;
}

void handle_player_event(void* context, void* dependencies, Event event) {
    Player* player = (Player*)context;
    EntityManager* entity_manager = get_entity_manager(dependencies);
    GameManager* game_manager =
        get_entity(entity_manager, dependencies, "game_manager");

    switch (event.type) {
        case KEY_PRESS_EVENT:
            if (event.key_press.keycode == KEYCODE_SPACE &&
                game_manager->running &&
                !game_manager->in_round_start_grace_period) {
                if (player->y >= 0.0f) {
                    player->v_y = player->v_jump;
                }
            }
            break;
        case WINDOW_RESIZE_EVENT:
            player->x_0 = event.window_resize.width / (2 * RENDERER_SCALE) -
                          player->width / 2;
            player->y_0 = event.window_resize.height / (2 * RENDERER_SCALE) -
                          player->height;
            break;
        default:
            break;
    }
}

void update_player(void* context, void* dependencies, float delta_time) {
    Player* player = (Player*)context;

    // Apply velocity and acceleration
    player->y += player->v_y * delta_time;
    player->v_y += player->a_gravity * delta_time;

    // Check if the player has landed and reset values
    if (player->y > 0.0) {
        player->y = 0.0;
        player->v_y = 0.0;
    }
}

void render_player(void* context, void* dependencies) {
    Player* player = (Player*)context;
    Renderer* renderer = get_renderer(dependencies);

    draw_sprite(
        renderer, &player->texture, player->x_0,
        (int32_t)((float)player->y_0 + player->y), player->width,
        player->height, 0
    );
}

void cleanup_player(void* context, void* dependencies) {
    Player* player = (Player*)context;

    unload_texture(&player->texture);
}
