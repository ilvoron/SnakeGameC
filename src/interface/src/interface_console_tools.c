#include <io.h>
#include <stdio.h>
#include <windows.h>
#include "interface_console_tools.h"



// --------
//  public
// --------

int consoleWidth = 80;
int consoleHeight = 25;



// ---------
//  private
// ---------

void _resize_console(int width, int height) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT windowSize = {0, 0, width - 1, height - 1};
	SetConsoleWindowInfo(hConsole, true, &windowSize);
	COORD newSize = {width, height};
	SetConsoleScreenBufferSize(hConsole, newSize);
	consoleWidth = width;
	consoleHeight = height;
}

void _disable_console_resize() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style &= ~(WS_MAXIMIZEBOX | WS_SIZEBOX);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void _disable_text_selection() {
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD prev_mode;
	GetConsoleMode(hInput, &prev_mode);
	SetConsoleMode(hInput, prev_mode & ~(ENABLE_QUICK_EDIT_MODE | ENABLE_EXTENDED_FLAGS));
}

void _disable_scroll_bar() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hOutput, &csbi);
	COORD new_size = {
		csbi.srWindow.Right - csbi.srWindow.Left + 1,
		csbi.srWindow.Bottom - csbi.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(hOutput, new_size);
}

void _set_font() {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	cfi.dwFontSize.Y = 20;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, LF_FACESIZE, L"Courier New");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void _set_non_blocking_mode() {
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD fdwMode;
	fdwMode &= ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
	fdwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hInput, fdwMode);
}

void _hide_caret() {
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hOutput, &cursorInfo);
	cursorInfo.bVisible = false;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(hOutput, &cursorInfo);
}

bool _is_running_as_admin() {
	bool fIsElevated = false;
	HANDLE hToken = NULL;
	TOKEN_ELEVATION tokenElevation;
	DWORD dwSize;

	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
		if (GetTokenInformation(hToken, TokenElevation, &tokenElevation, sizeof(tokenElevation), &dwSize)) {
			fIsElevated = tokenElevation.TokenIsElevated;
		}
	}

	if (hToken) { CloseHandle(hToken); }
	return fIsElevated;
}

void _center_console_window() {
	HWND consoleWindow = GetConsoleWindow();
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	RECT r;
	GetWindowRect(consoleWindow, &r);
	int windowWidth = r.right - r.left;
	int windowHeight = r.bottom - r.top;
	int posX = (screenWidth - windowWidth) / 2;
	int posY = (screenHeight - windowHeight) / 2;
	SetWindowPos(consoleWindow, NULL, posX, posY, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
}

void _disable_key_auto_repeat() {
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
}



// --------
//  public
// --------

void setup_console(int width, int height) {
	_resize_console(width, height);
	_center_console_window();
	_disable_console_resize();
	_disable_text_selection();
	_disable_scroll_bar();
	_set_font();
	_set_non_blocking_mode();
	_hide_caret();
	SetConsoleOutputCP(437);
	SetConsoleTitle("Snake Game");
}

bool is_console_in_output() {
	return _isatty(_fileno(stdout));
}

bool is_console_in_focus() {
	if (_is_running_as_admin() && is_console_in_output()) {
		HWND consoleWindow = GetConsoleWindow();
		HWND foregroundWindow = GetForegroundWindow();
		return (consoleWindow == foregroundWindow);
	} else { return true; };
}

bool is_key_not_auto_repeat() {
	if (is_console_in_output()) {
		HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
		INPUT_RECORD record;
		DWORD read;
		ReadConsoleInput(hInput, &record, 1, &read);
		if (record.EventType == KEY_EVENT) {
			KEY_EVENT_RECORD keyEvent = record.Event.KeyEvent;
			if (keyEvent.bKeyDown && keyEvent.wRepeatCount == 1) {
				return true;
			}
		}
		return false;
	} else { return true; }
}