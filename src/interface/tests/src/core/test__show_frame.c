#include <stdio.h>
#include <unistd.h>
#include "test__show_frame.h"
#include "global.h"
#include "interface.h"
#include "board.h"
#include "tools.h"
#include "output.h"
#include "consts.h"

bool _hasTestShowFrameBad = false;

void _OutMap(struct Board Board, struct Settings* Settings) {
	freopen(TEMP_FILE_MAP, "w", stdout);
	for (int y = 0; y < Board.height; y++) {
		for (int x = 0; x < Board.width; x++) {
			if (Board.snake.bodyMap[y][x]) {
				if (Board.snake.body[0].x == x && Board.snake.body[0].y == y) { printf("%2.c", Settings->skin.snakeHead);}
				else { printf("%2.c", Settings->skin.snakeBody);}
				continue; 
			}
			if (Board.apple.x == x && Board.apple.y == y) { printf("%2.c", Settings->skin.appleCell); continue; }
			if (Board.map[y][x] == Board.free_cell) { printf("%2.c", Settings->skin.freeCell); continue; }
			if (Board.map[y][x] == Board.wall_cell) { printf("%c%c", Settings->skin.wallCell, Settings->skin.wallCell); continue; }
		}
		printf("\n");
	}
	freopen(DEFAULT_OUT, "a", stdout);
}

void _TestShowFrame1_1(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_frame]");
	printf(" Test 1.1. Testing 1x1 map... ");
	
	GenerateBoard(1, 1);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	show_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowFrameBad = true; }
}

void _TestShowFrame1_2(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_frame]");
	printf(" Test 1.2. Testing 2x2 map... ");
	
	GenerateBoard(2, 2);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	show_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowFrameBad = true; }
}

void _TestShowFrame1_3(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_frame]");
	printf(" Test 1.3. Testing 3x3 map... ");
	
	GenerateBoard(3, 3);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	show_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowFrameBad = true; }
}

void _TestShowFrame1_4(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_frame]");
	printf(" Test 1.4. Testing 4x4 map... ");
	
	GenerateBoard(4, 4);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	show_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowFrameBad = true; }
}

void _TestShowFrame1_5(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_frame]");
	printf(" Test 1.5. Testing 5x10 map... ");
	
	GenerateBoard(5, 10);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	show_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowFrameBad = true; }
}

void _TestShowFrame1_6(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_frame]");
	printf(" Test 1.6. Testing 15x15 map... ");
	
	GenerateBoard(15, 15);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	show_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowFrameBad = true; }
}

void _TestShowFrame1_7(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_frame]");
	printf(" Test 1.7. Testing 40x20 map... ");
	
	GenerateBoard(40, 20);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	show_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowFrameBad = true; }
}

void _TestShowFrame2_1(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_frame]");
	printf(" Test 2.1. Testing apple (top left corner)... ");
	
	GenerateBoard(5, 5);
	SetApple(1, 1);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	show_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowFrameBad = true; }
}

void _TestShowFrame2_2(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_frame]");
	printf(" Test 2.2. Testing apple (top right corner)... ");
	
	GenerateBoard(5, 5);
	SetApple(3, 1);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	show_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowFrameBad = true; }
}

void _TestShowFrame2_3(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_frame]");
	printf(" Test 2.3. Testing apple (bottom left corner)... ");
	
	GenerateBoard(5, 5);
	SetApple(1, 3);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	show_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowFrameBad = true; }
}

void _TestShowFrame2_4(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_frame]");
	printf(" Test 2.4. Testing apple (bottom right corner)... ");
	
	GenerateBoard(5, 5);
	SetApple(3, 3);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	show_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowFrameBad = true; }
}

void _TestShowFrame2_5(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_frame]");
	printf(" Test 2.5. Testing apple (top left corner in wall)... ");
	
	GenerateBoard(5, 5);
	SetApple(0, 0);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	show_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowFrameBad = true; }
}

void _TestShowFrame2_6(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_frame]");
	printf(" Test 2.6. Testing apple (top right corner in wall)... ");
	
	GenerateBoard(5, 5);
	SetApple(4, 0);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	show_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowFrameBad = true; }
}

void _TestShowFrame2_7(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_frame]");
	printf(" Test 2.7. Testing apple (bottom left corner in wall)... ");
	
	GenerateBoard(5, 5);
	SetApple(0, 4);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	show_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowFrameBad = true; }
}

void _TestShowFrame2_8(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_frame]");
	printf(" Test 2.8. Testing apple (bottom right corner in wall)... ");
	
	GenerateBoard(5, 5);
	SetApple(4, 4);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	show_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowFrameBad = true; }
}

void _TestShowFrame3_1(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_frame]");
	printf(" Test 3.1. Testing snake (1-length snake)... ");
	
	GenerateBoard(5, 5);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	show_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowFrameBad = true; }
}

void _TestShowFrame3_2(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_frame]");
	printf(" Test 3.2. Testing snake (2-length snake)... ");
	
	GenerateBoard(5, 5);
	SetSnake(2, 3, false);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	show_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowFrameBad = true; }
}

void _TestShowFrame3_3(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_frame]");
	printf(" Test 3.3. Testing snake (3-length snake)... ");
	
	GenerateBoard(5, 5);
	SetSnake(2, 3, false);
	SetSnake(1, 3, false);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	show_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowFrameBad = true; }
}

void _TestShowFrame3_4(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_frame]");
	printf(" Test 3.4. Testing snake (1-length snake, but moved)... ");
	
	GenerateBoard(5, 5);
	SetSnake(2, 1, true);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	show_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowFrameBad = true; }
}

void _TestShowFrame3_5(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_frame]");
	printf(" Test 3.5. Testing snake (1-length snake on a wall cell)... ");
	
	GenerateBoard(5, 5);
	SetSnake(0, 0, true);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	show_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowFrameBad = true; }
}

void _TestShowFrame3_6(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_frame]");
	printf(" Test 3.6. Testing snake (1-length snake on an apple cell)... ");
	
	GenerateBoard(5, 5);
	SetSnake(get_board().apple.x, get_board().apple.y, true);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	show_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowFrameBad = true; }
}


// public

bool TestRenderFrame(struct Settings* Settings) {
	printf("Testing ");
	PrintSTATUS(false, false, "show_frame()");
	printf("...\n");
	
	_TestShowFrame1_1(Settings);
	_TestShowFrame1_2(Settings);
	_TestShowFrame1_3(Settings);
	_TestShowFrame1_4(Settings);
	_TestShowFrame1_5(Settings);
	_TestShowFrame1_6(Settings);
	_TestShowFrame1_7(Settings);
	_TestShowFrame2_1(Settings);
	_TestShowFrame2_2(Settings);
	_TestShowFrame2_3(Settings);
	_TestShowFrame2_4(Settings);
	_TestShowFrame2_5(Settings);
	_TestShowFrame2_6(Settings);
	_TestShowFrame2_7(Settings);
	_TestShowFrame2_8(Settings);
	_TestShowFrame3_1(Settings);
	_TestShowFrame3_2(Settings);
	_TestShowFrame3_3(Settings);
	_TestShowFrame3_4(Settings);
	_TestShowFrame3_5(Settings);
	_TestShowFrame3_6(Settings);
	
	printf("Testing ");
	PrintSTATUS(false, false, "show_frame()");
	printf("... ");
	if (_hasTestShowFrameBad) { PrintBAD(false, true); }
	else { PrintOK(false, true); }
	return _hasTestShowFrameBad;
};