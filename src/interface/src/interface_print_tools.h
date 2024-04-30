#ifndef INTERFACE_PRINT_TOOLS_H
#define INTERFACE_PRINT_TOOLS_H
#include <stdbool.h>
#include "global.h"

void clear_screen(bool fullClean);
int print_centered_text(char lines[CONSOLE_HEIGHT][MAX_STRING_SIZE], int numLines, int offsetY);
void print_centered_line(char* text);

#endif