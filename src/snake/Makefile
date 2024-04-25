COMPILER = x86_64-w64-mingw32-gcc
TARGET = libsnake.a

PREF_SRC = src
PREF_OBJ = obj
PREF_TMP = tmp

SRC := $(wildcard $(PREF_SRC)/*.c)
OBJ := $(patsubst $(PREF_SRC)/%, $(PREF_OBJ)/%, $(SRC:.c=.o))
OBJ_TARGETS := $(subst \,/,$(OBJ))

ifeq ($(OS),Windows_NT)
TARGET := $(subst /,\,$(TARGET))
PREF_SRC := $(subst /,\,$(PREF_SRC))
PREF_OBJ := $(subst /,\,$(PREF_OBJ))
PREF_TMP := $(subst /,\,$(PREF_TMP))
SRC := $(subst /,\,$(SRC))
OBJ := $(subst /,\,$(OBJ))
else
TARGET := $(subst \,/,$(TARGET))
PREF_SRC := $(subst \,/,$(PREF_SRC))
PREF_OBJ := $(subst \,/,$(PREF_OBJ))
PREF_TMP := $(subst \,/,$(PREF_TMP))
SRC := $(subst \,/,$(SRC))
OBJ := $(subst \,/,$(OBJ))
endif

all: copy $(OBJ_TARGETS)
	ar rcs $(TARGET) $(OBJ)
	
$(PREF_OBJ)/%.o: $(PREF_SRC)/%.c
ifeq ($(OS),Windows_NT)
	if not exist $(PREF_OBJ) mkdir $(PREF_OBJ)
else
	mkdir -p $(PREF_OBJ)
endif
	$(COMPILER) -c $< -o $@ -I$(PREF_TMP)
	
copy: 
ifeq ($(OS),Windows_NT)
	if not exist $(PREF_TMP) mkdir $(PREF_TMP)
	xcopy /Y /Q $(PREF_SRC)\snake.c $(PREF_TMP)
	xcopy /Y /Q $(PREF_SRC)\snake.h $(PREF_TMP)
	xcopy /Y /Q ..\global.h $(PREF_TMP)
else
	mkdir -p $(PREF_TMP)
	cp $(PREF_SRC)/snake.c $(PREF_SRC)/snake.h ../global.h $(PREF_TMP)
endif

clean:
ifeq ($(OS),Windows_NT)
	if exist $(PREF_TMP) rmdir /Q /S $(PREF_TMP)
	if exist $(PREF_OBJ) rmdir /Q /S $(PREF_OBJ)
	if exist $(TARGET) del /Q $(TARGET)
else
	rm -rf $(PREF_TMP) $(PREF_OBJ) $(TARGET)
endif

test:
	make -C tests/
	make clean -C tests/