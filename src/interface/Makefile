COMPILER := x86_64-w64-mingw32-gcc
BUILD_DIR := .
BUILD_FILE := libinterface.a
SRC_DIR := src
SRC_GLOBAL := ../global.h
SRC_FILES := $(wildcard $(SRC_DIR)/*.c $(SRC_DIR_global)/*.c)
OBJ_DIR := obj
OBJ_FILES := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRC_FILES:.c=.o))
OBJ_TARGETS := $(subst \,/,$(OBJ_FILES))

ifeq ($(OS),Windows_NT)
BUILD_DIR := $(subst /,\,$(BUILD_DIR))
BUILD_FILE := $(subst /,\,$(BUILD_FILE))
SRC_DIR := $(subst /,\,$(SRC_DIR))
SRC_GLOBAL := $(subst /,\,$(SRC_GLOBAL))
SRC_FILES := $(subst /,\,$(SRC_FILES))
OBJ_DIR := $(subst /,\,$(OBJ_DIR))
OBJ_FILES := $(subst /,\,$(OBJ_FILES))
else
BUILD_DIR := $(subst \,/,$(BUILD_DIR))
BUILD_FILE := $(subst \,/,$(BUILD_FILE))
SRC_DIR := $(subst \,/,$(SRC_DIR))
SRC_GLOBAL := $(subst \,/,$(SRC_GLOBAL))
SRC_FILES := $(subst \,/,$(SRC_FILES))
OBJ_DIR := $(subst \,/,$(OBJ_DIR))
OBJ_FILES := $(subst \,/,$(OBJ_FILES))
endif

main: copy $(OBJ_TARGETS)
ifeq ($(OS),Windows_NT)
	@echo Archiving object files to a library ($(foreach file,$(OBJ_FILES),"$(file)") --^> "$(BUILD_DIR)\$(BUILD_FILE)")...
	@ar rcs "$(BUILD_DIR)\$(BUILD_FILE)" $(foreach file,$(OBJ_FILES),"$(file)")
else
	@echo Archiving object files to a library ($(foreach file,$(OBJ_FILES),"$(file)") --^> "$(BUILD_DIR)/$(BUILD_FILE)")...
	@ar rcs "$(BUILD_DIR)/$(BUILD_FILE)" $(foreach file,$(OBJ_FILES),"$(file)")
endif
	@echo Done!

copy:
ifeq ($(OS),Windows_NT)
	@echo Copying source file ("$(SRC_GLOBAL)" --^> "$(SRC_DIR)\$(notdir $(SRC_GLOBAL))")...
	@xcopy /Y /Q "$(SRC_GLOBAL)" "$(SRC_DIR)" >NUL 2>NUL
else
	@echo Copying source file ("$(SRC_GLOBAL)" --^> "$(SRC_DIR)/$(notdir $(SRC_GLOBAL))")...
	cp "$(SRC_GLOBAL)" "$(SRC_DIR)"
endif
	@echo Done!

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
ifeq ($(OS),Windows_NT)
	@echo Compiling source file ("$(subst /,\,$<)" --^> "$(subst /,\,$@)")...
	@if not exist "$(subst /,\,$(dir $@))" @echo     Creating a directory for the object file ("$(subst /,\,$(dir $@))") && @mkdir "$(subst /,\,$(dir $@))" && @echo     Done!
	@$(COMPILER) -c "$(subst /,\,$<)" -o "$(subst /,\,$@)"
else
	@echo Compiling source file ("$(subst \,/,$<)" --^> "$(subst \,/,$@)")...
	@if not exist "$(subst \,/,$(dir $@))" @echo     Creating a directory for the object file ("$(subst \,/,$(dir $@))") && @mkdir -p "$(subst \,/,$(dir $@))" && @echo     Done!
	@$(COMPILER) -c "$(subst \,/,$<)" -o "$(subst \,/,$@)"
endif
	@echo Done!

clean:
ifeq ($(OS),Windows_NT)
	if exist "$(OBJ_DIR)" rmdir /Q /S "$(OBJ_DIR)"
	if exist "$(BUILD_FILE)" del /Q "$(BUILD_FILE)"
	if exist "$(SRC_DIR)\$(notdir $(SRC_GLOBAL))" del /Q "$(SRC_DIR)\$(notdir $(SRC_GLOBAL))"
else
	rm -rf "$(OBJ_DIR)" "$(BUILD_FILE)" "$(SRC_DIR)/$(notdir $(SRC_GLOBAL))"
endif

debug:
	@echo [DEBUG INFORMATION]
	@echo "Compiler (COMPILER): $(COMPILER)"
	@echo "Build directory (BUILD_DIR): $(BUILD_DIR)"
	@echo "Build file (BUILD_FILE): $(BUILD_FILE)"
	@echo "Source files directory (SRC_DIR): $(SRC_DIR)"
	@echo "Source global file (SRC_GLOBAL): $(SRC_GLOBAL)"
	@echo "Source files (SRC_FILES): $(SRC_FILES)"
	@echo "Object files directory (OBJ_DIR): $(OBJ_DIR)"
	@echo "Object files (OBJ_FILES): $(OBJ_FILES)"