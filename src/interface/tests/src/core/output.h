#ifndef OUTPUT_H
#define OUTPUT_H

#include <windows.h>

enum ConsoleColor {
    colorDefault,
    colorGreen,
    colorYellow,
    colorRed,
    colorBlue
};

void SetConsoleTextColor(enum ConsoleColor color);
void PrintOK(bool beforeNL, bool afterNL);
void PrintWARN(bool beforeNL, bool afterNL);
void PrintBAD(bool beforeNL, bool afterNL);
void PrintSTATUS(bool beforeNL, bool afterNL, const char* str);

#endif