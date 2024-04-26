COMPILER = x86_64-w64-mingw32-gcc
BUILD_DIR = .
BUILD_FILE_LIB = libinterface_test.a
BUILD_FILE_EXE = libinterface_test.exe
SRC_DIR = src
SRC_DIR_CORE = $(SRC_DIR)/core
SRC_DIR_MIMIC = $(SRC_DIR)/mimic
SRC_FILES_IMPORTED = ..\libinterface.a ..\src\interface.h ..\..\global.h
SRC_FILES = $(wildcard $(SRC_DIR_CORE)/*.c $(SRC_DIR_MIMIC)/*.c)
OBJ_DIR = obj
OBJ_FILES = $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRC_FILES:.c=.o))
TMP_DIR = temp
INTERFACE_MAKEFILE_DIR = ..

main: interface copy $(OBJ_FILES)
	if not exist "$(BUILD_DIR)" mkdir $(BUILD_DIR)"
	ar rcs "$(BUILD_DIR)\$(BUILD_FILE_LIB)" $(foreach file,$(OBJ_FILES),"$(file)") $(foreach file,$(SRC_FILES_IMPORTED),"$(TMP_DIR)\$(notdir $(file))")

exe: interface copy $(OBJ_FILES)
	if not exist "$(BUILD_DIR)" mkdir $(BUILD_DIR)"
	ar rcs "$(BUILD_DIR)\$(BUILD_FILE_LIB)" $(foreach file,$(OBJ_FILES),"$(file)") $(foreach file,$(SRC_FILES_IMPORTED),"$(TMP_DIR)\$(notdir $(file))")
	$(COMPILER) "$(BUILD_DIR)\$(BUILD_FILE_LIB)" -o "$(BUILD_DIR)\$(BUILD_FILE_EXE)" $(foreach file,$(SRC_FILES_IMPORTED),"$(TMP_DIR)\$(notdir $(file))")

interface:
	$(MAKE) -C "$(INTERFACE_MAKEFILE_DIR)" COMPILER="$(COMPILER)" OS="$(OS)" BUILD_DIR="$(abspath $(TMP_DIR))"

copy:
	if not exist "$(TMP_DIR)" mkdir "$(TMP_DIR)"
	$(foreach file,$(SRC_FILES_IMPORTED),xcopy /Y /Q "$(file)" "$(TMP_DIR)" >nul 2>&1 &)

$(OBJ_DIR)/%.o: $(SRC_DIR)\%.c
	if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(COMPILER) -c "$<" -o "$@" -I "$(SRC_DIR)" -I "$(TMP_DIR)" -I "$(SRC_DIR_CORE)" -I "$(SRC_DIR_MIMIC)"

clean:
	if exist "$(OBJ_DIR)" rmdir /Q /S "$(OBJ_DIR)"
	if exist "$(TMP_DIR)" rmdir /Q /S "$(TMP_DIR)"
	if exist "$(BUILD_FILE_LIB)" del /Q "$(BUILD_FILE_LIB)"
	if exist "$(BUILD_FILE_EXE)" del /Q "$(BUILD_FILE_EXE)"

debug:
	@echo [DEBUG INFORMATION]
	@echo "Compiler (COMPILER): $(COMPILER)"
	@echo "Build directory (BUILD_FILE): $(BUILD_FILE)"
	@echo "Build library file (BUILD_FILE_LIB): $(BUILD_FILE_LIB)"
	@echo "Build executable file (BUILD_FILE_EXE): $(BUILD_FILE_EXE)"
	@echo "Source files directory (SRC_DIR): $(SRC_DIR)"
	@echo "Source core files directory (SRC_DIR_CORE): $(SRC_DIR_CORE)"
	@echo "Source mimic files directory (SRC_DIR_MIMIC): $(SRC_DIR_MIMIC)"
	@echo "Source imported files (SRC_FILES_IMPORTED): $(SRC_FILES_IMPORTED)"
	@echo "Source files (SRC_FILES): $(SRC_FILES)"
	@echo "Object files directory (OBJ_DIR): $(OBJ_DIR)"
	@echo "Object files (OBJ_FILES): $(OBJ_FILES)"
	@echo "Temporary files directory (TMP_DIR): $(TMP_DIR)"
	@echo "Interface module makefile directory (INTERFACE_MAKEFILE_DIR): $(INTERFACE_MAKEFILE_DIR)"