#include "core/entity.h"

#include <memory.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "core/log.h"

void init_entities(EntityManager* entity_manager, void* dependencies) {
    memset(entity_manager, 0, sizeof(EntityManager));
}

void handle_entities_event(
    EntityManager* entity_manager, void* dependencies, Event event
) {
    for (size_t i = 0; i < entity_manager->entity_count; i++) {
        Entity* entity = &entity_manager->entities[i];

        if (entity->active && entity->handle_event != NULL) {
            entity->handle_event(entity->data, dependencies, event);
        }
    }
}

void update_entities(
    EntityManager* entity_manager, void* dependencies, float delta_time
) {
    for (size_t i = 0; i < entity_manager->entity_count; i++) {
        Entity* entity = &entity_manager->entities[i];

        if (entity->active && entity->update != NULL) {
            entity->update(entity->data, dependencies, delta_time);
        }
    }
}

void render_entities(EntityManager* entity_manager, void* dependencies) {
    for (size_t i = 0; i < entity_manager->entity_count; i++) {
        Entity* entity = &entity_manager->entities[i];

        if (entity->active && entity->render != NULL) {
            entity->render(entity->data, dependencies);
        }
    }
}

void cleanup_entities(EntityManager* entity_manager, void* dependencies) {
    for (size_t i = 0; i < entity_manager->entity_count; i++) {
        Entity* entity = &entity_manager->entities[i];

        if (entity->active && entity->cleanup != NULL) {
            entity->cleanup(entity->data, dependencies);
        }
    }
}

void add_entity(
    EntityManager* entity_manager, void* dependencies, EntityConfig config
) {
    Entity* entity = &entity_manager->entities[entity_manager->entity_count++];

    *entity = (Entity){
        .id = config.id,
        .init = config.init,
        .handle_event = config.handle_event,
        .update = config.update,
        .render = config.render,
        .cleanup = config.cleanup,
        .data = malloc(config.size),
        .active = true,
    };

    if (entity->init != NULL) {
        entity->init(entity->data, dependencies);
    }
}

void* get_entity(
    EntityManager* entity_manager, void* dependencies, const char* id
) {
    for (size_t i = 0; i < entity_manager->entity_count; i++) {
        Entity* entity = &entity_manager->entities[i];

        if (entity->active && strcmp(entity->id, id) == 0) {
            return entity->data;
        }
    }

    ASSERT(false, "Failed to get entity with id %s", id);
}

void remove_entity(
    EntityManager* entity_manager, void* dependencies, const char* id
) {
    for (size_t i = 0; i < entity_manager->entity_count; i++) {
        Entity* entity = &entity_manager->entities[i];

        if (entity->active && strcmp(entity->id, id) == 0) {
            if (entity->cleanup != NULL) {
                entity->cleanup(entity->data, dependencies);
            }

            entity->active = false;
            free(entity->data);
        }
    }
}
