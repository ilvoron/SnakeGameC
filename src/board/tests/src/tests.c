#include "snake.h"
#include <stdbool.h>
#include "global.h"
#include "board.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

extern struct Board _board;
extern int NUM_FUNK;
struct Settings settings;
struct Snake snake;

int main() {
	bool isFailed = false;
	printf("Start testing module...\n");
	printf("----------------------------------------\n");
	printf("Testing start_game() with params (width = 7, height = 7)...\n");
	start_game(7, 7); // + _create_map, create_snake, _create_apple
	if ((_board.width != 7 || _board.height != 7) || (NUM_FUNK != 3)){
		printf("Testing start_game()... FAILED\n");
		isFailed = true;
		return -1;
	}
	else {
		printf("Testing start_game()... OK\n");
	}
	printf("----------------------------------------\n");
	printf("Testing update_game_state()...\n");
	int f = NUM_FUNK;
	update_game_state(&(settings.gameState)); // + move_snake, _check_collision
	if (NUM_FUNK - f != 2) {
		printf("Testing update_game_state()... FAILED\n");
		isFailed = true;
		return -2;
	}
	else {
		printf("Testing update_game_state()... OK\n");
	}
	printf("----------------------------------------\n");
	printf("Testing change_direction()...\n");
	f = NUM_FUNK;
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
	f = NUM_FUNK;
	end_game(); // + delete_snake
	if ((_board.map != 0) || (NUM_FUNK - f != 1)){
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