#include "TestModel.h"
#include "controller.h"

int Choice;
int SEG; int EG; int SM; int SG; int UGS; int RF; int CD; int CI; int II; int TestChoice = 1;

const struct Speed SPEED_DEFAULT = {1, 10, 1, 3, 3};

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

int Test_Controller(){
	struct Settings settings;
	remove("Output.txt");
	
	settings.gameState = GS_START;
								 
	settings.speed = SPEED_DEFAULT;
	settings.skin = SKIN_DEFAULT;
	settings.inGameKeyHandler = keyHandler;

	freopen("Output.txt", "a", stdout);	
	settings.errorCode = EC_1; SEG = 0;  EG = 0;  SM = 0;  SG = 0;  UGS = 0;  RF = 0;  CD = 0;  CI = 0;  II = 0;
	End_Of_Program(settings);
	if(get_result("End_Of_Program") != 0) return 2;

	settings.errorCode = EC_2; SEG = 0;  EG = 0;  SM = 0;  SG = 0;  UGS = 0;  RF = 0;  CD = 0;  CI = 0;  II = 0;
	End_Of_Program(settings);
	if(get_result("End_Of_Program") != 0) return 2;
	
	settings.errorCode = EC_3; SEG = 0;  EG = 0;  SM = 0;  SG = 0;  UGS = 0;  RF = 0;  CD = 0;  CI = 0;  II = 0;
	End_Of_Program(settings);
	if(get_result("End_Of_Program") != 0) return 2;

	settings.gameState = GS_INGAME_USER_ABORT;
	settings.errorCode = ERR_NO;
	End_Of_Program(settings);
	
	printf("\n"); 
	SEG = 0;  EG = 0;  SM = 0;  SG = 0;  UGS = 0;  RF = 0;  CD = 0;  CI = 0;  II = 0;
	keyHandler (DIR_LEFT);
	if(get_result("keyHandler") != 0) return 3;
	SEG = 0;  EG = 0;  SM = 0;  SG = 0;  UGS = 0;  RF = 0;  CD = 0;  CI = 0;  II = 0;
	keyHandler (DIR_UP);
	if(get_result("keyHandler") != 0) return 3;
	SEG = 0;  EG = 0;  SM = 0;  SG = 0;  UGS = 0;  RF = 0;  CD = 0;  CI = 0;  II = 0;
	keyHandler (DIR_RIGHT);
	if(get_result("keyHandler") != 0) return 3;
	SEG = 0;  EG = 0;  SM = 0;  SG = 0;  UGS = 0;  RF = 0;  CD = 0;  CI = 0;  II = 0;
	keyHandler (DIR_DOWN);
	if(get_result("keyHandler") != 0) return 3;


	SEG = 0;  EG = 0;  SM = 0;  SG = 0;  UGS = 0;  RF = 0;  CD = 0;  CI = 0;  II = 0;
	Updater(settings);
	if(get_result("Updater") != 0) return 1;

	fclose(stdout);
	freopen("CON", "w",stdout);
	
	return 0;
}
/*
long long get_time() {
	long long milliseconds = clock();
	return milliseconds;
};

void keyHandler (enum DIRECTIONS direction) {
	change_direction(direction, &(settings.gameState));
	render_frame();
	lastframe = get_time();
};

void End_Of_Program(struct Settings settings){
	if (settings.gameState != GS_INGAME_USER_ABORT) {
		show_end_game();								// Показываем конец игры пользователю
	}
	end_game();											// Завершение игры у BOARD	
	show_error(settings.errorCode);	
};									
void Updater (struct Settings settings){
	init_interface(&settings);
	while (settings.gameState != GS_EXIT) {  			// Пока сосстояние игры != выход из игры
		
		settings.gameState = GS_MENU; 						// Переходим в состояние "В МЕНЮ"
		
		while (settings.gameState != GS_MENU_EXIT && settings.gameState != GS_MENU_START) {
			show_menu(&settings); 									// Показываем меню пока состояние из игры не Старт/Выход. Состояние игры меняется внутри функции show_menu
		}
		
		if (settings.gameState == GS_MENU_START) {			// Если в состояние "СТАРТ ИГРЫ"
			settings.gameState = GS_START; 					// Переходим в состояние "СТАРТ" 
			start_game(20, 20); 							// Функция первичного создания поля размером 40/20
			frameTime = 1000 / (settings.speed.current);		// Период обновления экрана в мс  
			
			settings.gameState = GS_INGAME; 				// Переходим в состояние "В ИГРЕ" 					 			
			while (settings.gameState != GS_INGAME_HIT_WALL && settings.gameState != GS_INGAME_HIT_SNAKE && settings.gameState != GS_INGAME_USER_ABORT && settings.gameState != GS_INGAME_WIN) {
															Если не в состоянии "СТОЛКНОВЕНИЕ С СТЕНОЙ" "СТОЛКНОВЕНИЕ С ЗМЕЕЙ" "ПРЕРЫВАНИЕ ИГРЫ" 
				diff = get_time() - lastframe;				// Считаем время с последнего обновления экрана
				if (diff > frameTime * inaccuracy) {		// Если время обновления больше периода обновления с некоторой погрешностью
					update_game_state(&(settings.gameState)); // Проверяем состояние игры у BOARD
					render_frame();							// Отрисовка экрана
					lastframe = get_time();					// Фиксируем время последнего обновления 
					Sleep(frameTime);						// Задержка потока в мс
				} else {
					Sleep(diff);							// Задержка потока в мс
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
};*/

void show_error(enum ERROR_CODE errorCode){
	
	freopen("CON", "a", stdout);
	switch(errorCode){
		case EC_1: 
			printf("Error #1\n");
			break;
		case EC_2: 
			printf("Error #2\n");
			break;
		case EC_3: 
			printf("Error #3\n");
			break;
		default: 
		printf("Cant find Error\n");
		
	}
	fclose(stdout);
	freopen("Output.txt", "a",stdout);
};

void show_end_game(enum END_GAME_CODE){
	SEG++;
	printf("This is show_end_game\n");
};
void end_game(){
	EG++;
	printf("This is end_game\n");
};
void show_menu(struct Settings* settings){
	SM++;
	printf("This is show_menu\n");

	Choice = TestChoice;
	TestChoice++;
	if(Choice == 1) settings->gameState = GS_MENU_START; // Выбираем старт игры
	else settings->gameState = GS_MENU_EXIT; // Выбираем выход из игры
};
void start_game(int width, int height){
	SG++;
	printf("This is start_game\n");
};
void update_game_state(enum GAME_STATE* gameState){
	UGS++;
	printf("This is update_game_state %d\n", UGS);

	if(UGS == 4) *gameState = GS_INGAME_HIT_SNAKE;
};
void render_frame(){
	RF++;
	printf("This is render_frame\n");
};
void change_direction(enum DIRECTIONS direction, enum GAME_STATE* gameState){
	CD++;
	printf("This is change_direction\n");
	printf("Direction: %d\n", direction);
};
void close_interface(){
	CI++;
	printf("This is close_interface\n");
};
void init_interface(struct Settings* settings){
	II++;
	printf("\nThis is init_interface\n");
};

int get_result(char Name[]){

	if((Name == "Updater")&&(SEG != 1 || EG != 1 || SM != 2 || SG != 1 || UGS != 4 || RF != 4 || CD != 0 || CI != 1 || II != 1)){ 
	printf("\nUncorrect work "); puts( Name);
	printf("\nNumber of function calls:\n show_end_game - %d\n end_game - %d\n show_menu - %d\n start_game - %d\n update_game_state - %d\n render_frame - %d\n change_direction - %d\n close_interface - %d\n init_interface - %d\n",SEG , EG , SM , SG , UGS , RF , CD , CI , II );
	return 1;
	}
	if((Name == "keyHandler")&&(SEG != 0 || EG != 0 || SM != 0 || SG != 0 || UGS != 0 || RF != 1 || CD != 1 || CI != 0 || II != 0)) { 
	printf("\nUncorrect work "); puts( Name);	
	printf("\nNumber of function calls:\n show_end_game - %d\n end_game - %d\n show_menu - %d\n start_game - %d\n update_game_state - %d\n render_frame - %d\n change_direction - %d\n close_interface - %d\n init_interface - %d\n",SEG , EG , SM , SG , UGS , RF , CD , CI , II );
	return 2;
	}
	if((Name == "End_Of_Program")&&(SEG != 1 || EG != 1 || SM != 0 || SG != 0 || UGS != 0 || RF != 0 || CD != 0 || CI != 0 || II != 0)) { 
	printf("\nUncorrect work "); puts( Name); 
	printf("\nNumber of function calls:\n show_end_game - %d\n end_game - %d\n show_menu - %d\n start_game - %d\n update_game_state - %d\n render_frame - %d\n change_direction - %d\n close_interface - %d\n init_interface - %d\n",SEG , EG , SM , SG , UGS , RF , CD , CI , II );
	return 3;
	}

	return 0;
};
