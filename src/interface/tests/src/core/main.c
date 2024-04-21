#include <stdio.h>
#include "global.h"
#include "interface.h"
#include "output.h"
#include "tools.h"
#include "consts.h"
#include "board.h"
#include "output.h"
#include "test__init_interface.h"
#include "test__show_menu.h"
#include "test__render_frame.h"
#include "test__show_end_game.h"
#include "test__show_error.h"
#include "test__close_interface.h"

struct Settings Settings;
bool hasBad = false;

int main() {
	system(Concat("mkdir ", TEMP_PATH));
	freopen(DEFAULT_OUT, "w", stdout);
	printf("Start testing...\n");
	TestInitInterface(&Settings);
	hasBad = TestShowMenu(&Settings) ^ hasBad;
	hasBad = TestRenderFrame(&Settings) ^ hasBad;
	hasBad = TestShowEndGame(&Settings) ^ hasBad;
	hasBad = TestShowError(&Settings) ^ hasBad;
	TestCloseInterface();
	FreeTools();
	FreeBoard();
	ClearKeyInputBuffer();
	printf("Testing was completed... ");
	if (hasBad) { PrintBAD(false, false); }
	else { PrintOK(false, false); }
}