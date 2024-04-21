#include <stdio.h>
#include <unistd.h>
#include "test__show_menu.h"
#include "global.h"
#include "consts.h"
#include "interface.h"
#include "tools.h"
#include "output.h"

// private

bool _hasTestShowMenuBad = false;

void _GenerateExpectedOutput(struct Settings* Settings) {
	for (int i = 0; i < GS__MENU_COUNT; i++) {
		switch (i) {
			case 0: freopen(TEMP_FILE_SM_0, "w", stdout); break;
			case 1: freopen(TEMP_FILE_SM_1, "w", stdout); break;
			case 2: freopen(TEMP_FILE_SM_2, "w", stdout); break;
			case 3: freopen(TEMP_FILE_SM_3, "w", stdout); break;
			default: break;
		}
		printf(Settings->skin.menuMainLabel, Settings->inputTriggers[I_UP].keyLabels[0], Settings->inputTriggers[I_DOWN].keyLabels[0], Settings->inputTriggers[I_CONFIRM].keyLabels[0]);
		printf("\n");
		for (int j = 0; j < GS__MENU_COUNT; j++) {
			if (j == i) { printf("---> [%s] <---", Settings->skin.menuMainLabels[j]); }
			else { printf("[%s]", Settings->skin.menuMainLabels[j]); }
			printf("\n");
		}
	}
	
	freopen(TEMP_FILE_SPEED, "w", stdout);
	SimulateKeyPressAssync(1, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false, NULL);
	printf(Settings->skin.menuSpeedLabel, Settings->inputTriggers[I_UP].keyLabels[0], Settings->inputTriggers[I_DOWN].keyLabels[0], Settings->inputTriggers[I_ERASE].keyLabels[0], Settings->inputTriggers[I_CONFIRM].keyLabels[0], Settings->inputTriggers[I_RETURN].keyLabels[0], Settings->speed._default, Settings->speed.min, Settings->speed.max, Settings->speed._new);
	printf("\n");
	show_menu();
	usleep(10000);
	
	freopen(TEMP_FILE_RT, "w", stdout);
	SimulateKeyPressAssync(1, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false, NULL);
	printf(Settings->skin.menuRenderLabel, Settings->inputTriggers[I_UP].keyLabels[0], Settings->inputTriggers[I_DOWN].keyLabels[0], Settings->inputTriggers[I_CONFIRM].keyLabels[0], Settings->inputTriggers[I_RETURN].keyLabels[0], (Settings->renderType+1));
	printf("\n");
	show_menu();
	usleep(10000);

	freopen(DEFAULT_OUT, "a", stdout);
}

void _TestShowMenu1(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_menu]");
	printf(" Test 1. Calling function... ");
	
	freopen(TEMP_FILE, "w", stdout);
	SimulateKeyPressAssync(1, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false, NULL);
	show_menu();
	freopen(DEFAULT_OUT, "a", stdout);
	usleep(10000);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_SM_0)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowMenuBad = true; }
}

void _TestShowMenu2_1(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_menu]");
	printf(" Test 2.1. Testing menu inputs (select: \"%s\", keys: \"%s\")... ", Settings->skin.menuMainLabels[0], Settings->inputTriggers[I_UP].keyLabels[0]);
	
	freopen(TEMP_FILE, "w", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_UP].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, true,
							  TEMP_FILE);
	show_menu();
	freopen(DEFAULT_OUT, "a", stdout);
	usleep(10000);

	if (CompareFiles(TEMP_FILE, TEMP_FILE_SM_0)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowMenuBad = true; }
}

void _TestShowMenu2_2(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_menu]");
	printf(" Test 2.2. Testing menu inputs (select: \"%s\", keys: \"%s\")... ", Settings->skin.menuMainLabels[0], Settings->inputTriggers[I_DOWN].keyLabels[0]);
	
	freopen(TEMP_FILE, "w", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_DOWN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, true,
							  TEMP_FILE);
	show_menu();
	freopen(DEFAULT_OUT, "a", stdout);
	usleep(10000);

	if (CompareFiles(TEMP_FILE, TEMP_FILE_SM_1)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowMenuBad = true; }
}

void _TestShowMenu2_3(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_menu]");
	printf(" Test 2.3. Testing menu inputs (select: \"%s\", keys: \"%s\", \"%s\")... ", Settings->skin.menuMainLabels[0], Settings->inputTriggers[I_DOWN].keyLabels[0], Settings->inputTriggers[I_DOWN].keyLabels[0]);
	
	freopen(TEMP_FILE, "w", stdout);
	SimulateKeyPressAssync(3, Settings->inputTriggers[I_DOWN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_DOWN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, true,
							  TEMP_FILE);
	show_menu();
	freopen(DEFAULT_OUT, "a", stdout);
	usleep(10000);

	if (CompareFiles(TEMP_FILE, TEMP_FILE_SM_2)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowMenuBad = true; }
}

void _TestShowMenu2_4(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_menu]");
	printf(" Test 2.4. Testing menu inputs (select: \"%s\", keys: \"%s\", \"%s\", \"%s\")... ", Settings->skin.menuMainLabels[0], Settings->inputTriggers[I_DOWN].keyLabels[0], Settings->inputTriggers[I_DOWN].keyLabels[0], Settings->inputTriggers[I_DOWN].keyLabels[0]);
	
	freopen(TEMP_FILE, "w", stdout);
	SimulateKeyPressAssync(4, Settings->inputTriggers[I_DOWN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_DOWN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_DOWN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, true,
							  TEMP_FILE);
	show_menu();
	freopen(DEFAULT_OUT, "a", stdout);
	usleep(10000);

	if (CompareFiles(TEMP_FILE, TEMP_FILE_SM_3)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowMenuBad = true; }
}

void _TestShowMenu2_5(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_menu]");
	printf(" Test 2.5. Testing menu inputs (select: \"%s\", keys: \"%s\", \"%s\", \"%s\", \"%s\")... ", Settings->skin.menuMainLabels[0], Settings->inputTriggers[I_DOWN].keyLabels[0], Settings->inputTriggers[I_DOWN].keyLabels[0], Settings->inputTriggers[I_DOWN].keyLabels[0], Settings->inputTriggers[I_DOWN].keyLabels[0]);
	
	freopen(TEMP_FILE, "w", stdout);
	SimulateKeyPressAssync(5, Settings->inputTriggers[I_DOWN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_DOWN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_DOWN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_DOWN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, true,
							  TEMP_FILE);
	show_menu();
	freopen(DEFAULT_OUT, "a", stdout);
	usleep(10000);

	if (CompareFiles(TEMP_FILE, TEMP_FILE_SM_3)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowMenuBad = true; }
}

void _TestShowMenu3_1(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_menu]");
	printf(" Test 3.1. Testing menu inputs (selected: \"%s\")... ", Settings->skin.menuMainLabels[0]);
	
	freopen(TEMP_FILE, "w", stdout);
	SimulateKeyPressAssync(1, Settings->inputTriggers[I_CONFIRM].keyCodes[0], 15000, false, NULL);
	show_menu();
	freopen(DEFAULT_OUT, "a", stdout);
	usleep(10000);

	if (Settings->gameState == GS_MENU_START) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowMenuBad = true; }
}

void _TestShowMenu3_2(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_menu]");
	printf(" Test 3.2. Testing menu inputs (selected: \"%s\")... ", Settings->skin.menuMainLabels[1]);
	
	freopen(TEMP_FILE, "w", stdout);
	SimulateKeyPressAssync(4, Settings->inputTriggers[I_DOWN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_CONFIRM].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_CONFIRM].keyCodes[0], 15000, true,
							  Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  TEMP_FILE);
	show_menu();
	freopen(DEFAULT_OUT, "a", stdout);
	usleep(10000);

	if (CompareFiles(TEMP_FILE, TEMP_FILE_SPEED)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowMenuBad = true; }
}

void _TestShowMenu3_3(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_menu]");
	printf(" Test 3.3. Testing menu inputs (selected: \"%s\")... ", Settings->skin.menuMainLabels[2]);
	
	freopen(TEMP_FILE, "w", stdout);
	SimulateKeyPressAssync(5, Settings->inputTriggers[I_DOWN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_DOWN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_CONFIRM].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_CONFIRM].keyCodes[0], 15000, true,
							  Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  TEMP_FILE);
	show_menu();
	freopen(DEFAULT_OUT, "a", stdout);
	usleep(10000);

	if (CompareFiles(TEMP_FILE, TEMP_FILE_RT)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowMenuBad = true; }
}

void _TestShowMenu3_4(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_menu]");
	printf(" Test 3.4. Testing menu inputs (selected: \"%s\")... ", Settings->skin.menuMainLabels[3]);
	
	freopen(TEMP_FILE, "w", stdout);
	SimulateKeyPressAssync(4, Settings->inputTriggers[I_DOWN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_DOWN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_DOWN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_CONFIRM].keyCodes[0], 15000, false,
							  NULL);
	show_menu();
	freopen(DEFAULT_OUT, "a", stdout);
	usleep(10000);

	if (Settings->gameState == GS_MENU_EXIT) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowMenuBad = true; }
}

// public

bool TestShowMenu(struct Settings* Settings) {
	printf("Testing ");
	PrintSTATUS(false, false, "show_menu()");
	printf("...\n");
	
	_GenerateExpectedOutput(Settings);
	_TestShowMenu1(Settings);
	_TestShowMenu2_1(Settings);
	_TestShowMenu2_2(Settings);
	_TestShowMenu2_3(Settings);
	_TestShowMenu2_4(Settings);
	_TestShowMenu2_5(Settings);
	_TestShowMenu3_1(Settings);
	_TestShowMenu3_2(Settings);
	_TestShowMenu3_3(Settings);
	_TestShowMenu3_4(Settings);
	
	printf("Testing ");
	PrintSTATUS(false, false, "show_menu()");
	printf("... ");
	if (_hasTestShowMenuBad) { PrintBAD(false, true); }
	else { PrintOK(false, true); }
	return _hasTestShowMenuBad;
}