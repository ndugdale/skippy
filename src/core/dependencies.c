#include "core/dependencies.h"

#include "core/application.h"
#include "core/entity.h"
#include "core/renderer.h"
#include "core/window.h"

EntityManager* get_entity_manager(void* dependencies) {
    return &((Application*)(dependencies))->entity_manager;
}

Renderer* get_renderer(void* dependencies) {
    return &((Application*)(dependencies))->renderer;
}

Window* get_window(void* dependencies) {
    return &((Application*)(dependencies))->window;
}
