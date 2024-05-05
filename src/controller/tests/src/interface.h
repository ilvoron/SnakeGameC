#ifndef INTERFACE_H
#define INTERFACE_H
#include "global.h"

/**
 * @brief init_interface – функция инициализирует интерфейс
 * @param struct Settings* settings – указатель на структуру с настройками игры
 */
void init_interface(struct Settings* settings);

/**
 * @brief clear_interface – функция выгружает интерфейс
 */
void close_interface();

/**
 * @brief show_menu – функция выводит меню игры на экран
 */
void show_menu(struct Settings* settings);

/**
 * @brief show_frame – функция отрисовки игрового поля на экране
 */
void show_frame();

/**
 * @brief show_end_game – функция выводит информацию о конце игры
 */
void show_end_game();

/**
 * @brief get_event - возвращает игровое событие, если оно произошло
 * @return enum GAME_EVENT - код игрового события
 */
extern enum GAME_EVENT get_event();

#endif