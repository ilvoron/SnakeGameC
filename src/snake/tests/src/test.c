#include "snake.h"
#include "global.h"
#include <stdio.h>
#include <stdbool.h>
//test.c

bool test_move_snake(){
	bool isFailed = false;
	printf("Test func move_snake\n");
	struct Snake snake;
	create_snake(&(snake),10,10);
	
	//test 1 (движение вправо)
	printf("TEST 1: ");
	snake.body[0].x=3;
	snake.body[0].y=3;
	snake.direction = DIR_RIGHT;
	move_snake(&(snake));
	if (snake.body[0].x==4 && snake.body[0].y==3){
		printf("OK\n");
	}
	else{
		isFailed = true;
		printf("ERROR\n");
	}
	//test 2 (движение влево)
	printf("TEST 2: ");
	snake.body[0].x=3;
	snake.body[0].y=3;
	snake.direction = DIR_LEFT;
	move_snake(&(snake));
	if (snake.body[0].x==2 && snake.body[0].y==3){
		printf("OK\n");
	}
	else{
		isFailed = true;
		printf("ERROR\n");
	}
	//test 3 (движение вниз)
	printf("TEST 3: ");
	snake.body[0].x=3;
	snake.body[0].y=3;
	snake.direction = DIR_DOWN;
	move_snake(&(snake));
	if (snake.body[0].x==3 && snake.body[0].y==4){
		printf("OK\n");
	}
	else{
		isFailed = true;
		printf("ERROR\n");
	}
	//test 4 (движение вверх)
	printf("TEST 4: ");
	snake.body[0].x=3;
	snake.body[0].y=3;
	snake.direction = DIR_UP;
	move_snake(&(snake));
	if (snake.body[0].x==3 && snake.body[0].y==2){
		printf("OK\n");
	}
	else{
		isFailed = true;
		printf("ERROR\n");
	}
	//test 5 (передвижение змеи без изменения направления
	printf("TEST 5: ");
	create_snake(&(snake),10,10);
	move_snake(&(snake));
	grow_snake(&(snake));
	move_snake(&(snake));
	if (snake.body[1].x==5 && snake.body[1].y==4){
		printf("OK\n");
	}
	else {
		isFailed = true;
		printf("ERROR\n");
	}
	return isFailed;
}

bool test_creare_snake(){
	bool isFailed = false;
	printf("Test func create_snake\n");
	struct Snake snake;
	create_snake(&(snake),10,10);
	//test 1 (проверка направления)
	printf("TEST 1: ");
	if (snake.direction == DIR_UP){
		printf("OK\n");
	}
	else{
		printf("ERROR\n");
		isFailed = true;
	}
	//test 2 (проверка bodyMaxWidth и bodyMaxHeight)
	printf("TEST 2: ");
	if (snake.bodyMaxWidth ==8 &&  snake.bodyMaxHeight ==8){
		printf("OK\n");
	}
	else{
		printf("ERROR\n");
		isFailed = true;
	}
	//test 3 (проверка создания головы змеи)
	printf("TEST 3: ");
	if (snake.body[0].x == 5 && snake.body[0].y == 5){
		printf("OK\n");
	}
	else{
		printf("ERROR\n");
		isFailed = true;
	}
	return isFailed;
}

bool test_grow_snake(){
	bool isFailed = false;
	printf("Test func grow_snake\n");
	struct Snake snake;
	create_snake(&(snake),10,10);
	//test 1
	printf("TEST 1: ");
	grow_snake(&(snake));
	if (snake.length==2){
		printf("OK\n");
	}
	else{
		printf("ERROR\n");
		isFailed = true;
	}
	// test 2 (длина не изменяется при передвижении)
	printf("TEST 2: ");
	create_snake(&(snake),10,10);
	move_snake(&(snake));
	grow_snake(&(snake));
	move_snake(&(snake));
	if (snake.length==2){
		printf("OK\n");
	}
	else{
		printf("ERROR\n");
		isFailed = true;
	}
	return isFailed;
}

bool test_check_snake(){
	bool isFailed = false;
	printf("Test func check_snake\n");
	struct Snake snake;
	create_snake(&(snake),10,10);
	//test 1 (длина змеи = 1)
	printf("TEST 1: ");
	if (check_snake(&(snake),0)==true){
		printf("OK\n");
	}
	else{
		printf("ERROR\n");
		isFailed = true;
	}
	//test 2 (змея не столкнулась)
	printf("TEST 2: ");
	move_snake(&(snake));
	grow_snake(&(snake));
	move_snake(&(snake));
	snake.direction=DIR_LEFT;
	grow_snake(&(snake));
	move_snake(&(snake));
	bool flag = false;
	for (int i = 0; i <snake.length;i++){
		if (!check_snake(&(snake),i)){
			printf("ERROR\n");
			isFailed = true;
			flag=true;
			break;
		}
	}
	if (flag==false){ printf("OK\n");}
	//test 3 (змея столкнулась)
	create_snake(&(snake),10,10);
	printf("TEST 3: ");
	
	move_snake(&(snake));
	grow_snake(&(snake));
	move_snake(&(snake));
	snake.direction=DIR_RIGHT;
	grow_snake(&(snake));
	move_snake(&(snake));
	snake.direction=DIR_DOWN;
	grow_snake(&(snake));
	move_snake(&(snake));
	snake.direction=DIR_LEFT;
	grow_snake(&(snake));
	move_snake(&(snake));
	
	bool flag1 = false;
	for (int i = 1; i <snake.length;i++){
		if (!check_snake(&(snake),i)){
			flag1=true;
			printf("OK\n");
			break;
		}
	}
	if (flag1==false){
		printf("ERROR\n");
		isFailed = true;
	}
	return isFailed;
}

bool test_delete_snake(){
	bool isFailed = false;
	printf("Test func delete_snake\n");
	struct Snake snake;
	//Test 1 (тест отчистки bodyMap)
	printf("TEST 1: ");
	create_snake(&(snake),10,10);
	delete_snake(&(snake));
	if (snake.bodyMap==NULL){ printf("OK\n"); }
	else{ printf("ERROR\n"); isFailed = true; }
	//Test 2 (тест отчистки body)
	printf("TEST 2: ");
	create_snake(&(snake),10,10);
	delete_snake(&(snake));
	if (snake.body==NULL){ printf("OK\n"); }
	else{ printf("ERROR\n"); isFailed = true; }
	
}





int main(){
	bool isFailed = false;
	printf("Start testing module snake...\n");
	isFailed = test_move_snake() ^ isFailed;
	isFailed = test_creare_snake() ^ isFailed;
	isFailed = test_grow_snake() ^ isFailed;
	isFailed = test_check_snake() ^ isFailed;
	isFailed = test_delete_snake() ^ isFailed;
	printf("End testing module snake\n");
	if (isFailed) {
		return -1;
	}
	return 0;
}
