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

/*void __test__render_frame() {
	render_frame();
}

void __test__show_end_game() {
	show_end_game(EG_WIN);
}

void __test__show_error() {
	enum ERROR_CODE errCode = ERR_NO;
	show_error(errCode);
}*/

int main() {
	system(Concat("mkdir ", TEMP_PATH));
	freopen(DEFAULT_OUT, "w", stdout);
	printf("Start testing...\n");
	TestInitInterface(&Settings);
	TestShowMenu(&Settings);
	TestRenderFrame(&Settings);
	TestShowEndGame(&Settings);
	TestShowError(&Settings);
	TestCloseInterface();
	FreeTools();
	FreeBoard();
	ClearKeyInputBuffer();
	printf("Testing was completed... ");
	PrintOK(false, false);
}