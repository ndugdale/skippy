#pragma once

#include <stdbool.h>

#include "core/entity.h"

#define COLLISION_MANAGER_ID "collision_manager"

typedef struct {
    bool collision;
} CollisionManager;

void create_collision_manager(
    EntityManager* entity_manager, void* dependencies
);
