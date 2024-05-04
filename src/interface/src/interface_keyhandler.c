#include <unistd.h>
#include "global.h"
#include "interface_console_tools.h"
#include "interface_global.h"
#include "interface_ingame_renderer.h"
#include "interface_keyhandler.h"
#include "stdio.h"



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

struct Key get_key(bool forceGet) {
	struct Key key = {-1, -1};
	char keyState[256] = {0};
	if (is_console_in_focus() || forceGet) {
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

enum GAME_EVENT get_event() {
	struct Key key;
	key = get_key(false);
	switch (key.input) {
		case I_RETURN: _settings->gameState = GS_INGAME_USER_ABORT; return GE_ABORT; break;
		case I_LEFT: return GE_LEFT; break;
		case I_UP: return GE_UP; break;
		case I_RIGHT: return GE_RIGHT; break;
		case I_DOWN: return GE_DOWN; break;
		case I_PAUSE: _settings->isPause = !_settings->isPause; render_pause(); return GE_PAUSE; break;
		default: return GE_NONE; break;
	}
}