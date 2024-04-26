#include "snake.h"
#include <stdbool.h>
#include "global.h"
#include "board.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

extern struct Board _board;
struct Settings settings;
struct Snake snake;

int main() {
	bool isFailed = false;
	printf("Start testing module...\n");
	printf("----------------------------------------\n");
	printf("Testing start_game() with params (width = 7, height = 7)...\n");
	start_game(7, 7); // + _create_map, create_snake, _create_apple
	if ((_board.width != 7 || _board.height != 7)){
		printf("Testing start_game()... FAILED\n");
		isFailed = true;
		return -1;
	}
	else {
		printf("Testing start_game()... OK\n");
	}
	printf("----------------------------------------\n");
	printf("Testing update_game_state()...\n");
	_board.snake.direction = DIR_UP;
	_board.snake.bodyMap[_board.snake.trailLastPos.y][_board.snake.trailLastPos.x] = false;
	_board.apple.x = 3;
	_board.apple.y = 3;
	_board.snake.body[0].x = 3;
	_board.snake.body[0].y = 4;
	_board.snake.trailLastPos.x = 3;
	_board.snake.trailLastPos.y = 4;
	_board.snake.bodyMap[4][3] = true;
	update_game_state(&(settings.gameState)); // + move_snake, _check_collision
	if (settings.gameState != GS_INGAME_HIT_APPLE) {
		printf("Testing update_game_state()... FAILED\n");
		isFailed = true;
		return -2;
	}
	else {
		printf("Testing update_game_state()... OK\n");
	}
	printf("----------------------------------------\n");
	printf("Testing change_direction()...\n");
	change_direction(snake.direction, &(settings.gameState));
	if (_board.snake.direction != snake.direction) {
		printf("Testing change_direction()... FAILED\n");
		isFailed = true;
		return -3;
	}
	else {
		printf("Testing change_direction()... OK\n");
	}
	printf("----------------------------------------\n");
	printf("Testing end_game()...\n");
	end_game(); // + delete_snake
	if (_board.map != 0){
		printf("Testing end_game()... FAILED\n");
		isFailed = true;
		return -4;
	}
	else{
		printf("Testing end_game()... OK\n");
	}
	printf("----------------------------------------\n");
	printf("End testing module...\n");
	if (isFailed) {
		return -5;
	}
	return 0;
}