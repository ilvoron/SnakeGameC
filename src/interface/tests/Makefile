COMPILER = x86_64-w64-mingw32-gcc
BUILD_DIR = .
BUILD_FILE_LIB = libinterface_test.a
BUILD_FILE_EXE = interface_test.exe
SRC_DIR = src
SRC_DIR_CORE = $(SRC_DIR)/core
SRC_DIR_MIMIC = $(SRC_DIR)/mimic
SRC_DIR_IMPORTED = $(SRC_DIR)/imported
SRC_FILES_IMPORTED = ../libinterface.a ../src/interface.h ../../global.h
SRC_FILES = $(wildcard $(SRC_DIR_IMPORTED)/*.c $(SRC_DIR_CORE)/*.c $(SRC_DIR_MIMIC)/*.c)
OBJ_DIR = obj
OBJ_FILES = $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRC_FILES:.c=.o))
TMP_DIR = temp
INTERFACE_MAKEFILE_DIR = ..

main: copy $(OBJ_FILES)
ifeq ($(OS),Windows_NT)
	ar rcs "$(subst /,\,$(BUILD_DIR)\$(BUILD_FILE_LIB))" $(foreach file,$(OBJ_FILES),"$(subst /,\,$(file))") $(foreach file,$(SRC_FILES_IMPORTED),"$(subst /,\,$(SRC_DIR_IMPORTED)\$(notdir $(file)))")
else
	ar rcs "$(subst \,/,$(BUILD_DIR)/$(BUILD_FILE_LIB))" $(foreach file,$(OBJ_FILES),"$(subst \,/,$(file))") $(foreach file,$(SRC_FILES_IMPORTED),"$(subst \,/,$(SRC_DIR_IMPORTED)/$(notdir $(file)))")
endif

exe: copy $(OBJ_FILES)
ifeq ($(OS),Windows_NT)
	$(COMPILER) $(foreach file,$(OBJ_FILES),"$(subst /,\,$(file))") -o "$(subst /,\,$(BUILD_DIR)\$(BUILD_FILE_EXE))" $(foreach file,$(SRC_FILES_IMPORTED),"$(subst /,\,$(SRC_DIR_IMPORTED)\$(notdir $(file)))")
else
	$(COMPILER) $(foreach file,$(OBJ_FILES),"$(subst \,/,$(file))") -o "$(subst \,/,$(BUILD_DIR)/$(BUILD_FILE_EXE))" $(foreach file,$(SRC_FILES_IMPORTED),"$(subst \,/,$(SRC_DIR_IMPORTED)/$(notdir $(file)))")
endif

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
ifeq ($(OS),Windows_NT)
	if not exist "$(subst /,\,$(dir $@))" mkdir "$(subst /,\,$(dir $@))"
	$(COMPILER) -c "$(subst /,\,$<)" -o "$(subst /,\,$@)" -I "$(subst /,\,$(SRC_DIR))" -I "$(subst /,\,$(SRC_DIR_IMPORTED))" -I "$(subst /,\,$(SRC_DIR_CORE))" -I "$(subst /,\,$(SRC_DIR_MIMIC))"
else
	mkdir -p "$(subst \,/,$(dir $@))"
	$(COMPILER) -c "$(subst \,/,$<)" -o "$(subst \,/,$@)" -I "$(subst \,/,$(SRC_DIR))" -I "$(subst \,/,$(SRC_DIR_IMPORTED))" -I "$(subst \,/,$(SRC_DIR_CORE))" -I "$(subst \,/,$(SRC_DIR_MIMIC))"
endif

copy:
ifeq ($(OS),Windows_NT)
	if not exist "$(subst /,\,$(SRC_DIR_IMPORTED))" mkdir "$(subst /,\,$(SRC_DIR_IMPORTED))"
	$(foreach file,$(SRC_FILES_IMPORTED),xcopy /Y /Q "$(subst /,\,$(file))" "$(subst /,\,$(SRC_DIR_IMPORTED))" &)
else
	mkdir -p "$(subst \,/,$(SRC_DIR_IMPORTED))"
	cp $(foreach file,$(SRC_FILES_IMPORTED),"$(subst \,/,$(file))") "$(subst \,/,$(SRC_DIR_IMPORTED))"
endif

clean:
ifeq ($(OS),Windows_NT)
	if exist "$(subst /,\,$(SRC_DIR_IMPORTED))" rmdir /Q /S "$(subst /,\,$(SRC_DIR_IMPORTED))"
	if exist "$(subst /,\,$(OBJ_DIR))" rmdir /Q /S "$(subst /,\,$(OBJ_DIR))"
	if exist "$(subst /,\,$(TMP_DIR))" rmdir /Q /S "$(subst /,\,$(TMP_DIR))"
	if exist "$(subst /,\,$(BUILD_FILE_LIB))" del /Q "$(subst /,\,$(BUILD_FILE_LIB))"
	if exist "$(subst /,\,$(BUILD_FILE_EXE))" del /Q "$(subst /,\,$(BUILD_FILE_EXE))"
else
	rm -rf "$(subst \,/,$(SRC_DIR_IMPORTED))" "$(subst \,/,$(OBJ_DIR))" "$(subst \,/,$(TMP_DIR))" "$(subst \,/,$(BUILD_FILE_LIB))" "$(subst \,/,$(BUILD_FILE_EXE))"
endif

interface:
ifeq ($(OS),Windows_NT)
	$(MAKE) -C "$(subst /,\,$(INTERFACE_MAKEFILE_DIR))"
else
	$(MAKE) -C "$(subst \,/,$(INTERFACE_MAKEFILE_DIR))"
endif

debug:
	@echo "Compiler: $(COMPILER)"
	@echo "Build directory: $(BUILD_FILE)"
	@echo "Build library file: $(BUILD_FILE_LIB)"
	@echo "Build executable file: $(BUILD_FILE_EXE)"
	@echo "Source files directory: $(SRC_DIR)"
	@echo "Source core files directory: $(SRC_DIR_CORE)"
	@echo "Source mimic files directory: $(SRC_DIR_MIMIC)"
	@echo "Source imported files directory: $(SRC_DIR_IMPORTED)"
	@echo "Source imported files: $(SRC_FILES_IMPORTED)"
	@echo "Source files: $(SRC_FILES)"
	@echo "Object files directory: $(OBJ_DIR)"
	@echo "Object files: $(OBJ_FILES)"
	@echo "Temporary files directory: $(TMP_DIR)"
	@echo "Interface module makefile directory: $(INTERFACE_MAKEFILE_DIR)"