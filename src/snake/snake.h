#ifndef SNAKE_H
#define SNAKE_H
#include "global.h"

void create_snake(struct Snake* snake, int boardWidth, int boardHeight);
void delete_snake(struct Snake* snake);
void move_snake(struct Snake* snake);
void grow_snake(struct Snake* snake);
bool check_snake(struct Snake* snake, int index);

#endif