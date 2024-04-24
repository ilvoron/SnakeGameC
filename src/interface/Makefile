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
	@if not exist "$(subst /,\,$(dir $@))" (\
		@echo     Creating a directory for the object file ^("$(subst /,\,$(dir $@))"^) &&\
		@mkdir "$(subst /,\,$(dir $@))" &&\
		@echo     Done!\
	)
	@$(COMPILER) -c "$(subst /,\,$<)" -o "$(subst /,\,$@)"
else
	@echo Compiling source file ("$(subst \,/,$<)" --^> "$(subst \,/,$@)")...
	@if not exist "$(subst \,/,$(dir $@))" (\
		@echo     Creating a directory for the object file ^("$(subst \,/,$(dir $@))"^) &&\
		@mkdir -p "$(subst \,/,$(dir $@))" &&\
		@echo     Done!\
	)
	@$(COMPILER) -c "$(subst \,/,$<)" -o "$(subst \,/,$@)"
endif
	@echo Done!



clean:
	@echo Cleaning up...
ifeq ($(OS),Windows_NT)
	@if exist "$(OBJ_DIR)" (\
		@echo     Deleting folder "$(OBJ_DIR)"... &&\
		@rmdir /Q /S "$(OBJ_DIR)" &&\
		@echo     Done!\
	)
	@if exist "$(BUILD_FILE)" (\
		@echo     Deleting file "$(BUILD_FILE)"... &&\
		@del /Q "$(BUILD_FILE)" &&\
		@echo     Done!\
	)
	@if exist "$(SRC_DIR)\$(notdir $(SRC_GLOBAL))" (\
		@echo     Deleting file "$(SRC_DIR)\$(notdir $(SRC_GLOBAL))"... &&\
		@del /Q "$(SRC_DIR)\$(notdir $(SRC_GLOBAL))" &&\
		@echo     Done!\
	)
else
	@if exist "$(OBJ_DIR)" (\
		@echo     Deleting folder "$(OBJ_DIR)"... &&\
		@rm -rf "$(OBJ_DIR)" &&\
		@echo     Done!\
	)
	@if exist "$(BUILD_FILE)" (\
		@echo     Deleting file "$(BUILD_FILE)"... &&\
		@rm -rf "$(BUILD_FILE)" &&\
		@echo     Done!\
	)
	@if exist "$(SRC_DIR)/$(notdir $(SRC_GLOBAL))" (\
		@echo     Deleting file "$(SRC_DIR)/$(notdir $(SRC_GLOBAL))"... &&\
		@rm -rf "$(SRC_DIR)/$(notdir $(SRC_GLOBAL))" &&\
		@echo     Done!\
	)
endif
	@echo Done!



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