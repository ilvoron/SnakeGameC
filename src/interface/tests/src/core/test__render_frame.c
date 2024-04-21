#include <stdio.h>
#include <unistd.h>
#include "test__render_frame.h"
#include "global.h"
#include "interface.h"
#include "board.h"
#include "tools.h"
#include "output.h"
#include "consts.h"

bool _hasTestRenderFrameBad = false;

void _OutMap(struct Board Board, struct Settings* Settings) {
	freopen(TEMP_FILE_MAP, "w", stdout);
	for (int y = 0; y < Board.height; y++) {
		for (int x = 0; x < Board.width; x++) {
			if (Board.snake.bodyMap[y][x]) {
				if (Board.snake.body[0].x == x && Board.snake.body[0].y == y) { printf("%c", Settings->skin.snakeHead);}
				else { printf("%c", Settings->skin.snakeBody);}
				continue; 
			}
			if (Board.apple.x == x && Board.apple.y == y) { printf("%c", Settings->skin.appleCell); continue; }
			if (Board.map[y][x] == Board.free_cell) { printf("%c", Settings->skin.freeCell); continue; }
			if (Board.map[y][x] == Board.wall_cell) { printf("%c", Settings->skin.wallCell); continue; }
		}
		printf("\n");
	}
	
	printf(Settings->skin.ingameLabel, Board.snake.length, (Board.width-2)*(Board.height-2), Settings->inputTriggers[I_LEFT].keyLabels[0], Settings->inputTriggers[I_UP].keyLabels[0], Settings->inputTriggers[I_RIGHT].keyLabels[0], Settings->inputTriggers[I_DOWN].keyLabels[0], Settings->inputTriggers[I_RETURN].keyLabels[0]);
	printf("\n");
	freopen(DEFAULT_OUT, "a", stdout);
}

void _TestRenderFrame1_1(struct Settings* Settings) {
	PrintSTATUS(false, false, "[render_frame]");
	printf(" Test 1.1. Testing 1x1 map... ");
	
	GenerateBoard(1, 1);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
	                          Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	render_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestRenderFrameBad = true; }
}

void _TestRenderFrame1_2(struct Settings* Settings) {
	PrintSTATUS(false, false, "[render_frame]");
	printf(" Test 1.2. Testing 2x2 map... ");
	
	GenerateBoard(2, 2);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	render_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
	                          Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestRenderFrameBad = true; }
}

void _TestRenderFrame1_3(struct Settings* Settings) {
	PrintSTATUS(false, false, "[render_frame]");
	printf(" Test 1.3. Testing 3x3 map... ");
	
	GenerateBoard(3, 3);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	render_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
	                          Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestRenderFrameBad = true; }
}

void _TestRenderFrame1_4(struct Settings* Settings) {
	PrintSTATUS(false, false, "[render_frame]");
	printf(" Test 1.4. Testing 4x4 map... ");
	
	GenerateBoard(4, 4);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	render_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
	                          Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestRenderFrameBad = true; }
}

void _TestRenderFrame1_5(struct Settings* Settings) {
	PrintSTATUS(false, false, "[render_frame]");
	printf(" Test 1.5. Testing 5x10 map... ");
	
	GenerateBoard(5, 10);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	render_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
	                          Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestRenderFrameBad = true; }
}

void _TestRenderFrame1_6(struct Settings* Settings) {
	PrintSTATUS(false, false, "[render_frame]");
	printf(" Test 1.6. Testing 15x15 map... ");
	
	GenerateBoard(15, 15);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	render_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
	                          Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestRenderFrameBad = true; }
}

void _TestRenderFrame1_7(struct Settings* Settings) {
	PrintSTATUS(false, false, "[render_frame]");
	printf(" Test 1.7. Testing 40x20 map... ");
	
	GenerateBoard(40, 20);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	render_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
	                          Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestRenderFrameBad = true; }
}

void _TestRenderFrame2_1(struct Settings* Settings) {
	PrintSTATUS(false, false, "[render_frame]");
	printf(" Test 2.1. Testing apple (top left corner)... ");
	
	GenerateBoard(5, 5);
	SetApple(1, 1);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	render_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
	                          Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestRenderFrameBad = true; }
}

void _TestRenderFrame2_2(struct Settings* Settings) {
	PrintSTATUS(false, false, "[render_frame]");
	printf(" Test 2.2. Testing apple (top right corner)... ");
	
	GenerateBoard(5, 5);
	SetApple(3, 1);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	render_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
	                          Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestRenderFrameBad = true; }
}

void _TestRenderFrame2_3(struct Settings* Settings) {
	PrintSTATUS(false, false, "[render_frame]");
	printf(" Test 2.3. Testing apple (bottom left corner)... ");
	
	GenerateBoard(5, 5);
	SetApple(1, 3);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	render_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
	                          Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestRenderFrameBad = true; }
}

void _TestRenderFrame2_4(struct Settings* Settings) {
	PrintSTATUS(false, false, "[render_frame]");
	printf(" Test 2.4. Testing apple (bottom right corner)... ");
	
	GenerateBoard(5, 5);
	SetApple(3, 3);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	render_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
	                          Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestRenderFrameBad = true; }
}

void _TestRenderFrame2_5(struct Settings* Settings) {
	PrintSTATUS(false, false, "[render_frame]");
	printf(" Test 2.5. Testing apple (top left corner in wall)... ");
	
	GenerateBoard(5, 5);
	SetApple(0, 0);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	render_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
	                          Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestRenderFrameBad = true; }
}

void _TestRenderFrame2_6(struct Settings* Settings) {
	PrintSTATUS(false, false, "[render_frame]");
	printf(" Test 2.6. Testing apple (top right corner in wall)... ");
	
	GenerateBoard(5, 5);
	SetApple(4, 0);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	render_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
	                          Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestRenderFrameBad = true; }
}

void _TestRenderFrame2_7(struct Settings* Settings) {
	PrintSTATUS(false, false, "[render_frame]");
	printf(" Test 2.7. Testing apple (bottom left corner in wall)... ");
	
	GenerateBoard(5, 5);
	SetApple(0, 4);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	render_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
	                          Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestRenderFrameBad = true; }
}

void _TestRenderFrame2_8(struct Settings* Settings) {
	PrintSTATUS(false, false, "[render_frame]");
	printf(" Test 2.8. Testing apple (bottom right corner in wall)... ");
	
	GenerateBoard(5, 5);
	SetApple(4, 4);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	render_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
	                          Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestRenderFrameBad = true; }
}

void _TestRenderFrame3_1(struct Settings* Settings) {
	PrintSTATUS(false, false, "[render_frame]");
	printf(" Test 3.1. Testing snake (1-length snake)... ");
	
	GenerateBoard(5, 5);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	render_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
	                          Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestRenderFrameBad = true; }
}

void _TestRenderFrame3_2(struct Settings* Settings) {
	PrintSTATUS(false, false, "[render_frame]");
	printf(" Test 3.2. Testing snake (2-length snake)... ");
	
	GenerateBoard(5, 5);
	SetSnake(2, 3, false);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	render_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
	                          Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestRenderFrameBad = true; }
}

void _TestRenderFrame3_3(struct Settings* Settings) {
	PrintSTATUS(false, false, "[render_frame]");
	printf(" Test 3.3. Testing snake (3-length snake)... ");
	
	GenerateBoard(5, 5);
	SetSnake(2, 3, false);
	SetSnake(1, 3, false);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	render_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
	                          Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestRenderFrameBad = true; }
}

void _TestRenderFrame3_4(struct Settings* Settings) {
	PrintSTATUS(false, false, "[render_frame]");
	printf(" Test 3.4. Testing snake (1-length snake, but moved)... ");
	
	GenerateBoard(5, 5);
	SetSnake(2, 1, true);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	render_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
	                          Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestRenderFrameBad = true; }
}

void _TestRenderFrame3_5(struct Settings* Settings) {
	PrintSTATUS(false, false, "[render_frame]");
	printf(" Test 3.5. Testing snake (1-length snake on a wall cell)... ");
	
	GenerateBoard(5, 5);
	SetSnake(0, 0, true);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	render_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
	                          Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestRenderFrameBad = true; }
}

void _TestRenderFrame3_6(struct Settings* Settings) {
	PrintSTATUS(false, false, "[render_frame]");
	printf(" Test 3.6. Testing snake (1-length snake on an apple cell)... ");
	
	GenerateBoard(5, 5);
	SetSnake(get_board().apple.x, get_board().apple.y, true);
	_OutMap(get_board(), Settings);
	freopen(TEMP_FILE, "w", stdout);
	render_frame();
	freopen(DEFAULT_OUT, "a", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
	                          Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_MAP)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestRenderFrameBad = true; }
}


// public

bool TestRenderFrame(struct Settings* Settings) {
	printf("Testing ");
	PrintSTATUS(false, false, "render_frame()");
	printf("...\n");
	
	_TestRenderFrame1_1(Settings);
	_TestRenderFrame1_2(Settings);
	_TestRenderFrame1_3(Settings);
	_TestRenderFrame1_4(Settings);
	_TestRenderFrame1_5(Settings);
	_TestRenderFrame1_6(Settings);
	_TestRenderFrame1_7(Settings);
	_TestRenderFrame2_1(Settings);
	_TestRenderFrame2_2(Settings);
	_TestRenderFrame2_3(Settings);
	_TestRenderFrame2_4(Settings);
	_TestRenderFrame2_5(Settings);
	_TestRenderFrame2_6(Settings);
	_TestRenderFrame2_7(Settings);
	_TestRenderFrame2_8(Settings);
	_TestRenderFrame3_1(Settings);
	_TestRenderFrame3_2(Settings);
	_TestRenderFrame3_3(Settings);
	_TestRenderFrame3_4(Settings);
	_TestRenderFrame3_5(Settings);
	_TestRenderFrame3_6(Settings);
	
	printf("Testing ");
	PrintSTATUS(false, false, "render_frame()");
	printf("... ");
	if (_hasTestRenderFrameBad) { PrintBAD(false, true); }
	else { PrintOK(false, true); }
	return _hasTestRenderFrameBad;
};