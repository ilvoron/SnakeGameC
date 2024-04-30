#ifndef INTERFACE_GLOBAL_H
#define INTERFACE_GLOBAL_H
#define CONSOLE_WIDTH 80
#define CONSOLE_HEIGHT 35
#include "global.h"

extern struct Settings* _settings;
extern enum GAME_STATE _gameState;

extern const struct InputTrigger INPUT_TRIGGERS_DEFAULT[I__COUNT];
extern const struct Speed SPEED_DEFAULT;
extern const struct Skin SKIN_DEFAULT;

#endif