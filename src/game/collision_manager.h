#pragma once

#include "core/entity.h"

#define COLLISION_MANAGER_ID "collision_manager"

typedef struct {
} CollisionManager;

void create_collision_manager(
    EntityManager* entity_manager, void* dependencies
);
