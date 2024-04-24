COMPILER = x86_64-w64-mingw32-gcc
BUILD_DIR = .
BUILD_FILE = libinterface.a
SRC_DIR = src
SRC_GLOBAL = ../global.h
SRC_FILES = $(wildcard $(SRC_DIR)/*.c $(SRC_DIR_global)/*.c)
OBJ_DIR = obj
OBJ_FILES = $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRC_FILES:.c=.o))

main: copy $(OBJ_FILES)
ifeq ($(OS),Windows_NT)
	ar rcs "$(subst /,\,$(BUILD_DIR)\$(BUILD_FILE))" $(foreach file,$(OBJ_FILES),"$(subst /,\,$(file))")
else
	ar rcs "$(subst \,/,$(BUILD_DIR)/$(BUILD_FILE))" $(foreach file,$(OBJ_FILES),"$(subst \,/,$(file))")
endif

copy:
ifeq ($(OS),Windows_NT)
	xcopy /Y /Q "$(subst /,\,$(SRC_GLOBAL))" "$(subst /,\,$(SRC_DIR))"
else
	cp "$(subst \,/,$(SRC_GLOBAL))" "$(subst \,/,$(SRC_DIR))"
endif

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
ifeq ($(OS),Windows_NT)
	if not exist "$(subst /,\,$(dir $@))" mkdir "$(subst /,\,$(dir $@))"
	$(COMPILER) -c "$(subst /,\,$<)" -o "$(subst /,\,$@)"
else
	mkdir -p "$(subst \,/,$(dir $@))"
	$(COMPILER) -c "$(subst \,/,$<)" -o "$(subst \,/,$@)"
endif

clean:
ifeq ($(OS),Windows_NT)
	if exist "$(subst /,\,$(OBJ_DIR))" rmdir /Q /S "$(subst /,\,$(OBJ_DIR))"
	if exist "$(subst /,\,$(BUILD_FILE))" del /Q "$(subst /,\,$(BUILD_FILE))"
	if exist "$(subst /,\,$(SRC_DIR)\$(notdir $(SRC_GLOBAL)))" del /Q "$(subst /,\,$(SRC_DIR)\$(notdir $(SRC_GLOBAL)))"
else
	rm -rf "$(subst \,/,$(OBJ_DIR))" "$(subst \,/,$(BUILD_FILE))" "$(subst \,/,$(SRC_DIR)/$(notdir $(SRC_GLOBAL)))"
endif

debug:
	@echo "Compiler: $(COMPILER)"
	@echo "Build directory: $(BUILD_FILE)"
	@echo "Build file: $(BUILD_FILE)"
	@echo "Source files directory: $(SRC_DIR)"
	@echo "Source global file: $(SRC_GLOBAL)"
	@echo "Source files: $(SRC_FILES)"
	@echo "Object files directory: $(OBJ_DIR)"
	@echo "Object files: $(OBJ_FILES)"