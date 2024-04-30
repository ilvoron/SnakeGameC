#ifndef INTERFACE_KEYHANDLER_H
#define INTERFACE_KEYHANDLER_H
#include <windows.h>
#include "global.h"

struct Key {
	enum INPUTS input;
	int offset;
};

void clear_input();
struct Key get_key();
DWORD WINAPI key_handler_in_game(LPVOID lpParam);

#endif