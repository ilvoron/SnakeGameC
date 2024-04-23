#include <stdbool.h>
#include <stdio.h>
#include <windows.h>
#include "output.h"

// private

bool isBackupedOriginalConsoleAttributes = false;
WORD originalConsoleAttributes = 0;

void _BackupDefaultConsoleAttributes() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	originalConsoleAttributes = consoleInfo.wAttributes;
	isBackupedOriginalConsoleAttributes = true;
}

// public

void SetConsoleTextColor(enum ConsoleColor color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD attributes = 0;
	if (!isBackupedOriginalConsoleAttributes) { _BackupDefaultConsoleAttributes(); }
	switch (color) {
		case colorGreen: attributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY; break;
		case colorYellow: attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY; break;
		case colorRed: attributes = FOREGROUND_RED | FOREGROUND_INTENSITY; break;
		case colorBlue: attributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY; break;
		case colorDefault:
		default: attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; break;
	}
	SetConsoleTextAttribute(hConsole, attributes);
}

void PrintOK(bool beforeNL, bool afterNL) {
	if (beforeNL) { printf("\n"); }
	SetConsoleTextColor(colorGreen);
	printf("OK");
	SetConsoleTextColor(colorDefault);
	if (afterNL) { printf("\n"); }
}

void PrintWARN(bool beforeNL, bool afterNL) {
	if (beforeNL) { printf("\n"); }
	SetConsoleTextColor(colorYellow);
	printf("WARN");
	SetConsoleTextColor(colorDefault);
	if (afterNL) { printf("\n"); }
}

void PrintBAD(bool beforeNL, bool afterNL) {
	if (beforeNL) { printf("\n"); }
	SetConsoleTextColor(colorRed);
	printf("BAD");
	SetConsoleTextColor(colorDefault);
	if (afterNL) { printf("\n"); }
}

void PrintSTATUS(bool beforeNL, bool afterNL, const char* str) {
	if (beforeNL) { printf("\n"); }
	SetConsoleTextColor(colorBlue);
	printf("%s", str);
	SetConsoleTextColor(colorDefault);
	if (afterNL) { printf("\n"); }
}