TARGET = TestProject.exe
TESTAr = libTestModel.a
CC = gcc


PREF_SRC = ./src/
PREF_OBJ = obj
PREF_TMP = tmp
SRC = $(wildcard $(PREF_TMP)/*.c) 
OBJ = $(patsubst $(PREF_TMP)%.c, $(PREF_OBJ)/%.o, $(SRC))

all : clean copy $(TARGET)
	$(TARGET)
	
$(TARGET) : $(TESTAr)
	$(CC) -o $(TARGET) -L. -lTestModel

$(TESTAr): $(OBJ)
	ar rcs $@ $(OBJ)

$(PREF_OBJ)/%.o : $(PREF_TMP)/%.c 
	$(CC) -c $< -o $@ -Isrc -Itmp

copy:
	xcopy /y ..\src\controller.c tmp
	xcopy /y ..\src\controller.h tmp
	xcopy /y ..\..\global.h tmp
	xcopy /y src tmp
	
clean :
	del /q Output.txt $(TARGET) $(PREF_OBJ)\*.o $(PREF_TMP)

