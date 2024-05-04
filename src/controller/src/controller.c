#include "controller.h"

const unsigned int updateFrequency = 10;

struct Settings settings;
long long frameTime;
long long frameStopwatch = 0;

void Updater(struct Settings _settings) {
	settings = _settings;
	init_interface(&settings);
	while (settings.gameState != GS_EXIT) {
		
		settings.gameState = GS_MENU;
		
		while (settings.gameState != GS_MENU_EXIT && settings.gameState != GS_MENU_START) { show_menu(&settings); }
		
		if (settings.gameState == GS_MENU_START) {
			settings.gameState = GS_START;
			start_game(20, 20);
			frameTime = 1000 / (settings.speed.current);
			
			settings.gameState = GS_INGAME;
			settings.isPause = false;
			enum GAME_EVENT geEvent = GE_NONE;
			enum DIRECTIONS direction = DIR_NONE;
			
			while (settings.gameState != GS_INGAME_HIT_WALL && settings.gameState != GS_INGAME_HIT_SNAKE && settings.gameState != GS_INGAME_USER_ABORT && settings.gameState != GS_INGAME_WIN) {
				geEvent = get_event();
				
				switch (geEvent) {
					case GE_LEFT: direction = DIR_LEFT; break;
					case GE_UP: direction = DIR_UP; break;
					case GE_RIGHT: direction = DIR_RIGHT; break;
					case GE_DOWN: direction = DIR_DOWN; break;
				}
				
				if ((direction != DIR_NONE) && change_direction(direction, &(settings.gameState))) {
					direction = DIR_NONE;
					frameStopwatch = 0;
					show_frame();
				}
				
				if (geEvent == GE_NONE) {
					frameStopwatch += updateFrequency;
					if (frameStopwatch >= frameTime) {
						frameStopwatch = 0;
						update_game_state(&(settings.gameState));
						show_frame();
					}
				}
				
				Sleep(updateFrequency);
			}
			
			if (settings.gameState == GS_INGAME_WIN) { show_end_game(EG_WIN); }
			else { show_end_game(EG_LOSE); }
			
			end_game();
		} else {
			settings.gameState = GS_EXIT;
		}
	}
 
	close_interface();
}