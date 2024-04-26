COMPILER = x86_64-w64-mingw32-gcc
BUILD_DIR = .
BUILD_FILE_LIB = libinterface.a
SRC_DIR = src
SRC_GLOBAL = ..\global.h
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_DIR = obj
OBJ_FILES = $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRC_FILES:.c=.o))
TMP_DIR = temp

main: copy $(OBJ_FILES)
	if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	ar rcs "$(BUILD_DIR)\$(BUILD_FILE_LIB)" $(foreach file,$(OBJ_FILES),"$(file)")

copy:
	if not exist "$(TMP_DIR)" mkdir "$(TMP_DIR)"
	xcopy /Y /Q "$(SRC_GLOBAL)" "$(TMP_DIR)" >nul 2>&1

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	if not exist "$(dir $@)" @mkdir "$(dir $@)"
	$(COMPILER) -c "$<" -o "$@" -I "$(TMP_DIR)"

clean:
	if exist "$(OBJ_DIR)" rmdir /Q /S "$(OBJ_DIR)"
	if exist "$(TMP_DIR)" rmdir /Q /S "$(TMP_DIR)"
	if exist "$(BUILD_FILE_LIB)" del /Q "$(BUILD_FILE_LIB)"

debug:
	@echo [DEBUG INFORMATION]
	@echo "Compiler (COMPILER): $(COMPILER)"
	@echo "Build directory (BUILD_DIR): $(BUILD_DIR)"
	@echo "Build file (BUILD_FILE_LIB): $(BUILD_FILE_LIB)"
	@echo "Source files directory (SRC_DIR): $(SRC_DIR)"
	@echo "Source global file (SRC_GLOBAL): $(SRC_GLOBAL)"
	@echo "Source files (SRC_FILES): $(SRC_FILES)"
	@echo "Object files directory (OBJ_DIR): $(OBJ_DIR)"
	@echo "Object files (OBJ_FILES): $(OBJ_FILES)"