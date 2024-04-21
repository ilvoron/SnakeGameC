#ifndef BOARD_H
#define BOARD_H
#include "snake.h"
#include "global.h"

/**
 * @brief start_game функция создает начальный игровой экран
 */
void start_game(int width, int height);

/**
 * @brief end_game функция освобождает память массива с игровым экраном
 */
void end_game();

/**
 * @brief update_game_state функция отвечающая за изменение состояния игры (движение змеи, проверку колизии, создание яблок)
 * @param enum GAME_STATE* переменная, указывающая на текущее состояние игры
 */
void update_game_state(enum GAME_STATE* gameState);

/**
 * @brief change_direction функция отвечающая за изменение направления движения змеи
 * @param enum DIRECTIONS переменная, указывающая на текущее направлене движения
 * @param enum GAME_STATE* переменная, указывающая на текущее состояние игры
 */
void change_direction(enum DIRECTIONS direction, enum GAME_STATE* gameState);

/**
 * @brief init_interface – функция инициализирует интерфейс
 * return struct Board – стуктура, содержашая игровое поле
 */
struct Board get_board();

#endif