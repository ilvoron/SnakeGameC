COMPILER = x86_64-w64-mingw32-gcc
TARGET = libboard.a

PREF_SRC = src
PREF_OBJ = obj
PREF_TMP = tmp

SRC := $(wildcard $(PREF_SRC)/*.c) $(PREF_SRC)/board.c
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

main: copy $(OBJ_TARGETS)
	ar rcs $(TARGET) $(OBJ)

copy:
ifeq ($(OS),Windows_NT)
	if not exist $(PREF_TMP) mkdir $(PREF_TMP)
	xcopy /Y /Q $(PREF_SRC) $(PREF_TMP)
	xcopy /Y /Q ..\global.h $(PREF_TMP)
else
	mkdir -p $(PREF_TMP)
	cp ../global.h $(PREF_SRC)/* $(PREF_TMP)
endif

$(PREF_OBJ)/%.o: $(PREF_TMP)/%.c
ifeq ($(OS),Windows_NT)
	if not exist $(PREF_OBJ) mkdir $(PREF_OBJ)
else
	mkdir -p $(PREF_OBJ)
endif
	$(COMPILER) -c $< -o $@ -I$(PREF_TMP)

clean:
ifeq ($(OS),Windows_NT)
	if exist $(PREF_TMP) rmdir /Q /S $(PREF_TMP)
	if exist $(PREF_OBJ) rmdir /Q /S $(PREF_OBJ)
	if exist $(TARGET) del /Q $(TARGET)
else
	rm -rf $(PREF_TMP) $(PREF_OBJ) $(TARGET)
endif