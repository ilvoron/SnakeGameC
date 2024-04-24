CC = gcc
TARGET = libsnake.a

PREF_SRC = src
PREF_OBJ = obj
PREF_TMP = tmp

SRC = $(wildcard $(PREF_SRC)/*.c)
OBJ = $(patsubst $(PREF_SRC)/%, $(PREF_OBJ)/%, $(SRC:.c=.o))

all : test copy prepare $(TARGET) clean

$(TARGET): $(OBJ)
	ar rcs $@ $(OBJ)
	
$(PREF_OBJ)/%.o : $(PREF_SRC)/%.c
	$(CC) -c $< -o $@ -I$(PREF_TMP) -Itests/src
	
copy : 
	cp $(PREF_SRC)\snake.c $(PREF_TMP)
	cp $(PREF_SRC)\snake.h $(PREF_TMP)
	cp ..\global.h $(PREF_TMP)
prepare:
	mkdir -p obj

debug :
	@echo "Module folders: $(MFS)"

clean :
	rm -rf $(PREF_TMP)\* $(PREF_OBJ)\*

test :
	make -C tests/
	make clean -C tests/