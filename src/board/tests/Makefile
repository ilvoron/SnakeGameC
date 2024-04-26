COMPILER = x86_64-w64-mingw32-gcc
BUILD_DIR = .
BUILD_FILE_LIB = libboard_test.a
BUILD_FILE_EXE = libboard_test.exe
SRC_DIR = src
OBJ_DIR = obj
TMP_DIR = temp
SRC_FILES = $(wildcard $(SRC_DIR)/*.c) $(SRC_DIR)/board.c
OBJ_FILES = $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRC_FILES:.c=.o))

main: copy $(OBJ_FILES)
	if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	ar rcs "$(BUILD_DIR)\$(BUILD_FILE_LIB)" $(foreach file,$(OBJ_FILES),"$(file)")

exe: copy $(OBJ_FILES)
	if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	ar rcs "$(BUILD_DIR)\$(BUILD_FILE_LIB)" $(foreach file,$(OBJ_FILES),"$(file)")
	$(COMPILER) "$(BUILD_DIR)\$(BUILD_FILE_LIB)" -o "$(BUILD_DIR)\$(BUILD_FILE_EXE)"

copy:
	if not exist "$(TMP_DIR)" mkdir "$(TMP_DIR)"
	xcopy /Y /Q "$(SRC_DIR)" "$(TMP_DIR)"
	xcopy /Y /Q ..\src\board.c "$(TMP_DIR)"
	xcopy /Y /Q ..\src\board.h "$(TMP_DIR)"
	xcopy /Y /Q ..\..\global.h "$(TMP_DIR)"

$(OBJ_DIR)/%.o: $(TMP_DIR)/%.c
	if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	$(COMPILER) -c "$<" -o "$@" -I "$(TMP_DIR)"

clean:
	if exist "$(TMP_DIR)" rmdir /Q /S "$(TMP_DIR)"
	if exist "$(OBJ_DIR)" rmdir /Q /S "$(OBJ_DIR)"
	if exist "$(BUILD_FILE_LIB)" del /Q "$(BUILD_FILE_LIB)"
	if exist "$(BUILD_FILE_EXE)" del /Q "$(BUILD_FILE_EXE)"