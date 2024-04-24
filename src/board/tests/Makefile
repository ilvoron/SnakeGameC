main: clean board.o snake.o tests.o
	gcc board.o snake.o tests.o -o tests.exe

clean:
	rm -f board.o tests.o snake.o tests.exe

board.o: board.c
	gcc -c board.c
	
snake.o: snake.c
	gcc -c snake.c
	
tests.o: tests.c
	gcc -c tests.c