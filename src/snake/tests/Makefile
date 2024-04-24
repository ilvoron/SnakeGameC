testik : prepare copy test.o snake.o
	gcc obj\test.o obj\snake.o -o test.exe

prepare:
	mkdir -p obj

copy :
	cp ..\src\snake.c ..\src\snake.h ..\..\global.h src

test.o : src\test.c
	gcc -c src\test.c -o obj\test.o

snake.o : src\snake.c
	gcc -c src\snake.c -o obj\snake.o

clean:
	rm -rf obj