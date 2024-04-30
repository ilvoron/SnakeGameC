#include <string.h>
#include <stdio.h>
#include <windows.h>
#include "interface_console_tools.h"
#include "interface_print_tools.h"



// ---------
//  private
// ---------

bool _isClearing = false;



// --------
//  public
// --------

void clear_screen(bool fullClean) {
	if (!_isClearing) {
		_isClearing = true;
		if (fullClean) { system("cls"); }
		else {
			COORD topLeft = {0, 0};
			HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
			CONSOLE_SCREEN_BUFFER_INFO screen;
			DWORD written;
			GetConsoleScreenBufferInfo(console, &screen);
			FillConsoleOutputCharacter(console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
			FillConsoleOutputAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE, screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
			SetConsoleCursorPosition(console, topLeft);
		}
		_isClearing = false;
	}
}

int print_centered_text(char lines[CONSOLE_HEIGHT][MAX_STRING_SIZE], int numLines, int offsetY) {
	int fixNumLines = numLines;
	for (int i = 0; i < fixNumLines; i++) {
		char* token = strtok(lines[i], "\n");
		int offset = 0;
		while (token != NULL) {
			if (offset > 0) {
				for (int j = numLines - 1; j > i + offset; j--) {
					strcpy(lines[j], lines[j-1]);
				}
				sprintf(lines[i + offset], token);
				numLines++;
			}
			offset++;
			token = strtok(NULL, "\n");
		}
	}

	int verticalStart = (consoleHeight + offsetY - numLines) / 2;
	if (verticalStart < 0) { verticalStart = 0; }
	int initVerticalStart = verticalStart;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = {0, verticalStart};

	for (int i = 0; i < numLines; i++) {
		int len = strlen(lines[i]);
		int horizontalStart = (consoleWidth - len) / 2;
		if (horizontalStart < 0) { horizontalStart = 0; }

		coord.X = horizontalStart;
		coord.Y = verticalStart + i;
		SetConsoleCursorPosition(hConsole, coord);
		printf("%s", lines[i]);
	}
	
	fflush(stdout);
	return initVerticalStart - offsetY;
}

void print_centered_line(char* text) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	GetConsoleScreenBufferInfo(console, &screen);
	COORD coords = screen.dwCursorPosition;
	char* token = strtok(text, "\n");
	int counter = 0;
	while (token != NULL) {
		if (counter > 0) { coords.Y++; }
		int len = strlen(token);
		int pos = (consoleWidth - len) / 2;
		if (pos < 0) pos = 0;
		coords.X = pos;
		SetConsoleCursorPosition(console, coords);
		printf("%s", token);
		token = strtok(NULL, "\n");
		counter++;
	}
}