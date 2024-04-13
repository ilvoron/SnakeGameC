#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <windows.h>
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

const struct InputTrigger INPUT_TRIGGERS_DEFAULT[I__COUNT] = {
	{2, {VK_LEFT, VK_A}, {"left arrow", "a"}},
	{2, {VK_UP, VK_W}, {"up arrow", "w"}},
	{2, {VK_RIGHT, VK_D}, {"right arrow", "D"}},
	{2, {VK_DOWN, VK_S}, {"down arrow", "s"}},
	{1, {VK_RETURN}, {"enter"}},
	{1, {VK_ESCAPE}, {"escape"}},
	{1, {VK_BACK}, {"backspace"}},
	{20,
		{VK_0, VK_1, VK_2, VK_3, VK_4, VK_5, VK_6, VK_7, VK_8, VK_9,
		 VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3, VK_NUMPAD4, VK_NUMPAD5, VK_NUMPAD6, VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD9,
		},
		{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
		 "NP 0", "NP 1", "NP 2", "NP 3", "NP 4", "NP 5", "NP 6", "NP 7", "NP 8", "NP 9"
	}}
};

const struct Speed SPEED_DEFAULT = {1, 10, 3, 3, 3};

const struct Skin SKIN_DEFAULT = {'#', '*', '.', '$', '+',
	"Use \"%s\" and \"%s\" to change menu item. Press \"%s\" to select",
	{
		"Start game",
		"Change snake speed",
		"Change render type",
		"Exit game"
	},
	"Enter the speed of snake (enter from keyboard or use \"%s\" or \"%s\", \"%s\" to erase), then press \"%s\" or press \"%s\" to go back (default=%d, min=%d, max=%d): %d",
	"Chose render type (use \"%s\" or \"%s\" to select), then press \"%s\" or press \"%s\" to go back: %d\n1. Character-based (slow, accurate)\n2. (recommended) String(line)-based (faster, accurate, may not work)\n3. Dynamic character-based (very fast, not accurate, may not work)",
	"Score %d of %d. Press \"%s\", \"%s\", \"%s\" or \"%s\" to move or press \"%s\" to go back to menu",
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
int _snakeLength;
int _threadNumber;
int _inputDelay = 10000;
HANDLE _hThread = NULL;
DWORD _dwThreadId;
DWORD _originalConsoleMode;

void _set_non_blocking_mode() {
    HANDLE hStdin;
    DWORD fdwMode, cRead;
	GetConsoleMode(hStdin, &_originalConsoleMode);
    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    fdwMode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
    fdwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hStdin, fdwMode);
}

void _restore_default_mode() {
    HANDLE hStdin;
    SetConsoleMode(hStdin, _originalConsoleMode);
}

void _clear_screen() {
	_isClearing = false;
	while (!_isClearing) {
		COORD topLeft = {0, 0};
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO screen;
		DWORD written;
		GetConsoleScreenBufferInfo(console, &screen);
		FillConsoleOutputCharacter(console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
		FillConsoleOutputAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE, screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
		SetConsoleCursorPosition(console, topLeft);
		_isClearing = true;
	}
}

void _render_menu() {
	_clear_screen();
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
	struct _Key key = {-1, -1};
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

DWORD WINAPI _key_handler_in_game(LPVOID lpParam) {
	struct _Key key;
	while (true) {
		if (!_lockAsync && (_settings->gameState == GS_INGAME || _settings->gameState == GS_INGAME_HIT_APPLE)) {
			_lockAsync = true;
			key = _get_key();
			if ((int)key.input >= 0) {
				switch (key.input) {
					case I_RETURN: _settings->gameState = GS_INGAME_USER_ABORT; break;
					case I_LEFT: _settings->inGameKeyHandler(DIR_LEFT); break;
					case I_UP: _settings->inGameKeyHandler(DIR_UP); break;
					case I_RIGHT: _settings->inGameKeyHandler(DIR_RIGHT); break;
					case I_DOWN: _settings->inGameKeyHandler(DIR_DOWN); break;
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
	_clear_screen();
	printf(_settings->skin.menuSpeedLabel, _settings->inputTriggers[I_UP].keyLabels[0], _settings->inputTriggers[I_DOWN].keyLabels[0], _settings->inputTriggers[I_ERASE].keyLabels[0], _settings->inputTriggers[I_CONFIRM].keyLabels[0], _settings->inputTriggers[I_RETURN].keyLabels[0], _settings->speed._default, _settings->speed.min, _settings->speed.max, _settings->speed._new);
	printf("\n");
	fflush(stdout);
}

void _print_settings_render() {
	_clear_screen();
	printf(_settings->skin.menuRenderLabel, _settings->inputTriggers[I_UP].keyLabels[0], _settings->inputTriggers[I_DOWN].keyLabels[0], _settings->inputTriggers[I_CONFIRM].keyLabels[0], _settings->inputTriggers[I_RETURN].keyLabels[0], (_settings->renderType+1));
	printf("\n");
	fflush(stdout);
}

void _select_item() {
	if (_gameState != GS_MENU_SPEED && _gameState != GS_MENU_RENDER) { return; }
	
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
		case GS_MENU_RENDER:
			_gameState = GS_MENU_RENDER_CHANGING;
			_print_settings_render();
			while (inSettings) {
				key = _get_key();
				if (key.input >= 0) {
					switch (key.input) {
						case I_UP:
							_settings->renderType++;
							if (_settings->renderType > 2) {
								_settings->renderType = 2;
							}
							_print_settings_render();
							break;
						case I_DOWN:
							_settings->renderType--;
							if ((int)_settings->renderType < 0) {
								_settings->renderType = 0;
							}
							_print_settings_render();
							break;
						case I_RETURN:
							inSettings = false;
							show_menu();
						case I_CONFIRM:
							inSettings = false;
							show_menu();
						default: break;
					}
				}
			}
			break;
		default: return; break;
	}
}

// public

void init_interface(struct Settings* settings) {
	_set_non_blocking_mode();
	_settings = settings;
	_settings->speed._new = settings->speed._default;
	_clear_input();
	_threadNumber = 1;
	while (_hThread == NULL) {
		_hThread = CreateThread(NULL, 0, _key_handler_in_game, &_threadNumber, 0, &_dwThreadId);
	}
}

void close_interface() {
	_restore_default_mode();
	CloseHandle(_hThread);
}

void show_menu() {
	bool inMenu = true;
	struct _Key key;
	_gameState = GS_MENU_START;
	_isMapInit = false;
	
	_clear_screen();
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
				case I_RETURN:
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
				_clear_screen();
				for (int y = 0; y < board.height; y++) {
					for (int x = 0; x < board.width; x++) {
						if (board.snake.bodyMap[y][x]) {
							if (board.snake.body[0].x == x && board.snake.body[0].y == y) {
								printf("%c", _settings->skin.snakeHead);
							} else {
								printf("%c", _settings->skin.snakeBody);
							}
							continue;
						}
						if (board.apple.x == x && board.apple.y == y) {
							printf("%c", _settings->skin.appleCell);
							continue;
						}
						if (board.map[y][x] == board.free_cell) {
							printf("%c", _settings->skin.freeCell);
							continue;
						}
						if (board.map[y][x] == board.wall_cell) {
							printf("%c", _settings->skin.wallCell);
							continue;
						}
					}
					printf("\n");
				}
				
				printf(_settings->skin.ingameLabel, board.snake.length, (board.width-2)*(board.height-2), _settings->inputTriggers[I_LEFT].keyLabels[0], _settings->inputTriggers[I_UP].keyLabels[0], _settings->inputTriggers[I_RIGHT].keyLabels[0], _settings->inputTriggers[I_DOWN].keyLabels[0], _settings->inputTriggers[I_RETURN].keyLabels[0]);
				printf("\n");
				fflush(stdout);
				break;
			case RT_SBASED:
				_clear_screen();
				char* output;
				int counter = 0;
				output = (char*)malloc(sizeof(char)*board.height*(board.width+1)+1);
				for (int y = 0; y < board.height; y++) {
					for (int x = 0; x < board.width; x++) {
						if (board.snake.bodyMap[y][x]) {
							if (board.snake.body[0].x == x && board.snake.body[0].y == y) {
								output[counter++] = _settings->skin.snakeHead;
							} else {
								output[counter++] = _settings->skin.snakeBody;
							}
							continue;
						}
						if (board.apple.x == x && board.apple.y == y) {
							output[counter++] = _settings->skin.appleCell;
							continue;
						}
						if (board.map[y][x] == board.free_cell) {
							output[counter++] = _settings->skin.freeCell;
							continue;
						}
						if (board.map[y][x] == board.wall_cell) {
							output[counter++] = _settings->skin.wallCell;
							continue;
						}
					}
					output[counter++] = '\n';
				}
				
				output[board.height*(board.width+1)] = '\0';
				printf("%s", output);
				printf(_settings->skin.ingameLabel, board.snake.length, (board.width-2)*(board.height-2), _settings->inputTriggers[I_LEFT].keyLabels[0], _settings->inputTriggers[I_UP].keyLabels[0], _settings->inputTriggers[I_RIGHT].keyLabels[0], _settings->inputTriggers[I_DOWN].keyLabels[0], _settings->inputTriggers[I_RETURN].keyLabels[0]);
				printf("\n");
				fflush(stdout);
				break;
			case RT_DYNAMIC:
				if (!_isMapInit) {
					_clear_screen();
					for (int y = 0; y < board.height; y++) {
						for (int x = 0; x < board.width; x++) {
							if (board.snake.bodyMap[y][x]) {
								if (board.snake.body[0].x == x && board.snake.body[0].y == y) {
									printf("%c", _settings->skin.snakeHead);
								} else {
									printf("%c", _settings->skin.snakeBody);
								}
								continue;
							}
							if (board.apple.x == x && board.apple.y == y) {
								printf("%c", _settings->skin.appleCell);
								continue;
							}
							if (board.map[y][x] == board.free_cell) {
								printf("%c", _settings->skin.freeCell);
								continue;
							}
							if (board.map[y][x] == board.wall_cell) {	
								printf("%c", _settings->skin.wallCell);
								continue;
							}
						}
						printf("\n");
					}
					
					_isMapInit = true;
					printf(_settings->skin.ingameLabel, board.snake.length, (board.width-2)*(board.height-2), _settings->inputTriggers[I_LEFT].keyLabels[0], _settings->inputTriggers[I_UP].keyLabels[0], _settings->inputTriggers[I_RIGHT].keyLabels[0], _settings->inputTriggers[I_DOWN].keyLabels[0], _settings->inputTriggers[I_RETURN].keyLabels[0]);
					printf("\n");
					fflush(stdout);
				} else {
					COORD coords;
					COORD coordsBefore;
					DWORD _writtenChars;
					CONSOLE_SCREEN_BUFFER_INFO screen;
					HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
					GetConsoleScreenBufferInfo(console, &screen);
					coordsBefore = screen.dwCursorPosition;
					
					if (_apple.x != board.apple.x || _apple.y != board.apple.y) {
						coords.X = _apple.x; coords.Y = _apple.y;
						FillConsoleOutputCharacter(console, _settings->skin.freeCell, 1, coords, &_writtenChars);
						coords.X = board.apple.x; coords.Y = board.apple.y;
						FillConsoleOutputCharacter(console, _settings->skin.appleCell, 1, coords, &_writtenChars);
					}
					
					if (board.snake.length == 1) {
						coords.X = _snakeHead.x; coords.Y = _snakeHead.y;
						FillConsoleOutputCharacter(console, _settings->skin.freeCell, 1, coords, &_writtenChars);
						coords.X = board.snake.body[0].x; coords.Y = board.snake.body[0].y;
						FillConsoleOutputCharacter(console, _settings->skin.snakeHead, 1, coords, &_writtenChars);
					} else if (_snakeLength != board.snake.length) {
						coords.X = _snakeHead.x; coords.Y = _snakeHead.y;
						FillConsoleOutputCharacter(console, _settings->skin.snakeBody, 1, coords, &_writtenChars);
						coords.X = board.snake.body[0].x; coords.Y = board.snake.body[0].y;
						FillConsoleOutputCharacter(console, _settings->skin.snakeHead, 1, coords, &_writtenChars);
						coords.X = 0; coords.Y = board.height;
						SetConsoleCursorPosition(console, coords);
						printf(_settings->skin.ingameLabel, board.snake.length, (board.width-2)*(board.height-2), _settings->inputTriggers[I_LEFT].keyLabels[0], _settings->inputTriggers[I_UP].keyLabels[0], _settings->inputTriggers[I_RIGHT].keyLabels[0], _settings->inputTriggers[I_DOWN].keyLabels[0], _settings->inputTriggers[I_RETURN].keyLabels[0]);
						printf("\n");
						fflush(stdout);
					} else {
						coords.X = _snakeHead.x; coords.Y = _snakeHead.y;
						FillConsoleOutputCharacter(console, _settings->skin.snakeBody, 1, coords, &_writtenChars);
						coords.X = board.snake.body[0].x; coords.Y = board.snake.body[0].y;
						FillConsoleOutputCharacter(console, _settings->skin.snakeHead, 1, coords, &_writtenChars);
						coords.X = _snakeTail.x; coords.Y = _snakeTail.y;
						FillConsoleOutputCharacter(console, _settings->skin.freeCell, 1, coords, &_writtenChars);
					}

					SetConsoleCursorPosition(console, coordsBefore);
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
	_settings->gameState = GS_MENU_ENDGAME;
	struct Board board = get_board();
	printf(_settings->skin.endameLabels[endGameCode], board.snake.length, (board.width-2)*(board.height-2), _settings->inputTriggers[I_CONFIRM].keyLabels[0]);
	printf("\n");
	
	bool inEndGame = true;
	struct _Key key;
	while (inEndGame) {
		key = _get_key();
		if (key.input == I_CONFIRM || key.input == I_RETURN) {
			inEndGame = false;
        }
	}
}

void show_error(enum ERROR_CODE errCode) {
	printf(_settings->skin.errorCodeLabels[errCode]);
}