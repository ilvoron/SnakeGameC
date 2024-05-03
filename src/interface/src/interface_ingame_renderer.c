#include <stdbool.h>
#include <stdio.h>
#include <windows.h>
#include "interface_global.h"
#include "interface_ingame_renderer.h"
#include "interface_print_tools.h"



// ---------
//  private
// ---------

int _snakeLengthLast;
struct Point _appleLast;
struct Point _snakeHeadLast;
struct Point _snakeTailLast;
bool _isPrintingPause = false;
int offsetX = 0;
int offsetY = 0;
int pauseY = 0;

void _print_snake_body(struct Board* board) {
	if (board->snake.hasTurn) {
		if ((board->snake.turn.before == DIR_LEFT && board->snake.turn.after == DIR_DOWN) || (board->snake.turn.before == DIR_UP && board->snake.turn.after == DIR_RIGHT)) { printf("%2.c", _settings->skin.snakeBodyRightDown); }
		else if ((board->snake.turn.before == DIR_LEFT && board->snake.turn.after == DIR_UP) || (board->snake.turn.before == DIR_DOWN && board->snake.turn.after == DIR_RIGHT)) { printf("%2.c", _settings->skin.snakeBodyRightUp); }
		else if ((board->snake.turn.before == DIR_RIGHT && board->snake.turn.after == DIR_DOWN) || (board->snake.turn.before == DIR_UP && board->snake.turn.after == DIR_LEFT)) { printf("%c%c", _settings->skin.snakeBodyLeftRight, _settings->skin.snakeBodyLeftDown); }
		else { printf("%c%c", _settings->skin.snakeBodyLeftRight, _settings->skin.snakeBodyLeftUp); }
	} else {
		if (board->snake.direction == DIR_LEFT || board->snake.direction == DIR_RIGHT) { printf("%c%c", _settings->skin.snakeBodyLeftRight, _settings->skin.snakeBodyLeftRight); }
		else { printf("%2.c", _settings->skin.snakeBodyUpDown); }
	}
}

void _print_snake_head(struct Board* board) {
	char snakeHead;
	switch (board->snake.direction) {
		case DIR_LEFT: snakeHead = _settings->skin.snakeHeadLeft; break;
		case DIR_RIGHT: snakeHead = _settings->skin.snakeHeadRight; break;
		case DIR_UP: snakeHead = _settings->skin.snakeHeadUp; break;
		case DIR_DOWN: snakeHead = _settings->skin.snakeHeadDown; break;
		default: break;
	}
	if (board->snake.length > 1) {
		if (!board->snake.hasTurn) {
			if (board->snake.direction == DIR_RIGHT) { printf("%c%c", _settings->skin.snakeBodyLeftRight, snakeHead); }
			else { printf("%2.c", snakeHead); }
		} else {
			if ((board->snake.turn.before == DIR_DOWN && board->snake.turn.after == DIR_RIGHT) || (board->snake.turn.before == DIR_UP && board->snake.turn.after == DIR_RIGHT)) { printf("%c%c", _settings->skin.snakeBodyLeftRight, snakeHead); } else { printf("%2.c", snakeHead); }
		}
	} else { printf("%2.c", snakeHead); }
}



// --------
//  public
// --------

bool isMapInit = false;

void render_frame_cbased(struct Board* board) {
	clear_screen(false);
	for (int y = 0; y < board->height; y++) {
		for (int x = 0; x < board->width; x++) {
			if (board->snake.bodyMap[y][x]) {
				if (board->snake.body[0].x == x && board->snake.body[0].y == y) {printf("%2.c", _settings->skin.snakeHead); }
				else { printf("%2.c", _settings->skin.snakeBody); }
				continue;
			}
			if (board->apple.x == x && board->apple.y == y) { printf("%2.c", _settings->skin.appleCell); continue; }
			if (board->map[y][x] == board->free_cell) { printf("%2.c", _settings->skin.freeCell); continue; }
			if (board->map[y][x] == board->wall_cell) { printf("%c%c", _settings->skin.wallCell, _settings->skin.wallCell); continue; }
		}
		printf("\n");
	}
	fflush(stdout);
}

void render_frame_dynamic(struct Board* board) {
	if (!isMapInit) {
		clear_screen(false);

		char buffer[CONSOLE_HEIGHT][MAX_STRING_SIZE];
		sprintf(buffer[0], "\n");
		sprintf(buffer[1], _settings->skin.ingameLabelScore, board->snake.length, (board->width-2)*(board->height-2));
		sprintf(buffer[2], _settings->skin.ingameLabelControls, _settings->inputTriggers[I_LEFT].keyLabels[0], _settings->inputTriggers[I_UP].keyLabels[0], _settings->inputTriggers[I_RIGHT].keyLabels[0], _settings->inputTriggers[I_DOWN].keyLabels[0], _settings->inputTriggers[I_PAUSE].keyLabels[0], _settings->inputTriggers[I_RETURN].keyLabels[0]);
		offsetY = print_centered_text(buffer, 3, board->height);
		offsetX = (CONSOLE_WIDTH - board->width * 2 - 1 ) / 2;

		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO screen;
		GetConsoleScreenBufferInfo(console, &screen);
		COORD coords;
		coords.X = offsetX;
		coords.Y = offsetY;
		SetConsoleCursorPosition(console, coords);

		for (int y = 0; y < board->height; y++) {
			for (int x = 0; x < board->width; x++) {
				if (board->snake.bodyMap[y][x]) {
					if (board->snake.body[0].x == x && board->snake.body[0].y == y) {
						_print_snake_head(board);
					} else {
						_print_snake_body(board);
					}
					continue;
				}
				if (board->apple.x == x && board->apple.y == y) {
					printf("%2.c", _settings->skin.appleCell);
					continue;
				}
				if (board->map[y][x] == board->free_cell) {
					printf("%2.c", _settings->skin.freeCell);
					continue;
				}
				if (board->map[y][x] == board->wall_cell) {
					if (x == board->width - 1) {
						if (y == 0 || y == board->height - 1) {
							printf("%c%c%c", _settings->skin.wallCell, _settings->skin.wallCell, _settings->skin.wallCell);
						} else {
							printf(" %c%c", _settings->skin.wallCell, _settings->skin.wallCell);
						}
					} else {
						printf("%c%c", _settings->skin.wallCell, _settings->skin.wallCell);
					}
					continue;
				}
			}
			coords.Y++;
			SetConsoleCursorPosition(console, coords);
		}

		coords.X = 0;
		coords.Y = board->height + offsetY + 1;
		pauseY = board->height + offsetY + 2;
		SetConsoleCursorPosition(console, coords);
		isMapInit = true;
		fflush(stdout);
	} else {
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO screen;
		GetConsoleScreenBufferInfo(console, &screen);
		COORD coords;

		if (_appleLast.x != board->apple.x || _appleLast.y != board->apple.y) {
			coords.X = _appleLast.x*2 + offsetX; coords.Y = _appleLast.y + offsetY;
			SetConsoleCursorPosition(console, coords);
			printf("%2.c", _settings->skin.freeCell);
			coords.X = board->apple.x*2 + offsetX; coords.Y = board->apple.y + offsetY;
			SetConsoleCursorPosition(console, coords);
			printf("%2.c", _settings->skin.appleCell);
		}

		if (board->snake.length == 1) {
			coords.X = _snakeHeadLast.x*2 + offsetX; coords.Y = _snakeHeadLast.y + offsetY;
			SetConsoleCursorPosition(console, coords);
			printf("%2.c", _settings->skin.freeCell);
			coords.X = board->snake.body[0].x*2 + offsetX; coords.Y = board->snake.body[0].y + offsetY;
			SetConsoleCursorPosition(console, coords);
			_print_snake_head(board);
		} else if (_snakeLengthLast != board->snake.length) {
			coords.X = _snakeHeadLast.x*2 + offsetX; coords.Y = _snakeHeadLast.y + offsetY;
			SetConsoleCursorPosition(console, coords);
			_print_snake_body(board);
			coords.X = board->snake.body[0].x*2 + offsetX; coords.Y = board->snake.body[0].y + offsetY;
			SetConsoleCursorPosition(console, coords);
			_print_snake_head(board);
			coords.X = 0; coords.Y = board->height + 1 + offsetY;
			SetConsoleCursorPosition(console, coords);
			char str[MAX_STRING_SIZE];
			sprintf(str, _settings->skin.ingameLabelScore, board->snake.length, (board->width-2)*(board->height-2));
			print_centered_line(str);
		} else {
			coords.X = _snakeHeadLast.x*2 + offsetX; coords.Y = _snakeHeadLast.y + offsetY;
			SetConsoleCursorPosition(console, coords);
			_print_snake_body(board);
			coords.X = board->snake.body[0].x*2 + offsetX; coords.Y = board->snake.body[0].y + offsetY;
			SetConsoleCursorPosition(console, coords);
			_print_snake_head(board);
			coords.X = _snakeTailLast.x*2 + offsetX; coords.Y = _snakeTailLast.y + offsetY;
			SetConsoleCursorPosition(console, coords);
			printf("%2.c", _settings->skin.freeCell);
		}

		coords.X = 0;
		coords.Y = board->height + offsetY + 1;
		SetConsoleCursorPosition(console, coords);
		fflush(stdout);
	}

	_appleLast = board->apple;
	_snakeLengthLast = board->snake.length;
	_snakeHeadLast = board->snake.body[0];
	_snakeTailLast = board->snake.body[_snakeLengthLast - 1];
}

void render_pause() {
	if (!_isPrintingPause) {
		_isPrintingPause = true;
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO screen;
		GetConsoleScreenBufferInfo(console, &screen);
		COORD coordsBefore = screen.dwCursorPosition;
		COORD coords = { 0, pauseY };
		if (_settings->isPause) {
			SetConsoleCursorPosition(console, coords);
			print_centered_line(_settings->skin.ingameLabelPause);
			SetConsoleCursorPosition(console, coordsBefore);
		} else {
			DWORD written;
			FillConsoleOutputCharacter(console, ' ', CONSOLE_WIDTH-1, coords, &written);
			SetConsoleCursorPosition(console, coordsBefore);
		}
		_isPrintingPause = false;
	}
}