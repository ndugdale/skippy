#pragma once

#include "core/entity.h"
#include "core/timer.h"
#include "core/window.h"
#include "event/event.h"
#include "renderer/renderer.h"

typedef struct {
    Window window;
    Renderer renderer;
    EntityManager entity_manager;
    Timer clock;
    Color background;
} Application;

void application_init(Application* application);
void application_dispatch_events(Application* application);
void application_handle_event(Application* application, Event event);
void application_update(Application* application);
void application_render(Application* application);
void application_cleanup(Application* application);
