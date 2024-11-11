#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "event/event.h"

#define MAX_ENTITIES 256

typedef struct {
    const char* id;
    void (*init)(void* context, void* dependencies);
    void (*handle_event)(void* context, void* dependencies, Event event);
    void (*update)(void* context, void* dependencies, float delta_time);
    void (*render)(void* context, void* dependencies);
    void (*cleanup)(void* context, void* dependencies);
    void* data;
    bool active;
} Entity;

typedef struct {
    const char* id;
    void (*init)(void* context, void* dependencies);
    void (*handle_event)(void* context, void* dependencies, Event event);
    void (*update)(void* context, void* dependencies, float delta_time);
    void (*render)(void* context, void* dependencies);
    void (*cleanup)(void* context, void* dependencies);
    size_t size;
} EntityConfig;

typedef struct {
    Entity entities[MAX_ENTITIES];
    uint16_t entity_count;
} EntityManager;

void init_entities(EntityManager* entity_manager, void* dependencies);
void handle_entities_event(
    EntityManager* entity_manager, void* dependencies, Event event
);
void update_entities(
    EntityManager* entity_manager, void* dependencies, float delta_time
);
void render_entities(EntityManager* entity_manager, void* dependencies);
void cleanup_entities(EntityManager* entity_manager, void* dependencies);

void add_entity(
    EntityManager* entity_manager, void* dependencies, EntityConfig config
);
void* get_entity(
    EntityManager* entity_manager, void* dependencies, const char* id
);
void remove_entity(
    EntityManager* entity_manager, void* dependencies, const char* id
);
