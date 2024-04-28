#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <windows.h>
#include <wincon.h>
#include <wchar.h>
#include "interface.h"
#include "board.h"
#include "global.h"

// public

const int VK_0 = 0x30;
const int VK_1 = 0x31;
const int VK_2 = 0x32;
const int VK_3 = 0x33;
const int VK_4 = 0x34;
const int VK_5 = 0x35;
const int VK_6 = 0x36;
const int VK_7 = 0x37;
const int VK_8 = 0x38;
const int VK_9 = 0x39;
const int VK_W = 0x57;
const int VK_A = 0x41;
const int VK_S = 0x53;
const int VK_D = 0x44;
const int VK_P = 0x50;
const int VK__EXIT = 0x0A;

const struct InputTrigger INPUT_TRIGGERS_DEFAULT[I__COUNT] = {
	{2, {VK_LEFT, VK_A}, {"left arrow", "a"}},
	{2, {VK_UP, VK_W}, {"up arrow", "w"}},
	{2, {VK_RIGHT, VK_D}, {"right arrow", "d"}},
	{2, {VK_DOWN, VK_S}, {"down arrow", "s"}},
	{1, {VK_RETURN}, {"enter"}},
	{3, {VK_ESCAPE, VK_END, VK_HOME}, {"escape", "end", "home"}},
	{1, {VK_BACK}, {"backspace"}},
	{3, {VK_SPACE, VK_P, VK_PAUSE}, {"space", "p", "pause"}},
	{20,
		{
			VK_0, VK_1, VK_2, VK_3, VK_4, VK_5, VK_6, VK_7, VK_8, VK_9,
			VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3, VK_NUMPAD4, VK_NUMPAD5, VK_NUMPAD6, VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD9
		},
		{
			"0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
			"NP 0", "NP 1", "NP 2", "NP 3", "NP 4", "NP 5", "NP 6", "NP 7", "NP 8", "NP 9"
		}
	},
	{1, {VK__EXIT}, {"__exit"}}
};

const struct Speed SPEED_DEFAULT = {1, 10, 3, 3, 3};

const struct Skin SKIN_DEFAULT = {219, 149, 250, '$', 180, 195, 193, 194, 254, 187, 188, 201, 200, 205, 186,
	"Use \"%s\" and \"%s\" to change menu item. Press \"%s\" to select",
	{
		"Start game",
		"Change snake speed",
		"Exit game"
	},
	"Enter the speed of snake (enter from keyboard or use \"%s\" or \"%s\", \"%s\" to erase), then press \"%s\" or press \"%s\" to go back (default=%d, min=%d, max=%d): %d",
	"Score %d of %d",
	"Controls:\n\"%s\" - move left\n\"%s\" - move up\n\"%s\" - move right\n\"%s\" - move down\n\"%s\" - pause game\n\"%s\" - go back to menu",
	"Game paused...",
	{
		"You lose! Scored %d of %d. Press \"%s\" to show menu...",
		"You win! Scored %d of %d. Press \"%s\" to show menu..."
	},
	{
		"No error"
	}
};

// private

struct _Key {
	enum INPUTS input;
	int offset;
};

enum _MENU_ACTION {
	_MA_PREV = -1,
	_MA_NEXT = 1
};

struct Settings* _settings;
struct Point _apple;
struct Point _snakeHead;
struct Point _snakeTail;
enum GAME_STATE _gameState;
bool _lockAsync = false;
bool _isClearing = false;
bool _isMapInit = false;
bool _isRendering = false;
bool _isPrintingPause = false;
int _snakeLength;
int _threadNumber;
int _inputDelay = 10000;
HANDLE _hThread = NULL;
DWORD _dwThreadId;
DWORD _originalConsoleMode;

void _prepare_console() {
	SetConsoleOutputCP(437);
	HANDLE hStdin;
	DWORD fdwMode, cRead;
	GetConsoleMode(hStdin, &_originalConsoleMode);
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	fdwMode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
	fdwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hStdin, fdwMode);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hStdin, &cursorInfo);
	cursorInfo.bVisible = false;
	cursorInfo.dwSize = 1;
	hStdin = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(hStdin, &cursorInfo);
}

void _restore_console() {
	HANDLE hStdin;
	SetConsoleMode(hStdin, _originalConsoleMode);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hStdin, &cursorInfo);
	cursorInfo.bVisible = true;
	cursorInfo.dwSize = 25;
	hStdin = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(hStdin, &cursorInfo);
}

void _clear_screen(bool fullClean) {
	if (!_isClearing) {
		_isClearing = true;
		if (fullClean) {
			system("cls");
		} else {
			COORD topLeft = {0, 0};
			HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
			CONSOLE_SCREEN_BUFFER_INFO screen;
			DWORD written;
			GetConsoleScreenBufferInfo(console, &screen);
			FillConsoleOutputCharacter(console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
			FillConsoleOutputAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE, screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
			SetConsoleCursorPosition(console, topLeft);
		}
		_isClearing = false;
	}
}

void _render_menu() {
	_clear_screen(false);
	printf(_settings->skin.menuMainLabel, _settings->inputTriggers[I_UP].keyLabels[0], _settings->inputTriggers[I_DOWN].keyLabels[0], _settings->inputTriggers[I_CONFIRM].keyLabels[0]);
	printf("\n");
	for (int i = 0; i < GS__MENU_COUNT; i++) {
		if (i == _gameState) {
			printf("---> [%s] <---", _settings->skin.menuMainLabels[i]);
		} else {
			printf("[%s]", _settings->skin.menuMainLabels[i]);
		}
		printf("\n");
	}
	fflush(stdout);
}

void _change_select(int action) {
	_gameState += action;
	if ((int)_gameState < 0) {
		_gameState = 0;
	} else if (_gameState >= GS__MENU_COUNT) {
		_gameState = GS__MENU_COUNT - 1;
	}
	_render_menu(_gameState);
}

struct _Key _get_key() {
	struct _Key key = {I__COUNT, 0};
	char keyState[256] = {0};
	for (int i = 0; i < I__COUNT; i++) {
		for (int j = 0; j < _settings->inputTriggers[i].keysCount; j++) {
			if (GetKeyState(_settings->inputTriggers[i].keyCodes[j]) & 0x8000) {
				key.input = i;
				key.offset = j;
				keyState[_settings->inputTriggers[i].keyCodes[j]] = 0; 
				SetKeyboardState(keyState);
				FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
				return key;
			}
		}
	}
	return key;
}

void _clear_input() {
	struct _Key key = {-1, -1};
	char keyState[256] = {0};
	for (int i = 0; i < I__COUNT; i++) {
		for (int j = 0; j < _settings->inputTriggers[i].keysCount; j++) {
			if (GetKeyState(_settings->inputTriggers[i].keyCodes[j]) & 0x8000) {
				keyState[_settings->inputTriggers[i].keyCodes[j]] = 0; 
				SetKeyboardState(keyState);
			}
		}
	}
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}

void _print_pause() {
	if (!_isPrintingPause) {
		_isPrintingPause = true;
		if (_settings->isPause) {
			printf(". ");
			printf(_settings->skin.ingameLabelPause);
		} else {
			HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
			CONSOLE_SCREEN_BUFFER_INFO screen;
			GetConsoleScreenBufferInfo(console, &screen);
			COORD coords = screen.dwCursorPosition;
			coords.X = coords.X - strlen(_settings->skin.ingameLabelPause) - 2;
			DWORD written;
			FillConsoleOutputCharacter(console, ' ', strlen(_settings->skin.ingameLabelPause) + 2, coords, &written);
			SetConsoleCursorPosition(console, coords);
		}
		_isPrintingPause = false;
	}
}

DWORD WINAPI _key_handler_in_game(LPVOID lpParam) {
	struct _Key key;
	while (true) {
		if (!_lockAsync && (_settings->gameState == GS_INGAME || _settings->gameState == GS_INGAME_HIT_APPLE)) {
			_lockAsync = true;
			key = _get_key();
			if ((int)key.input >= 0) {
				switch (key.input) {
					case I_RETURN: _settings->gameState = GS_INGAME_USER_ABORT; break;
					case I_LEFT: if (!_settings->isPause) {_settings->inGameKeyHandler(DIR_LEFT);} break;
					case I_UP: if (!_settings->isPause) {_settings->inGameKeyHandler(DIR_UP);} break;
					case I_RIGHT: if (!_settings->isPause) {_settings->inGameKeyHandler(DIR_RIGHT);} break;
					case I_DOWN: if (!_settings->isPause) {_settings->inGameKeyHandler(DIR_DOWN);} break;
					case I_PAUSE: _settings->isPause = !_settings->isPause; _print_pause(); break;
					default: break;
				}
			}
			_lockAsync = false;
		}
		usleep(_inputDelay);
	}
}

void _checkspeed(bool smart, int num) {
	if (smart) {
		if (_settings->speed._new > _settings->speed.max) {
			_settings->speed._new = _settings->speed.max;
			if (_settings->speed.max < 20 & num != 0) {
				_settings->speed._new = num;
			}
		} 
		if (_settings->speed._new < _settings->speed.min) {
			_settings->speed._new = _settings->speed.min;
		}
	} else {
		if (_settings->speed._new < _settings->speed.min) {
			_settings->speed._new = _settings->speed.min;
		} else if (_settings->speed._new > _settings->speed.max) {
			_settings->speed._new = _settings->speed.max;
		}
	}
}

void _print_settings_speed() {
	_clear_screen(false);
	printf(_settings->skin.menuSpeedLabel, _settings->inputTriggers[I_UP].keyLabels[0], _settings->inputTriggers[I_DOWN].keyLabels[0], _settings->inputTriggers[I_ERASE].keyLabels[0], _settings->inputTriggers[I_CONFIRM].keyLabels[0], _settings->inputTriggers[I_RETURN].keyLabels[0], _settings->speed._default, _settings->speed.min, _settings->speed.max, _settings->speed._new);
	printf("\n");
	fflush(stdout);
}

void _select_item() {
	if (_gameState != GS_MENU_SPEED) { return; }
	
	bool inSettings = true;
	struct _Key key;
	switch (_gameState) {
		case GS_MENU_SPEED:
			_gameState = GS_MENU_SPEED_CHANGING;
			_print_settings_speed();
			while (inSettings) {
				key = _get_key();
				if (key.input >= 0) {
					switch (key.input) {
						case I_DIGIT:
							int num = key.offset % 10;
							_settings->speed._new *= 10;
							_settings->speed._new += num;
							_checkspeed(true, num);
							_print_settings_speed();
							break;
						case I_UP:
							_settings->speed._new++;
							_checkspeed(false, -1);
							_print_settings_speed();
							break;
						case I_DOWN:
							_settings->speed._new--;
							_checkspeed(false, -1);
							_print_settings_speed();
							break;
						case I_ERASE:
							_settings->speed._new /= 10;
							_checkspeed(false, -1);
							_print_settings_speed();
							break;
						case I_RETURN:
							inSettings = false;
							show_menu();
						case I_CONFIRM:
							inSettings = false;
							_settings->speed.current = _settings->speed._new;
							show_menu();
						default: break;
					}
				}
			}
			break;
		default: return; break;
	}
}

void _print_snake_body(struct Board* board) {
	if (board->snake.hasTurn) {
		if ((board->snake.turn.before == DIR_LEFT && board->snake.turn.after == DIR_DOWN) || (board->snake.turn.before == DIR_UP && board->snake.turn.after == DIR_RIGHT)) {
			printf("%2.c", _settings->skin.snakeBodyRightDown);
		} else if ((board->snake.turn.before == DIR_LEFT && board->snake.turn.after == DIR_UP) || (board->snake.turn.before == DIR_DOWN && board->snake.turn.after == DIR_RIGHT)) {
			printf("%2.c", _settings->skin.snakeBodyRightUp);
		} else if ((board->snake.turn.before == DIR_RIGHT && board->snake.turn.after == DIR_DOWN) || (board->snake.turn.before == DIR_UP && board->snake.turn.after == DIR_LEFT)) {
			printf("%c%c", _settings->skin.snakeBodyLeftRight, _settings->skin.snakeBodyLeftDown);
		} else {
			printf("%c%c", _settings->skin.snakeBodyLeftRight, _settings->skin.snakeBodyLeftUp);
		}
	} else {
		if (board->snake.direction == DIR_LEFT || board->snake.direction == DIR_RIGHT) {
			printf("%c%c", _settings->skin.snakeBodyLeftRight, _settings->skin.snakeBodyLeftRight);
		} else {
			printf("%2.c", _settings->skin.snakeBodyUpDown);
		}
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
			if (board->snake.direction == DIR_RIGHT) {
				printf("%c%c", _settings->skin.snakeBodyLeftRight, snakeHead);
			} else {
				printf("%2.c", snakeHead);
			}
		} else {
			if ((board->snake.turn.before == DIR_DOWN && board->snake.turn.after == DIR_RIGHT) || (board->snake.turn.before == DIR_UP && board->snake.turn.after == DIR_RIGHT)) {
				printf("%c%c", _settings->skin.snakeBodyLeftRight, snakeHead);
			} else {
				printf("%2.c", snakeHead);
			}
		}
	} else {
		printf("%2.c", snakeHead);
	}
}

// public

void init_interface(struct Settings* settings) {
	_prepare_console();
	_settings = settings;
	_settings->speed._new = settings->speed._default;
	_clear_input();
	_threadNumber = 1;
	while (_hThread == NULL) {
		_hThread = CreateThread(NULL, 0, _key_handler_in_game, &_threadNumber, 0, &_dwThreadId);
	}
	_clear_screen(true);
}

void close_interface() {
	CloseHandle(_hThread);
	_restore_console();
	_clear_input();
}

void show_menu() {
	bool inMenu = true;
	struct _Key key;
	_gameState = GS_MENU_START;
	_isMapInit = false;
	
	_clear_screen(false);
	_render_menu();

	while (inMenu) {
		key = _get_key();
		if ((int)key.input >= 0) {
			switch (key.input) {
				case I_UP: _change_select(_MA_PREV); break;
				case I_DOWN: _change_select(_MA_NEXT); break;
				case I_CONFIRM:
					inMenu = false;
					_select_item();
					break;
				case I__EXIT:
					inMenu = false;
					_gameState = GS_MENU_EXIT; break;
					break;
				default: break;
			}
		}
	}
	
	_settings->gameState = _gameState;
}

void render_frame() {
	if (!_isRendering) {
		_isRendering = true;
		struct Board board = get_board();
		switch (_settings->renderType) {
			case RT_CBASED:
				_clear_screen(false);
				for (int y = 0; y < board.height; y++) {
					for (int x = 0; x < board.width; x++) {
						if (board.snake.bodyMap[y][x]) {
							if (board.snake.body[0].x == x && board.snake.body[0].y == y) {
								printf("%2.c", _settings->skin.snakeHead);
							} else {
								printf("%2.c", _settings->skin.snakeBody);
							}
							continue;
						}
						if (board.apple.x == x && board.apple.y == y) {
							printf("%2.c", _settings->skin.appleCell);
							continue;
						}
						if (board.map[y][x] == board.free_cell) {
							printf("%2.c", _settings->skin.freeCell);
							continue;
						}
						if (board.map[y][x] == board.wall_cell) {
							printf("%c%c", _settings->skin.wallCell, _settings->skin.wallCell);
							continue;
						}
					}
					printf("\n");
				}
				fflush(stdout);
				break;
			case RT_DYNAMIC:
				if (!_isMapInit) {
					_clear_screen(false);
					for (int y = 0; y < board.height; y++) {
						for (int x = 0; x < board.width; x++) {
							if (board.snake.bodyMap[y][x]) {
								if (board.snake.body[0].x == x && board.snake.body[0].y == y) {
									_print_snake_head(&board);
								} else {
									_print_snake_body(&board);
								}
								continue;
							}
							if (board.apple.x == x && board.apple.y == y) {
								printf("%2.c", _settings->skin.appleCell);
								continue;
							}
							if (board.map[y][x] == board.free_cell) {
								printf("%2.c", _settings->skin.freeCell);
								continue;
							}
							if (board.map[y][x] == board.wall_cell) {
								if (x == board.width - 1) {
									if (y == 0 || y == board.height - 1) {
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
						printf("\n");
					}
					
					_isMapInit = true;
					printf(_settings->skin.ingameLabelScore, board.snake.length, (board.width-2)*(board.height-2));
					printf("\n");
					printf(_settings->skin.ingameLabelControls, _settings->inputTriggers[I_LEFT].keyLabels[0], _settings->inputTriggers[I_UP].keyLabels[0], _settings->inputTriggers[I_RIGHT].keyLabels[0], _settings->inputTriggers[I_DOWN].keyLabels[0], _settings->inputTriggers[I_PAUSE].keyLabels[0], _settings->inputTriggers[I_RETURN].keyLabels[0]);
					printf("\n");
					
					HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
					CONSOLE_SCREEN_BUFFER_INFO screen;
					GetConsoleScreenBufferInfo(console, &screen);
					COORD coords;
					coords.X = snprintf(NULL, 0, _settings->skin.ingameLabelScore, board.snake.length, (board.width-2)*(board.height-2));
					coords.Y = board.height;
					SetConsoleCursorPosition(console, coords);
					
					fflush(stdout);
				} else {
					HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
					CONSOLE_SCREEN_BUFFER_INFO screen;
					GetConsoleScreenBufferInfo(console, &screen);
					COORD coords;
					
					if (_apple.x != board.apple.x || _apple.y != board.apple.y) {
						coords.X = _apple.x*2; coords.Y = _apple.y;
						SetConsoleCursorPosition(console, coords);
						printf("%2.c", _settings->skin.freeCell);
						coords.X = board.apple.x*2; coords.Y = board.apple.y;
						SetConsoleCursorPosition(console, coords);
						printf("%2.c", _settings->skin.appleCell);
					}
					
					if (board.snake.length == 1) {
						coords.X = _snakeHead.x*2; coords.Y = _snakeHead.y;
						SetConsoleCursorPosition(console, coords);
						printf("%2.c", _settings->skin.freeCell);
						coords.X = board.snake.body[0].x*2; coords.Y = board.snake.body[0].y;
						SetConsoleCursorPosition(console, coords);
						_print_snake_head(&board);
					} else if (_snakeLength != board.snake.length) {
						coords.X = _snakeHead.x*2; coords.Y = _snakeHead.y;
						SetConsoleCursorPosition(console, coords);
						_print_snake_body(&board);
						coords.X = board.snake.body[0].x*2; coords.Y = board.snake.body[0].y;
						SetConsoleCursorPosition(console, coords);
						_print_snake_head(&board);
						coords.X = 0; coords.Y = board.height;
						SetConsoleCursorPosition(console, coords);
						printf(_settings->skin.ingameLabelScore, board.snake.length, (board.width-2)*(board.height-2));
					} else {
						coords.X = _snakeHead.x*2; coords.Y = _snakeHead.y;
						SetConsoleCursorPosition(console, coords);
						_print_snake_body(&board);
						coords.X = board.snake.body[0].x*2; coords.Y = board.snake.body[0].y;
						SetConsoleCursorPosition(console, coords);
						_print_snake_head(&board);
						coords.X = _snakeTail.x*2; coords.Y = _snakeTail.y;
						SetConsoleCursorPosition(console, coords);
						printf("%2.c", _settings->skin.freeCell);
					}
					
					coords.X = snprintf(NULL, 0, _settings->skin.ingameLabelScore, board.snake.length, (board.width-2)*(board.height-2));
					coords.Y = board.height;
					SetConsoleCursorPosition(console, coords);
					fflush(stdout);
				}
				
				_apple = board.apple;
				_snakeLength = board.snake.length;
				_snakeHead = board.snake.body[0];
				_snakeTail = board.snake.body[_snakeLength - 1];
				break;
			default: break;
		}
		_isRendering = false;
	}
}

void show_end_game(enum END_GAME_CODE endGameCode) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	GetConsoleScreenBufferInfo(console, &screen);
	COORD coordsBefore = screen.dwCursorPosition;
	COORD coords = {0, coordsBefore.Y};
	SetConsoleCursorPosition(console, coords);
	
	_settings->gameState = GS_MENU_ENDGAME;
	struct Board board = get_board();
	printf(_settings->skin.endameLabels[endGameCode], board.snake.length, (board.width-2)*(board.height-2), _settings->inputTriggers[I_CONFIRM].keyLabels[0]);
	printf("\n");
	
	bool inEndGame = true;
	struct _Key key;
	while (inEndGame) {
		key = _get_key();
		if (key.input == I_CONFIRM || key.input == I__EXIT) {
			inEndGame = false;
		}
	}
}

void show_error(enum ERROR_CODE errCode) {
	printf(_settings->skin.errorCodeLabels[errCode]);
}