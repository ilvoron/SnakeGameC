#ifndef BOARD_H
#define BOARD_H
#include "snake.h"
#include "global.h"

void start_game(int width, int height);
void end_game();
void update_game_state(enum GAME_STATE* gameState);
void change_direction(enum DIRECTIONS direction, enum GAME_STATE* gameState);
/**
 * @brief init_interface – функция инициализирует интерфейс
 * return struct Board – стуктура, содержашая игровое поле
 */
struct Board get_board();

#endif