#pragma once

#include <stdbool.h>

typedef struct {
    bool running;
} GameManager;

void game_manager_init(GameManager* game_manager);
void game_manager_start_game(GameManager* game_manager);
void game_manager_end_game(GameManager* game_manager);
