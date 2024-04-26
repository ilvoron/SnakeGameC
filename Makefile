COMPILER = x86_64-w64-mingw32-gcc
TESTS_MAKEFILE_DIR = tests
SRC_MAIN = src/main.c
EXE_FILE = snake.exe
OBJ_DIR = obj
MODULES = board controller interface snake

main: test_modules $(MODULES)
	$(COMPILER) "$(SRC_MAIN)" -o "$(EXE_FILE)" -L "$(OBJ_DIR)"

test_modules:
	$(MAKE) -C "$(TESTS_MAKEFILE_DIR)" COMPILER=$(COMPILER) OS="$(OS)" || exit \b

$(MODULES):
	if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	$(MAKE) -C "src/$@" COMPILER="$(COMPILER)" OS="$(OS)" BUILD_DIR="$(abspath $(OBJ_DIR))"

clean:
	$(MAKE) clean -C "$(TESTS_MAKEFILE_DIR)" COMPILER=$(COMPILER) OS="$(OS)"
	if exist "$(OBJ_DIR)" rmdir /Q /S "$(OBJ_DIR)"

debug:
	@echo "Compiler: $(COMPILER)"
	@echo "Tests makefile directory: $(TESTS_MAKEFILE)"
	@echo "Source main file: $(SRC_MAIN)"
	@echo "Executable file: $(EXE_FILE)"
	@echo "Object files directory: $(OBJ_DIR)"
	@echo "Modules: $(MODULES)"