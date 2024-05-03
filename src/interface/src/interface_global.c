#include "interface_global.h"

const int VK_0 = 0x30;
const int VK_1 = 0x31;
const int VK_2 = 0x32;
const int VK_3 = 0x33;
const int VK_4 = 0x34;
const int VK_5 = 0x35;
const int VK_6 = 0x36;
const int VK_7 = 0x37;
const int VK_8 = 0x38;
const int VK_9 = 0x39;
const int VK_NUMPAD0 = 0x60;
const int VK_NUMPAD1 = 0x61;
const int VK_NUMPAD2 = 0x62;
const int VK_NUMPAD3 = 0x63;
const int VK_NUMPAD4 = 0x64;
const int VK_NUMPAD5 = 0x65;
const int VK_NUMPAD6 = 0x66;
const int VK_NUMPAD7 = 0x67;
const int VK_NUMPAD8 = 0x68;
const int VK_NUMPAD9 = 0x69;
const int VK_W = 0x57;
const int VK_A = 0x41;
const int VK_S = 0x53;
const int VK_D = 0x44;
const int VK_P = 0x50;
const int VK_LEFT = 0x25;
const int VK_UP = 0x26;
const int VK_RIGHT = 0x27;
const int VK_DOWN = 0x28;
const int VK_RETURN = 0x0D;
const int VK_ESCAPE = 0x1B;
const int VK_END = 0x23;
const int VK_HOME = 0x24;
const int VK_BACK = 0x08;
const int VK_SPACE = 0x20;
const int VK__EXIT = 0x0A;

const struct InputTrigger INPUT_TRIGGERS_DEFAULT[I__COUNT] = {
	{2, {VK_LEFT, VK_A}, {"left arrow", "a"}},
	{2, {VK_UP, VK_W}, {"up arrow", "w"}},
	{2, {VK_RIGHT, VK_D}, {"right arrow", "d"}},
	{2, {VK_DOWN, VK_S}, {"down arrow", "s"}},
	{1, {VK_RETURN}, {"enter"}},
	{1, {VK_ESCAPE}, {"escape"}},
	{1, {VK_BACK}, {"backspace"}},
	{2, {VK_SPACE, VK_P}, {"space", "p"}},
	{20,
		{
			VK_0, VK_1, VK_2, VK_3, VK_4, VK_5, VK_6, VK_7, VK_8, VK_9,
			VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3, VK_NUMPAD4, VK_NUMPAD5, VK_NUMPAD6, VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD9
		},
		{
			"0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
			"NP 0", "NP 1", "NP 2", "NP 3", "NP 4", "NP 5", "NP 6", "NP 7", "NP 8", "NP 9"
		}
	},
	{1, {VK__EXIT}, {"__exit"}}
};

const struct Speed SPEED_DEFAULT = {1, 10, 4, 4, 4};

const struct Skin SKIN_DEFAULT = {219, 149, 250, '$', 180, 195, 193, 194, 254, 187, 188, 201, 200, 205, 186,
	" \n \n\"%s\" and \"%s\" - change menu item\n\"%s\" - select",
	{
		"Start game",
		"Change snake speed",
		"Exit game"
	},
	"Enter the speed of snake: %2.d\n(default=%d, min=%d, max=%d)\n \n \nenter from keyboard\n(or use \"%s\" or \"%s\")\n\"%s\" - erase\n\"%s\" - confirm\n\"%s\" - go back to menu",
	"Score %3.d of %d",
	" \n \nControls:\n\"%s\" - move left\n\"%s\" - move up\n\"%s\" - move right\n\"%s\" - move down\n\"%s\" - pause game\n\"%s\" - go back to menu",
	"     Game paused...     ",
	{
		"You lose! Scored %d of %d\nPress \"%s\" to show menu...",
		"You win! Scored %d of %d\nPress \"%s\" to show menu..."
	},
	{
		"No error"
	}
};