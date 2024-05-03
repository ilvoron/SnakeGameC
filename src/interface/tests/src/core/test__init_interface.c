#include <stdio.h>
#include <unistd.h>
#include "test__init_interface.h"
#include "global.h"
#include "interface.h"
#include "output.h"
#include "tools.h"
#include "consts.h"

// private

bool keyTest = false;
struct Key {
	enum INPUTS input;
	int offset;
};
extern int _inputDelay;
extern struct Key get_key(bool forceGet);
bool _hasTestInitInterfaceBad = false;

void _KeyHandler(enum DIRECTIONS direction) {
	keyTest = true;
	BYTE keyboardState[256];
	memset(keyboardState, 0, sizeof(keyboardState));
	SetKeyboardState(keyboardState);
}

void _TestInitInterface1(struct Settings* Settings) {
	PrintSTATUS(false, false, "[init_interface]");
	printf(" Test 1. Calling function... ");
	
	Settings->gameState = GS_START;
	Settings->renderType = RT_CBASED;
	Settings->speed = SPEED_DEFAULT;
	Settings->skin = SKIN_DEFAULT;
	Settings->inGameKeyHandler = &_KeyHandler;
	Settings->isPause = false;
	for (int i = 0; i < I__COUNT; ++i) {
		Settings->inputTriggers[i] = INPUT_TRIGGERS_DEFAULT[i];
	}
	freopen(TEMP_FILE, "w", stdout);
	init_interface(Settings);
	freopen(DEFAULT_OUT, "a", stdout);
	PrintOK(false, true);
}

void _TestInitInterface2(struct Settings* Settings) {
	PrintSTATUS(false, false, "[init_interface]");
	printf(" Test 2. Testing inputs (if they're working)... ");
	ClearKeyInputBuffer();
	bool _hasTestInitInterface2Warn = false;
	
	int testedKeys = 0;
	for (int i = 0; i < I__COUNT; i++) {
		for (int j = 0; j < Settings->inputTriggers[i].keysCount; j++) {
			usleep(_inputDelay * 5);
			SimulateKeyPress(Settings->inputTriggers[i].keyCodes[j]);
			usleep(_inputDelay);
			PrintSTATUS(true, false, "[init_interface]");
			printf(" Test 2.%d. Testing key \"%s\"... ", i + j + 1, Settings->inputTriggers[i].keyLabels[j]);
			freopen(TEMP_FILE, "w", stdout);
			if ((int)(get_key(true).input) == i) { freopen(DEFAULT_OUT, "a", stdout); PrintOK(false, false); }
			else { freopen(DEFAULT_OUT, "a", stdout); PrintWARN(false, false); _hasTestInitInterface2Warn = true; }
			testedKeys++;
		}
	}
	ClearKeyInputBuffer();
	if (testedKeys == 0) {
		PrintOK(false, true);
	} else {
		PrintSTATUS(true, false, "[init_interface]");
		printf(" Test 2. Testing inputs (if they're working)... ");
		if (_hasTestInitInterface2Warn) { PrintWARN(false, true); }
		else { PrintOK(false, true); }
	}
}

void _TestInitInterface3(struct Settings* Settings) {
	PrintSTATUS(false, false, "[init_interface]");
	printf(" Test 3. Testing inputs in game (for correct behavior)... ");
	bool _hasTestInitInterface3Warn = false;
	bool _hasTestInitInterface3Bad = false;
	
	Settings->gameState = GS_INGAME;
	int testedKeys = 0;
	keyTest = true;
	ClearKeyInputBuffer();
	
	for (int i = 0; i < I__COUNT; i++) {
		for (int j = 0; j < Settings->inputTriggers[i].keysCount; j++) {
			usleep(_inputDelay * 5);
			SimulateKeyPress(Settings->inputTriggers[i].keyCodes[j]);
			usleep(_inputDelay);
			PrintSTATUS(true, false, "[init_interface]");
			printf(" Test 3.%d. Testing key \"%s\"... ", i + j + 1, Settings->inputTriggers[i].keyLabels[j]);
			if (i == I_LEFT || i == I_UP || i == I_RIGHT || i == I_DOWN) {
				if (keyTest) { PrintOK(false, false); }
				else { PrintBAD(false, false); _hasTestInitInterface3Bad = true; _hasTestInitInterfaceBad = true; }
			} else {
				if (!keyTest) { PrintOK(false, false); }
				else { PrintWARN(false, false); _hasTestInitInterface3Warn = true; }
			}
			keyTest = false;
			testedKeys++;
		}
	}
	ClearKeyInputBuffer();
	Settings->gameState = GS_START;
		if (testedKeys == 0) {
		PrintOK(false, true);
	} else {
		PrintSTATUS(true, false, "[init_interface]");
		printf(" Test 3. Testing inputs in game (for correct behavior)... ");
		if (_hasTestInitInterface3Warn) { PrintWARN(false, true); }
		else if (_hasTestInitInterface3Bad) { PrintBAD(false, true); }
		else { PrintOK(false, true); }
	}
}

// public

bool TestInitInterface(struct Settings* Settings) {
	printf("Testing ");
	PrintSTATUS(false, false, "init_interface()");
	printf("...\n");
	
	_TestInitInterface1(Settings);
	_TestInitInterface2(Settings);
	_TestInitInterface3(Settings);
	
	printf("Testing ");
	PrintSTATUS(false, false, "init_interface()");
	printf("... ");
	if (_hasTestInitInterfaceBad) { PrintBAD(false, true); }
	else { PrintOK(false, true); }
	return _hasTestInitInterfaceBad;
}