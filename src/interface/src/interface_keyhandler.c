#include <unistd.h>
#include "interface_console_tools.h"
#include "interface_global.h"
#include "interface_ingame_renderer.h"
#include "interface_keyhandler.h"



// ---------
//  private
// ---------

int _inputDelay = 10000;
bool _lockAsync = false;



// --------
//  public
// --------

void clear_input() {
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

struct Key get_key() {
	struct Key key = {-1, -1};
	char keyState[256] = {0};
	if (is_console_in_focus() && is_key_not_auto_repeat()) {
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
	}
	return key;
}

DWORD WINAPI key_handler_in_game(LPVOID lpParam) {
	struct Key key;
	while (true) {
		if (!_lockAsync && (_settings->gameState == GS_INGAME || _settings->gameState == GS_INGAME_HIT_APPLE)) {
			_lockAsync = true;
			key = get_key();
			if ((int)key.input >= 0) {
				switch (key.input) {
					case I_RETURN: _settings->gameState = GS_INGAME_USER_ABORT; break;
					case I_LEFT: if (!_settings->isPause) {_settings->inGameKeyHandler(DIR_LEFT);} break;
					case I_UP: if (!_settings->isPause) {_settings->inGameKeyHandler(DIR_UP);} break;
					case I_RIGHT: if (!_settings->isPause) {_settings->inGameKeyHandler(DIR_RIGHT);} break;
					case I_DOWN: if (!_settings->isPause) {_settings->inGameKeyHandler(DIR_DOWN);} break;
					case I_PAUSE: _settings->isPause = !_settings->isPause; render_pause(); break;
					default: break;
				}
			}
			_lockAsync = false;
		}
		usleep(_inputDelay);
	}
}