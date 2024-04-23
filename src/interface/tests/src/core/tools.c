#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <windows.h>
#include "tools.h"

// private

HANDLE hThread = NULL;
DWORD dwThreadId = 0;

typedef struct {
	unsigned int keysCount;
	int* keyCodes;
	unsigned int* delays;
	bool* cleanBefore;
	const char* cleanPath;
} ARGS;

DWORD WINAPI _SimulateKeyPress(LPVOID lpParam) {
	ARGS* args = (ARGS*)lpParam;
	for (int i = 0; i < args->keysCount; i++) {
		if (args->cleanBefore[i]) {
			freopen(args->cleanPath, "w", stdout);
		}
		usleep(args->delays[i]);
		INPUT key[1] = {0};
		key[0].type = INPUT_KEYBOARD;
		key[0].ki.wVk = args->keyCodes[i];
		SendInput(1, key, sizeof(INPUT));
	}
	free(args->keyCodes);
	free(args->delays);
	free(args->cleanBefore);
	free(args);
}

// public

bool CompareFiles(const char file1Path[], const char file2Path[]) {
	FILE *file1 = fopen(file1Path, "rb");
	FILE *file2 = fopen(file2Path, "rb");
	if (file1 == NULL || file2 == NULL) {
		if (file1) { fclose(file1); }
		if (file2) { fclose(file2); }
		return false;
	}

	int ch1, ch2;
	do {
		ch1 = fgetc(file1);
		ch2 = fgetc(file2);
		if (ch1 != ch2) {
			fclose(file1);
			fclose(file2);
			return false;
		}
	} while (ch1 != EOF && ch2 != EOF);

	if (ch1 != ch2) {
		fclose(file1);
		fclose(file2);
		return false;
	}

	fclose(file1);
	fclose(file2);
	return true;
}

void SimulateKeyPress(int keyCode) {
	INPUT key[1] = {0};
	key[0].type = INPUT_KEYBOARD;
	key[0].ki.wVk = keyCode;
	SendInput(1, key, sizeof(INPUT));
}

void SimulateKeyPressAssync(unsigned int keysCount, ...) {
	ARGS* args = malloc(sizeof(ARGS));
	args->keysCount = keysCount;
	args->keyCodes = (int*)malloc(sizeof(int) * keysCount);
	args->delays = (unsigned int*)malloc(sizeof(unsigned int) * keysCount);
	args->cleanBefore = (bool*)malloc(sizeof(bool) * keysCount);
	va_list argsV;
	va_start(argsV, keysCount);
	for (int i = 0; i < keysCount * 3; ++i) {
		switch (i % 3) {
			case 0: args->keyCodes[i / 3] = va_arg(argsV, int); break;
			case 1: args->delays[i / 3] = va_arg(argsV, unsigned int); break;
			case 2: args->cleanBefore[i / 3] = va_arg(argsV, int); break;
			default: break;
		}
	}
	args->cleanPath = va_arg(argsV, const char*);
	va_end(argsV);
	if (dwThreadId != 0) {
		CloseHandle(hThread);
		hThread = NULL;
	}
	while (hThread == NULL) { hThread = CreateThread(NULL, 0, &_SimulateKeyPress, args, 0, &dwThreadId); }
}

void ClearKeyInputBuffer() {
	HANDLE inputHandle = GetStdHandle(STD_INPUT_HANDLE);
	FlushConsoleInputBuffer(inputHandle);
}

void FreeTools() {
	CloseHandle(hThread);
	hThread = NULL;
}