#include "controller.h"

const int inaccuracy = 0.2;
struct Settings settings;
long long lastframe = 0.0;
long long diff;
long long frameTime;
bool useInaccuracy = false;

long long get_time() {
	long long miliseconds = clock();
	return miliseconds;
}

void keyHandler (enum DIRECTIONS direction) {
	if (change_direction(direction, &(settings.gameState))) {
		useInaccuracy = true;
		lastframe = get_time();
		Sleep(50);
		show_frame();
	}
}

void End_Of_Program(struct Settings settings){
	end_game();											// Завершение игры у BOARD	
};

void Updater(struct Settings _settings) {
	settings = _settings;
	init_interface(&settings);
	while (settings.gameState != GS_EXIT) {  			// Пока сосстояние игры != выход из игры
		
		settings.gameState = GS_MENU; 						// Переходим в состояние "В МЕНЮ"
		
		while (settings.gameState != GS_MENU_EXIT && settings.gameState != GS_MENU_START) {
			show_menu(&settings); 									// Показываем меню пока состояние из игры не Старт/Выход. Состояние игры меняется внутри функции show_menu
		}
		
		if (settings.gameState == GS_MENU_START) {			// Если в состояние "СТАРТ ИГРЫ"
			settings.gameState = GS_START; 					// Переходим в состояние "СТАРТ" 
			start_game(20, 20); 							// Функция первичного создания поля размером 20/20
			frameTime = 1000 / (settings.speed.current);		// Период обновления экрана в мс  
			
			settings.gameState = GS_INGAME; 				// Переходим в состояние "В ИГРЕ" 					 			
			settings.isPause = false;
			while (settings.gameState != GS_INGAME_HIT_WALL && settings.gameState != GS_INGAME_HIT_SNAKE && settings.gameState != GS_INGAME_USER_ABORT && settings.gameState != GS_INGAME_WIN) {
				if (!settings.isPause) {
																// Если не в состоянии "СТОЛКНОВЕНИЕ С СТЕНОЙ" "СТОЛКНОВЕНИЕ С ЗМЕЕЙ" "ПРЕРЫВАНИЕ ИГРЫ" 
					diff = get_time() - lastframe;				// Считаем время с последнего обновления экрана
					if (diff > frameTime * (0.9 + inaccuracy * useInaccuracy)) {		// Если время обновления больше периода обновления с некоторой погрешностью
						useInaccuracy = false;
						update_game_state(&(settings.gameState)); // Проверяем состояние игры у BOARD
						show_frame();							// Отрисовка экрана
						lastframe = get_time();					// Фиксируем время последнего обновления 
						Sleep(frameTime);						// Задержка потока в мс
					} else {
						Sleep(diff);							// Задержка потока в мс
					}
				
				} else {
					lastframe = get_time();
					Sleep(10);
				}
			}
			
			if (settings.gameState == GS_INGAME_WIN) {
				show_end_game(EG_WIN);
			}
			else {
				show_end_game(EG_LOSE);
			}
			
			End_Of_Program(settings);
		} else {
			settings.gameState = GS_EXIT;					// Переходим в состояние "ВЫХОД"
		}
	}
 
	close_interface();
}