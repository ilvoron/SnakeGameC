COMPILER = x86_64-w64-mingw32-gcc
TESTS_MAKEFILE = tests
SRC_MAIN = src/main.c
EXE_FILE = snake.exe
OBJ_DIR = obj
MODULES = board controller interface snake
MODULES_MAKEFILES_DIRS = $(foreach lib,$(MODULES),src/$(lib))
MODULES_LIBS = $(foreach lib,$(MODULES),src/$(lib)/lib$(lib).a)

main: tests_overall modules_overall copy
ifeq ($(OS),Windows_NT)
	$(COMPILER) "$(subst /,\,$(SRC_MAIN))" -o "$(subst /,\,$(EXE_FILE))" -L "$(subst /,\,$(OBJ_DIR))"
else
	$(COMPILER) "$(subst \,/,$(SRC_MAIN))" -o "$(subst \,/,$(EXE_FILE))" -L "$(subst \,/,$(OBJ_DIR))"
endif

tests_overall:
ifeq ($(OS),Windows_NT)
	cmd /c $(MAKE) -C "$(subst /,\,$(TESTS_MAKEFILE))" COMPILER=$(COMPILER) || exit \b
else
	$(MAKE) -C "$(subst \,/,$(TESTS_MAKEFILE))" COMPILER=$(COMPILER) || exit $$?
endif

modules_overall:
ifeq ($(OS),Windows_NT)
	$(foreach module,$(MODULES_MAKEFILES_DIRS),$(MAKE) -C "$(subst /,\,$(module))" COMPILER=$(COMPILER) &)
else
	$(foreach module,$(MODULES_MAKEFILES_DIRS),$(MAKE) -C "$(subst \,/,$(module))" COMPILER=$(COMPILER) &)
endif

copy:
ifeq ($(OS),Windows_NT)
	if not exist "$(subst /,\,$(OBJ_DIR))\" mkdir "$(subst /,\,$(OBJ_DIR))"
	$(foreach lib,$(MODULES_LIBS),xcopy /Y /Q "$(subst /,\,$(lib))" "$(subst /,\,$(OBJ_DIR))" &)
else
	mkdir -p "$(subst \,/,$(OBJ_DIR))"
	cp $(foreach lib,$(MODULES_LIBS),"$(subst \,/,$(lib))") "$(OBJ_DIR)"
endif

clean:
ifeq ($(OS),Windows_NT)
	$(MAKE) clean -C "$(subst /,\,$(TESTS_MAKEFILE))" COMPILER=$(COMPILER)
	if exist "$(subst /,\,$(OBJ_DIR))" rmdir /Q /S "$(subst /,\,$(OBJ_DIR))"
else
	$(MAKE) clean -C "$(subst \,/,$(TESTS_MAKEFILE))" COMPILER=$(COMPILER)
	rm -rf "$(subst \,/,$(OBJ_DIR))"
endif

debug:
	@echo "Compiler: $(COMPILER)"
	@echo "Tests makefile directory: $(TESTS_MAKEFILE)"
	@echo "Source main file: $(SRC_MAIN)"
	@echo "Executable file: $(EXE_FILE)"
	@echo "Object files directory: $(OBJ_DIR)"
	@echo "Modules: $(MODULES)"
	@echo "Modules makefiles directories: $(MODULES_MAKEFILES_DIRS)"
	@echo "Modules libs: $(MODULES_LIBS)"