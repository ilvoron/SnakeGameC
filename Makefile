COMPILER = x86_64-w64-mingw32-gcc
TESTS_MAKEFILE_DIR = tests
SRC_MAIN = src/main.c
EXE_FILE = snake.exe
OBJ_DIR = obj
RESOURCES_FILE = src/snake.rc
MODULES = controller interface board snake

main: test_modules $(MODULES) resources
	$(COMPILER) "$(SRC_MAIN)" "$(OBJ_DIR)\snake.res" -o "$(EXE_FILE)" $(foreach module,$(MODULES),-I "src\$(module)\src") -I "src" -L "$(OBJ_DIR)" $(foreach module,$(MODULES),-l "$(module)")
	@echo --^> Executable project file is ready to use!

no_tests: $(MODULES) resources
	$(COMPILER) "$(SRC_MAIN)" "$(OBJ_DIR)\snake.res" -o "$(EXE_FILE)" $(foreach module,$(MODULES),-I "src\$(module)\src") -I "src" -L "$(OBJ_DIR)" $(foreach module,$(MODULES),-l "$(module)")
	@echo --^> Executable project file is ready to use!

test_modules:
	$(MAKE) -C "$(TESTS_MAKEFILE_DIR)" COMPILER=$(COMPILER) OS="$(OS)" || exit \b

$(MODULES):
	if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	$(MAKE) -C "src/$@" COMPILER="$(COMPILER)" OS="$(OS)" BUILD_DIR="$(abspath $(OBJ_DIR))" BUILD_FILE_LIB="lib$@.a"

resources:
	if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	windres "$(RESOURCES_FILE)" -O coff -o "$(OBJ_DIR)\snake.res"

clean:
	$(MAKE) clean -C "$(TESTS_MAKEFILE_DIR)" COMPILER=$(COMPILER) OS="$(OS)"
	if exist "$(OBJ_DIR)" rmdir /Q /S "$(OBJ_DIR)"

debug:
	@echo "Compiler (COMPILER): $(COMPILER)"
	@echo "Tests makefile directory (TESTS_MAKEFILE): $(TESTS_MAKEFILE)"
	@echo "Source main file (SRC_MAIN): $(SRC_MAIN)"
	@echo "Executable file (EXE_FILE): $(EXE_FILE)"
	@echo "Object files directory (OBJ_DIR): $(OBJ_DIR)"
	@echo "Modules (MODULES): $(MODULES)"