#include "game/game_manager.h"

void game_manager_init(GameManager* game_manager) {
    game_manager->running = false;
}

void game_manager_start_game(GameManager* game_manager) {
    game_manager->running = true;
}

void game_manager_end_game(GameManager* game_manager) {
    game_manager->running = true;
}
