#include "controller.h"

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