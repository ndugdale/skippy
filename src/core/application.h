#pragma once

#include "core/clock.h"
#include "core/entity.h"
#include "core/renderer.h"
#include "core/window.h"
#include "event/event.h"

typedef struct {
    Window window;
    Renderer renderer;
    EntityManager entity_manager;
    Clock clock;
    Color background;
} Application;

void application_init(Application* application);
void application_dispatch_events(Application* application);
void application_handle_event(Application* application, Event event);
void application_update(Application* application);
void application_render(Application* application);
void application_cleanup(Application* application);
