#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>
#include "global.h"

// real
struct Board get_board();

// only for tests
void GenerateBoard();
void SetApple(unsigned int x, unsigned int y);
void SetSnake(unsigned int x, unsigned int y, bool updateLast);
void FreeBoard();

#endif