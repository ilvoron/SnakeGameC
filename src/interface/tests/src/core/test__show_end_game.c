#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "test__show_end_game.h"
#include "global.h"
#include "output.h"
#include "consts.h"
#include "interface.h"
#include "tools.h"
#include "board.h"

bool _hasTestShowEndGameBad = false;

void _GenerateEndGames(struct Settings* Settings) {
	GenerateBoard(5, 5);
	struct Board board = get_board();
	
	freopen(TEMP_FILE_EG_WIN, "w", stdout);
	printf(Settings->skin.endameLabels[EG_WIN], board.snake.length, (board.width-2)*(board.height-2), Settings->inputTriggers[I_CONFIRM].keyLabels[0]);
	printf("\n");
	
	freopen(TEMP_FILE_EG_LOSE, "w", stdout);
	printf(Settings->skin.endameLabels[EG_LOSE], board.snake.length, (board.width-2)*(board.height-2), Settings->inputTriggers[I_CONFIRM].keyLabels[0]);
	printf("\n");
	
	freopen(DEFAULT_OUT, "a", stdout);
}

void _TestShowEndGame1(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_end_game]");
	printf(" Test 1. Testing win endgame... ");
	
	freopen(TEMP_FILE, "w", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
	                          Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	show_end_game(EG_WIN);
	freopen(DEFAULT_OUT, "a", stdout);
	usleep(10000);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_EG_WIN)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowEndGameBad = true; }
}

void _TestShowEndGame2(struct Settings* Settings) {
	PrintSTATUS(false, false, "[show_end_game]");
	printf(" Test 2. Testing lose endgame... ");
	
	freopen(TEMP_FILE, "w", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
	                          Settings->inputTriggers[I_RETURN].keyCodes[0], 15000, false,
							  NULL);
	show_end_game(EG_LOSE);
	freopen(DEFAULT_OUT, "a", stdout);
	usleep(10000);
	
	if (CompareFiles(TEMP_FILE, TEMP_FILE_EG_LOSE)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowEndGameBad = true; }
}

// public

bool TestShowEndGame(struct Settings* Settings) {
	printf("Testing ");
	PrintSTATUS(false, false, "show_end_game()");
	printf("...\n");
	
	_GenerateEndGames(Settings);
	_TestShowEndGame1(Settings);
	_TestShowEndGame2(Settings);
	
	printf("Testing ");
	PrintSTATUS(false, false, "show_end_game()");
	printf("... ");
	if (_hasTestShowEndGameBad) { PrintBAD(false, true); }
	else { PrintOK(false, true); }
	return _hasTestShowEndGameBad;
};