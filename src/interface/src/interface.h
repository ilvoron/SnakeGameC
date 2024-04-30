#ifndef INTERFACE_H
#define INTERFACE_H
#include "global.h"
#include "interface_global.h"

extern const struct InputTrigger INPUT_TRIGGERS_DEFAULT[I__COUNT];
extern const struct Speed SPEED_DEFAULT;
extern const struct Skin SKIN_DEFAULT;

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
void show_menu();
/**
 * @brief show_frame – функция выводит игровое поле на экран
 */
void show_frame();
/**
 * @brief show_end_game – функция выводит информацию о конце игры
 */
void show_end_game(enum END_GAME_CODE endGameCode);
/**
 * @brief show_error - выводит сообщение-ошибку на экран
 * @param enum ERROR_CODE - код ошибки
 */
void show_error(enum ERROR_CODE);

#endif