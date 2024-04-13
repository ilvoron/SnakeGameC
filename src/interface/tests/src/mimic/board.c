#include <stdbool.h>
#include <stdlib.h>
#include "global.h"
#include "board.h"
#include "consts.h"

// public (real)

struct Board* Board = NULL;
struct Snake Snake;

struct Board get_board() {
	return *Board;
}

// public (only for tests)

void GenerateBoard(unsigned int width, unsigned int height) {
	if (Board != NULL) { FreeBoard(); }
	Board = (struct Board*)malloc(sizeof(struct Board));
	Board->width = width;
	Board->height = height;
	Board->wall_cell = '#';
	Board->free_cell = ' ';
	Board->map = (char**)malloc(sizeof(char*)*Board->height);
	for (int y = 0; y < Board->height; y++) {
		Board->map[y] = (char*)malloc(sizeof(char) * Board->width);
		for (int x = 0; x < Board->width; x++) {
			if (x == 0 || x == (Board->width - 1) || y == 0 || y == (Board->height - 1)) {
				Board->map[y][x] = Board->wall_cell;
			} else {
				Board->map[y][x] = Board->free_cell;
			}
		}
	}
	
	
	Snake.length = 1;
	Snake.direction = DIR_UP;
	Snake.bodyMaxWidth = Board->width - 2;
	Snake.bodyMaxHeight = Board->height - 2;
	Snake.body = (struct Point*)malloc(sizeof(struct Point) * (Board->height - 2) * (Board->width - 2));
	Snake.bodyMap = (bool**)malloc(sizeof(bool*) * Board->height);
	for (int y = 0; y < Board->height; y++) {
		Snake.bodyMap[y] = (bool*)malloc(sizeof(bool)  * Board->width);
		for (int x = 0; x < Board->width; x++) { Snake.bodyMap[y][x] = false; }
	}
	Snake.body[0].x = Board->width / 2;
	Snake.body[0].y = Board->height / 2;
	Snake.bodyMap[Board->height / 2][Board->width / 2] = true;
	
	Board->snake = Snake;
	Board->apple.x = 1;
	Board->apple.y = 1;
}

void SetApple(unsigned int x, unsigned int y) {
	Board->apple.x = x;
	Board->apple.y = y;
}

void SetSnake(unsigned int x, unsigned int y, bool updateLast) {
	if (updateLast) {
		Snake.bodyMap[Snake.body[Snake.length - 1].y][Snake.body[Snake.length - 1].x] = false;
		Snake.body[Snake.length - 1].x = x;
		Snake.body[Snake.length - 1].y = y;
		Snake.bodyMap[Snake.body[Snake.length - 1].y][Snake.body[Snake.length - 1].x] = true;
	} {
		Snake.length++;
		Snake.bodyMap[y][x] = true;
		Snake.body[Snake.length - 1].x = x;
		Snake.body[Snake.length - 1].y = y;
	}
}

void FreeBoard() {
	free(Snake.body);
	for (int y = 0; y < Snake.bodyMaxHeight + 2; y++) { free(Snake.bodyMap[y]); }
	free(Snake.bodyMap);
	for (int y = 0; y < Board->height; y++) { free(Board->map[y]); }
	free(Board->map);
	free(Board);
}