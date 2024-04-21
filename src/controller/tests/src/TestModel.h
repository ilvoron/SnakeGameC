#ifndef TESTMODEL_H
#define TESTMODEL_H
#include "global.h"
#include "interface.h"
#include "board.h"

/**
 * @brief Test_Controller запускает тест функций модуля
 */
int Test_Controller();

/**
 * @brief get_result функция вывода результатов вызова внешних функций в файла
 */
int get_result(char Name[]);
/*
void show_end_game(enum END_GAME_CODE);
void end_game();
void show_menu(struct Settings* settings);
void start_game(int width, int height);
void update_game_state(enum GAME_STATE* gameState);
void render_frame();
void change_direction(enum DIRECTIONS direction, enum GAME_STATE* gameState);
void close_interface();
void init_interface(struct Settings* settings);*/
#endif