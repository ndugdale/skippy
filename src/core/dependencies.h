#pragma once

#include "core/entity.h"
#include "core/window.h"
#include "renderer/renderer.h"

EntityManager* get_entity_manager(void* dependencies);
Renderer* get_renderer(void* dependencies);
Window* get_window(void* dependencies);
