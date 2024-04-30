#include <stdbool.h>
#include <stdio.h>
#include <windows.h>
#include "interface_console_tools.h"
#include "interface_global.h"
#include "interface_keyhandler.h"
#include "interface_menu_renderer.h"
#include "interface_print_tools.h"



// ---------
//  private
// ---------

void _print_settings_speed() {
	clear_screen(false);
	int strCount = 0;
	char buffer[CONSOLE_HEIGHT][MAX_STRING_SIZE];

	sprintf(buffer[0], _settings->skin.menuSpeedLabel, _settings->speed._new, _settings->speed._default, _settings->speed.min, _settings->speed.max, _settings->inputTriggers[I_UP].keyLabels[0], _settings->inputTriggers[I_DOWN].keyLabels[0], _settings->inputTriggers[I_ERASE].keyLabels[0], _settings->inputTriggers[I_CONFIRM].keyLabels[0], _settings->inputTriggers[I_RETURN].keyLabels[0]);

	print_centered_text(buffer, 1, 0);
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



// --------
//  public
// --------

void render_menu() {
	clear_screen(false);

	char buffer[CONSOLE_HEIGHT][MAX_STRING_SIZE];
	for (int i = 0; i < GS__MENU_COUNT; i++) {
		if (i == _gameState) {
			sprintf(buffer[i], "---> [%s] <---", _settings->skin.menuMainLabels[i]);
		} else {
			sprintf(buffer[i], "[%s]", _settings->skin.menuMainLabels[i]);
		}
	}

	sprintf(buffer[GS__MENU_COUNT], _settings->skin.menuMainLabel, _settings->inputTriggers[I_UP].keyLabels[0], _settings->inputTriggers[I_DOWN].keyLabels[0], _settings->inputTriggers[I_CONFIRM].keyLabels[0]);

	print_centered_text(buffer, GS__MENU_COUNT + 1, 0);
}


void change_select(enum MENU_ACTION action) {
	_gameState += (int)action;
	if ((int)_gameState < 0) {
		_gameState = 0;
	} else if (_gameState >= GS__MENU_COUNT) {
		_gameState = GS__MENU_COUNT - 1;
	}
	render_menu();
}

void select_item() {
	if (_gameState != GS_MENU_SPEED) { return; }
	
	bool inSettings = true;
	struct Key key;
	switch (_gameState) {
		case GS_MENU_SPEED:
			enum GAME_STATE savedGameState = _gameState; 
			_gameState = GS_MENU_SPEED_CHANGING;
			_print_settings_speed();
			while (inSettings) {
				key = get_key();
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
							_gameState = savedGameState;
							_settings->speed._new = _settings->speed.current;
							break;
						case I_CONFIRM:
							inSettings = false;
							_gameState = savedGameState;
							_settings->speed.current = _settings->speed._new;
							break;
						default: break;
					}
				}
			}
			break;
		default: return; break;
	}
}