#pragma once

#include "core/clock.h"
#include "core/renderer.h"
#include "core/window.h"
#include "event/event.h"
#include "game/collision_system.h"
#include "game/game_manager.h"
#include "game/player.h"
#include "game/turners.h"

typedef struct {
    Window window;
    Renderer renderer;
    GameManager game_manager;
    Clock clock;
    Player player;
    Turners turners;
    CollisionSystem collision_system;
    Color background;
} Application;

void application_init(Application* application);
void application_dispatch_events(Application* application);
void application_handle_event(Application* application, Event event);
void application_update(Application* application);
void application_render(Application* application);
void application_cleanup(Application* application);
