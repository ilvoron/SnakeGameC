CC = gcc
TARGET = controller.a

PREF_SRC = src
PREF_OBJ = obj
PREF_TMP = tmp

SRC = $(wildcard $(PREF_TMP)/*.c)
OBJ = $(patsubst $(PREF_TMP)/%.c, $(PREF_OBJ)/%.o, $(SRC))

all : test copy $(TARGET)	
	$(TARGET) 

$(TARGET): $(OBJ)
	ar rcs $@ $(OBJ)
	
$(PREF_OBJ)/%.o : $(PREF_TMP)/%.c
	$(CC) -c $< -o $@ -Itests/src -Itmp
	
copy :
	xcopy /y $(PREF_SRC)\controller.c $(PREF_TMP)
	xcopy /y $(PREF_SRC)\controller.h $(PREF_TMP)
#	xcopy /y ..\main.c $(PREF_TMP)
	xcopy /y ..\global.h $(PREF_TMP)

debug :
	@echo "Module folders: $(MFS)"

clean :
	del /q $(TARGET) $(PREF_TMP) $(PREF_OBJ)

test :
	make -C tests/
	make clean -C tests/

