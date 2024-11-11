#pragma once

#include "core/entity.h"
#include "core/renderer.h"
#include "core/window.h"

EntityManager* get_entity_manager(void* dependencies);
Renderer* get_renderer(void* dependencies);
Window* get_window(void* dependencies);
