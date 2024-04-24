#ifndef CONTROLLER_H
#define CONTTROLLER_H
#include "interface.h"
#include "board.h"
#include "snake.h"
#include "global.h"
#include <stdbool.h>
#include <windows.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <winsock.h>

/**
 * @brief Updater Функция – супервайзер для циклического вызова остальных функций 
 * @param Settings – структура для хранения всех данных игрока
 */
void Updater(struct Settings);
/**
 * @brief End_Of_Program Функция завершение 
 * @param Settings – структура для хранения всех данных игрока
 */
void End_Of_Program(struct Settings);
/**
 * @brief keyHandler Функция для обработки клавиш 
 * @param enum DIRECTIONS направление движение змеи
 */
void keyHandler (enum DIRECTIONS direction);
/**
 * @brief get_time Функция для рассчета времени между кадрами
 */
 long long get_time();
#endif