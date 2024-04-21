TARGET = TestProject.exe
CC = gcc

PREF_SRC = ./src/
PREF_OBJ = obj

SRC = $(wildcard $(PREF_SRC)*.c) 
OBJ = $(patsubst $(PREF_SRC)%.c, $(PREF_OBJ)/%.o, $(SRC))

all : clean copy $(TARGET)
	$(TARGET)
	
$(TARGET) : $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)
	
#$(PREF_OBJ)/controller.o: ../controller.c
#	$(CC) $< -o $@ -Isrc

$(PREF_OBJ)/%.o : $(PREF_SRC)%.c 
	$(CC) -c $< -o $@ -Isrc
copy:
	mkdir -p 
	cp ../controller.c ../controller.h ../../global.h
clean :
	del Output.txt $(TARGET) $(PREF_OBJ)\*.o 


