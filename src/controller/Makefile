CC = gcc
TARGET = libcontroller.a

PREF_SRC = src
PREF_OBJ = obj
PREF_TMP = tmp

SRC = $(wildcard $(PREF_SRC)/*.c)
OBJ = $(patsubst $(PREF_SRC)/%, $(PREF_OBJ)/%, $(SRC:.c=.o))

all : test copy $(TARGET) clean

$(TARGET): $(OBJ)
	ar rcs $@ $(OBJ)
	
$(PREF_OBJ)/%.o : $(PREF_TMP)/%.c
	$(CC) -c $< -o $@ -Itmp -Itests/src
	
copy :
	xcopy /y $(PREF_SRC)\controller.c $(PREF_TMP)
	xcopy /y $(PREF_SRC)\controller.h $(PREF_TMP)
	xcopy /y ..\global.h $(PREF_TMP)
#	xcopy /y tests\src tmp
debug :
	@echo "Module folders: $(MFS)"

clean :
	del /q $(PREF_TMP) $(PREF_OBJ)

test :
	make -C tests/
	make clean -C tests/

