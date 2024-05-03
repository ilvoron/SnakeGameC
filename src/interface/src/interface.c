#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wchar.h>
#include <windows.h>
#include "board.h"
#include "global.h"
#include "interface.h"
#include "interface_console_tools.h"
#include "interface_ingame_renderer.h"
#include "interface_keyhandler.h"
#include "interface_menu_renderer.h"
#include "interface_print_tools.h"



// ---------
//  private
// ---------

struct Settings* _settings;
enum GAME_STATE _gameState = GS_MENU_START;
HANDLE _hThread = NULL;
bool _isRendering = false;
bool _inMenu = false;



// --------
//  public
// --------

void init_interface(struct Settings* settings) {
	while (_hThread == NULL) { _hThread = CreateThread(NULL, 0, key_handler_in_game, NULL, 0, NULL); }
	_settings = settings;
	_settings->speed._new = settings->speed._default;
	setup_console(CONSOLE_WIDTH, CONSOLE_HEIGHT);
	clear_input(_settings);
	clear_screen(true);
}

void close_interface() {
	CloseHandle(_hThread);
	clear_input(_settings);
}

void show_menu() {
	_inMenu = true;
	isMapInit = false;
	struct Key key;

	clear_screen(false);
	render_menu();

	while (_inMenu) {
		key = get_key(false);
		if ((int)key.input >= 0) {
			switch (key.input) {
				case I_UP: change_select(MA_PREV); break;
				case I_DOWN: change_select(MA_NEXT); break;
				case I_CONFIRM: _inMenu = false; select_item(); break;
				case I__EXIT: _inMenu = false; _gameState = GS_MENU_EXIT; break;
				default: break;
			}
		}
	}

	_settings->gameState = _gameState;
}

void show_frame() {
	if (!_isRendering) {
		_isRendering = true;
		struct Board board = get_board();
		switch (_settings->renderType) {
			case RT_CBASED: render_frame_cbased(&board); break;
			case RT_DYNAMIC: render_frame_dynamic(&board); break;
			default: break;
		}
		_isRendering = false;
	}
}

void show_end_game(enum END_GAME_CODE endGameCode) {
	_settings->gameState = GS_MENU_ENDGAME;
	struct Board board = get_board();
	char str[MAX_STRING_SIZE];
	sprintf(str,_settings->skin.endameLabels[endGameCode], board.snake.length, (board.width-2)*(board.height-2), _settings->inputTriggers[I_CONFIRM].keyLabels[0]);
	print_centered_line(str);

	bool inEndGame = true;
	struct Key key;
	while (inEndGame) {
		key = get_key(false);
		if (key.input == I_CONFIRM || key.input == I__EXIT) { inEndGame = false; }
	}
}

void show_error(enum ERROR_CODE errCode) {
	if (is_console_in_output()) {
		MessageBox(NULL, _settings->skin.errorCodeLabels[errCode], "Error", MB_OK | MB_ICONERROR);
	} else {
		printf("%s", _settings->skin.errorCodeLabels[errCode]);
	}
}