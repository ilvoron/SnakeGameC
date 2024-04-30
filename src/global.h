#ifndef GLOBAL_H
#define GLOBAL_H
#define MAX_STRING_SIZE 512
#define MAX_KEYS_PER_INPUT 20
#define CONSOLE_WIDTH 80
#define CONSOLE_HEIGHT 36
#include <stdbool.h>

struct Point {
	int x;
	int y;
};

enum ERROR_CODE{
	EC_1,
	EC_2,
	EC_3,
	ERR_NO,
	ERR__COUNT
};

// Snake

enum DIRECTIONS {
	DIR_LEFT,
	DIR_UP,
	DIR_RIGHT,
	DIR_DOWN
};

struct Turn{
	enum DIRECTIONS before;
	enum DIRECTIONS after;
	struct Point cell;
};

struct Snake{
	int length;
	int direction;
	struct Point trailLastPos;
	struct Point* body;
	bool** bodyMap;
	int bodyMaxWidth;
	int bodyMaxHeight;
	struct Turn turn;
	bool hasTurn;
};

// Board

struct Board {
	int width;
	int height;
	int free_cells;
	char wall_cell;
	char free_cell;
	char** map;
	struct Snake snake;
	struct Point apple;
};

// Interface

enum GAME_STATE {
	GS_MENU_START,
	GS_MENU_SPEED,
	GS_MENU_EXIT,
	GS__MENU_COUNT,
	GS_MENU,
	GS_MENU_SPEED_CHANGING,
	GS_MENU_RENDER_CHANGING,
	GS_MENU_ENDGAME,
	GS_START,
	GS_INGAME,
	GS_INGAME_HIT_WALL,
	GS_INGAME_HIT_SNAKE,
	GS_INGAME_HIT_APPLE,
	GS_INGAME_USER_ABORT,
	GS_INGAME_WIN,
	GS_EXIT
};

enum INPUTS {
	I_LEFT,
	I_UP,
	I_RIGHT,
	I_DOWN,
	I_CONFIRM,
	I_RETURN,
	I_ERASE,
	I_PAUSE,
	I_DIGIT,
	I__EXIT,
	I__COUNT
};

enum END_GAME_CODE {
	EG_LOSE,
	EG_WIN
};

struct InputTrigger {
	int keysCount;
	int keyCodes[MAX_KEYS_PER_INPUT];
	char keyLabels[MAX_KEYS_PER_INPUT][MAX_STRING_SIZE];
};

struct Speed {
	int min;
	int max;
	int _default;
	int current;
	int _new; // no need to initialize
};

struct Skin {
	char wallCell;
	char appleCell;
	char freeCell;
	char snakeHead;
	char snakeHeadLeft;
	char snakeHeadRight;
	char snakeHeadUp;
	char snakeHeadDown;
	char snakeBody;
	char snakeBodyLeftDown;
	char snakeBodyLeftUp;
	char snakeBodyRightDown;
	char snakeBodyRightUp;
	char snakeBodyLeftRight;
	char snakeBodyUpDown;
	char menuMainLabel[MAX_STRING_SIZE];
	char menuMainLabels[GS__MENU_COUNT][MAX_STRING_SIZE];
	char menuSpeedLabel[MAX_STRING_SIZE];
	char ingameLabelScore[MAX_STRING_SIZE];
	char ingameLabelControls[MAX_STRING_SIZE];
	char ingameLabelPause[MAX_STRING_SIZE];
	char endameLabels[2][MAX_STRING_SIZE];
	char errorCodeLabels[ERR__COUNT][MAX_STRING_SIZE];
};

enum RENDER_TYPE {
	RT_CBASED,
	RT_DYNAMIC
};

struct Settings {
	enum ERROR_CODE errorCode;
	enum GAME_STATE gameState;
	enum RENDER_TYPE renderType;
	struct Speed speed;
	struct Skin skin;
	struct InputTrigger inputTriggers[I__COUNT];
	void (*inGameKeyHandler)(enum DIRECTIONS);
	bool isPause;
};

#endif