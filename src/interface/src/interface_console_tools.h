#ifndef INTERFACE_CONSOLE_TOOLS_H
#define INTERFACE_CONSOLE_TOOLS_H
#include <stdbool.h>

extern int consoleWidth;
extern int consoleHeight;

void setup_console(int width, int height);
bool is_console_in_output();
bool is_console_in_focus();

#endif