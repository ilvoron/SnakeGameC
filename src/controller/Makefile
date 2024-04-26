COMPILER = x86_64-w64-mingw32-gcc
BUILD_DIR = .
BUILD_FILE_LIB = libcontroller.a
SRC_DIR = src
OBJ_DIR = obj
TMP_DIR = temp
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%, $(OBJ_DIR)/%, $(SRC_FILES:.c=.o))

main: copy $(OBJ_FILES)
	if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	ar rcs "$(BUILD_DIR)\$(BUILD_FILE_LIB)" $(foreach file,$(OBJ_FILES),"$(file)")

copy:
	if not exist "$(TMP_DIR)" mkdir "$(TMP_DIR)"
	xcopy /Y /Q "$(SRC_DIR)" "$(TMP_DIR)"
	xcopy /Y /Q ..\global.h "$(TMP_DIR)"

$(OBJ_DIR)/%.o: $(TMP_DIR)/%.c
	if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	$(COMPILER) -c "$<" -o "$@" -I "$(TMP_DIR)" -I tests\src

clean:
	if exist "$(TMP_DIR)" rmdir /Q /S "$(TMP_DIR)"
	if exist "$(OBJ_DIR)" rmdir /Q /S "$(OBJ_DIR)"
	if exist "$(BUILD_FILE_LIB)" del /Q "$(BUILD_FILE_LIB)"
