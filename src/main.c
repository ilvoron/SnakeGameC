#include "controller.h"
#include "global.h"
#include "interface.h"

int main(){
	struct Settings settings;

	settings.gameState = GS_START;
	settings.renderType = RT_DYNAMIC;
	settings.speed = SPEED_DEFAULT;
	settings.skin = SKIN_DEFAULT;
	
	for (int i = 0; i < I__COUNT; ++i) {
		settings.inputTriggers[i] = INPUT_TRIGGERS_DEFAULT[i];
	}

	Updater(settings);

	return 0;
}