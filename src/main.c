#include "controller.h"

const struct Speed SPEED_DEFAULT = {1, 3, 1, 3, 3};

const struct Skin SKIN_DEFAULT = {'#', '*', '.', '$', '+',
	"menu item",
	{
		"Start",
		"Change speed",
		"Exit"
	},
	"Enter the speed of snake",
	"Score",
	"You lose!"
};

int main(){
	struct Settings settings;
		
	settings.gameState = GS_START;
	settings.renderType = RT_CBASED;
	settings.speed = SPEED_DEFAULT;
	settings.skin = SKIN_DEFAULT;
	settings.inGameKeyHandler = keyHandler;
	
	for (int i = 0; i < I__COUNT; ++i) {
		settings.inputTriggers[i] = INPUT_TRIGGERS_DEFAULT[i];
    }
	
	Updater(settings);
	
	return 0;
}