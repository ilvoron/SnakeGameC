#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "board.h"
#include "snake.h"
#include "global.h"
#include <stdio.h>

struct Board _board;
bool _isUpdadingGameState = false;

// private

int _randInt(int from, int to) {
	srand(time(NULL));
	return rand() % (to - from + 1) + from;
}

void _create_apple() {
	int apple_cell = _randInt(1, _board.free_cells);

	int cells = 0;
	for (int y = 0; y < _board.height; y++) {
		for (int x = 0; x < _board.width; x++) {
			if (_board.map[y][x] == _board.free_cell && !(_board.snake.bodyMap[y][x])) {
				cells++;
				if (cells == apple_cell) {
					_board.apple.x = x;
					_board.apple.y = y;
					_board.free_cells--;
				}
			}
		}
	}
}

void _create_map() {
	_board.map = (char**)malloc(sizeof(char*) * _board.height);
	for (int y = 0; y < _board.height; y++) {
		_board.map[y] = (char*)malloc(sizeof(char) * _board.width);
		for (int x = 0; x < _board.width; x++) {
			if (x == 0 || x == (_board.width - 1) || y == 0 || y == (_board.height - 1)) {
				_board.map[y][x] = _board.wall_cell;
			} else {
				_board.map[y][x] = _board.free_cell;
			}
		}
	}
}

enum GAME_STATE _check_collision() {
	int x; int y;
	for (int i = 0; i < _board.snake.length; i++) {
		x = _board.snake.body[i].x;
		y = _board.snake.body[i].y;
		if (_board.map[y][x] == _board.wall_cell) { return GS_INGAME_HIT_WALL; }
		if (!(check_snake(&(_board.snake), i))) { return GS_INGAME_HIT_SNAKE; }
		if (_board.apple.x == x && _board.apple.y == y) {
			grow_snake(&(_board.snake));
			return GS_INGAME_HIT_APPLE;
		}
	}
	return GS_INGAME;
}

// public

void start_game(int width, int height) {
	_board.width = width;
	_board.height = height;
	_board.wall_cell = '#';
	_board.free_cell = ' ';
	_board.free_cells = (((width - 2) * (height - 2)) - 1);
	_create_map();
	create_snake(&(_board.snake), width, height);
	_create_apple();
}

void end_game() {
	for (int y = 0; y < _board.height; y++) { free(_board.map[y]); }
	free(_board.map);
	_board.map = NULL;
	delete_snake(&(_board.snake));
}

void update_game_state(enum GAME_STATE* gameState) {
	if (!_isUpdadingGameState) {
		_isUpdadingGameState = true;
		if (_board.snake.hasTurn && (_board.snake.turn.cell.x != _board.snake.body[0].x || _board.snake.turn.cell.y != _board.snake.body[0].y)) {
			_board.snake.hasTurn = false;
		}
		move_snake(&(_board.snake));
		*gameState = _check_collision();
		if (_board.snake.length == (_board.width - 2) * (_board.height - 2)) { *gameState = GS_INGAME_WIN; }
		if (*gameState == GS_INGAME_HIT_APPLE) { _create_apple(&_board); }
		_isUpdadingGameState = false;
	}
}

bool change_direction(enum DIRECTIONS direction, enum GAME_STATE* gameState) {
	if (!_isUpdadingGameState) {
		if (_board.snake.length > 1 &&
			((_board.snake.direction == DIR_LEFT && direction == DIR_RIGHT) ||
			(_board.snake.direction == DIR_UP && direction == DIR_DOWN) ||
			(_board.snake.direction == DIR_RIGHT && direction == DIR_LEFT) ||
			(_board.snake.direction == DIR_DOWN && direction == DIR_UP)))
		{ return false; }

		if (_board.snake.length > 1 && _board.snake.direction != direction) {
			_board.snake.hasTurn = true;
			_board.snake.turn.before = _board.snake.direction;
			_board.snake.turn.after = direction;
			_board.snake.turn.cell.x = _board.snake.body[0].x;
			_board.snake.turn.cell.y = _board.snake.body[0].y;
		} else {
			_board.snake.hasTurn = false;
		}

		_board.snake.direction = direction;
		update_game_state(gameState);
		return true;
	} else { return false; }
}

struct Board get_board() {
	return _board;
}