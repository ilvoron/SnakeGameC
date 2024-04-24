#include "snake.h"
#include <stdbool.h>
#include <stdlib.h>
#include "global.h"
#include <string.h>
#include <stdio.h>

extern int NUM_FUNK;

void create_snake(struct Snake* snake, int boardWidth, int boardHeight) {
	NUM_FUNK++;
	snake->length = 1;
	snake->direction = DIR_UP;
	snake->bodyMaxWidth = boardWidth - 2;
	snake->bodyMaxHeight = boardHeight - 2;

	snake->body = (struct Point*)malloc(sizeof(struct Point) * (boardHeight - 2) * (boardWidth - 2));
	snake->bodyMap = (bool**)malloc(sizeof(bool*) * boardHeight);
	for (int y = 0; y < boardHeight; y++) {
		snake->bodyMap[y] = (bool*)malloc(sizeof(bool) * boardWidth);
		for (int x = 0; x < boardWidth; x++) { snake->bodyMap[y][x] = false; }
	}

	snake->body[0].x = boardWidth / 2;
	snake->body[0].y = boardHeight / 2;
	snake->bodyMap[boardHeight / 2][boardWidth / 2] = true;
}

void delete_snake(struct Snake* snake) {
	NUM_FUNK++;
	free(snake->body);
	for (int y = 0; y < snake->bodyMaxHeight + 2; y++) { free(snake->bodyMap[y]); }
	free(snake->bodyMap);
}

void move_snake(struct Snake* snake) {
	NUM_FUNK++;
	snake->trailLastPos.x = snake->body[snake->length - 1].x;
	snake->trailLastPos.y = snake->body[snake->length - 1].y;
	snake->bodyMap[snake->body[snake->length - 1].y][snake->body[snake->length - 1].x] = false;
	for (int i = snake->length - 1; i > 0; i--) {
		memcpy(&(snake->body[i].x), &(snake->body[i - 1].x), sizeof(int));
		memcpy(&(snake->body[i].y), &(snake->body[i - 1].y), sizeof(int));
	}

	switch (snake->direction) {
	case DIR_LEFT:
		(snake->body[0].x)--;
		break;
	case DIR_UP:
		(snake->body[0].y)--;
		break;
	case DIR_RIGHT:
		(snake->body[0].x)++;
		break;
	case DIR_DOWN:
		(snake->body[0].y)++;
		break;
	default: break;
	}

	snake->bodyMap[snake->body[0].y][snake->body[0].x] = true;
}

void grow_snake(struct Snake* snake) {};
bool check_snake(struct Snake* snake, int index) { return true; };