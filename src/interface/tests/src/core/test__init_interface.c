#include <stdio.h>
#include <unistd.h>
#include "test__init_interface.h"
#include "global.h"
#include "interface.h"
#include "output.h"
#include "tools.h"

// private

bool keyTest = false;
struct _Key {
	enum INPUTS input;
	int offset;
};
extern int _inputDelay;
extern struct _Key _get_key();

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
	for (int i = 0; i < I__COUNT; ++i) {
		Settings->inputTriggers[i] = INPUT_TRIGGERS_DEFAULT[i];
	}
	
	init_interface(Settings);
	PrintOK(false, true);
}

void _TestInitInterface2(struct Settings* Settings) {
	PrintSTATUS(false, false, "[init_interface]");
	printf(" Test 2. Testing inputs (if they're working)... ");

	int testedKeys = 0;
	for (int i = 0; i < I__COUNT; i++) {
		for (int j = 0; j < Settings->inputTriggers[i].keysCount; j++) {
			usleep(_inputDelay);
			SimulateKeyPress(Settings->inputTriggers[i].keyCodes[j]);
			usleep(_inputDelay);
			PrintSTATUS(true, false, "[init_interface]");
			printf(" Test 2.%d. Testing key \"%s\"... ", i + j + 1, Settings->inputTriggers[i].keyLabels[j]);
			if ((int)(_get_key().input) == i) { PrintOK(false, false); }
			else { PrintWARN(false, false); }
			testedKeys++;
		}
	}
	ClearKeyInputBuffer();
	if (testedKeys == 0) {
		PrintOK(false, true);
	} else {
		PrintSTATUS(true, false, "[init_interface]");
		printf(" Test 2. Testing inputs (if they're working)... ");
		PrintOK(false, true);
	}
}

void _TestInitInterface3(struct Settings* Settings) {
	PrintSTATUS(false, false, "[init_interface]");
	printf(" Test 3. Testing inputs in game (for correct behavior)... ");
	
	Settings->gameState = GS_INGAME;
	int testedKeys = 0;
	keyTest = false;
	for (int i = 0; i < I__COUNT; i++) {
		for (int j = 0; j < Settings->inputTriggers[i].keysCount; j++) {
			usleep((int)(_inputDelay * 2.5));
			SimulateKeyPress(Settings->inputTriggers[i].keyCodes[j]);
			usleep((int)(_inputDelay * 2.5));
			PrintSTATUS(true, false, "[init_interface]");
			printf(" Test 3.%d. Testing key \"%s\"... ", i + j + 1, Settings->inputTriggers[i].keyLabels[j]);
			if (i == I_LEFT || i == I_UP || i == I_RIGHT || i == I_DOWN) {
				if (keyTest) { PrintOK(false, false); }
				else { PrintBAD(false, false); }
			} else {
				if (!keyTest) { PrintOK(false, false); }
				else { PrintWARN(false, false); }
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
		PrintOK(false, true);
	}
}

// public

void TestInitInterface(struct Settings* Settings) {
	printf("Testing ");
	PrintSTATUS(false, false, "init_interface()");
	printf("...\n");
	
	_TestInitInterface1(Settings);
	_TestInitInterface2(Settings);
	_TestInitInterface3(Settings);
	
	printf("Testing ");
	PrintSTATUS(false, false, "init_interface()");
	printf("... ");
	PrintOK(false, true);
}