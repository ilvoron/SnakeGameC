COMPILER = x86_64-w64-mingw32-gcc
TESTS_MAKEFILE_DIR = tests
SRC_MAIN = src/main.c
EXE_FILE = snake.exe
OBJ_DIR = obj
RESOURCES_FILE = src/snake.rc
VERSION_FILE = src/snake.version
MODULES = controller interface board snake

main: test_modules $(MODULES) resources
	$(COMPILER) "$(SRC_MAIN)" "$(OBJ_DIR)\snake.res" -o "$(EXE_FILE)" $(foreach module,$(MODULES),-I "src\$(module)\src") -I "src" -L "$(OBJ_DIR)" $(foreach module,$(MODULES),-l "$(module)")
	@echo --^> Executable project file is ready to use! Version: $(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH).$(VERSION_BUILD) (build $(VERSION_BUILD))

no-tests: $(MODULES) resources
	$(COMPILER) "$(SRC_MAIN)" "$(OBJ_DIR)\snake.res" -o "$(EXE_FILE)" $(foreach module,$(MODULES),-I "src\$(module)\src") -I "src" -L "$(OBJ_DIR)" $(foreach module,$(MODULES),-l "$(module)")
	@echo --^> Executable project file is ready to use! Version: $(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH).$(VERSION_BUILD) (build $(VERSION_BUILD))

test_modules:
	$(MAKE) -C "$(TESTS_MAKEFILE_DIR)" COMPILER=$(COMPILER) OS="$(OS)" || exit \b

$(MODULES):
	if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	$(MAKE) -C "src/$@" COMPILER="$(COMPILER)" OS="$(OS)" VERSION_BUILD_DIR="$(abspath $(OBJ_DIR))" VERSION_BUILD_FILE_LIB="lib$@.a"

resources:
	if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	if not exist "$(VERSION_FILE)" echo NO VERSION FILE! & exit -1
	if not exist "$(RESOURCES_FILE)" echo NO RESOURCES FILE! & exit -1
	$(eval VERSION_FULL=$(shell cat $(VERSION_FILE)))
	$(eval VERSION_MAJOR=$(shell cut -d . -f 1 $(VERSION_FILE)))
	$(eval VERSION_MINOR=$(shell cut -d . -f 2 $(VERSION_FILE)))
	$(eval VERSION_PATCH=$(shell cut -d . -f 3 $(VERSION_FILE)))
	$(eval VERSION_BUILD=$(shell cut -d . -f 4 $(VERSION_FILE)))
	$(eval VERSION_BUILD=$$(shell expr $(VERSION_BUILD) + 1))
	@echo $(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH).$(VERSION_BUILD) > "$(VERSION_FILE)"
	@echo #define VERSION_FULL "$(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH).$(VERSION_BUILD)" > "$(OBJ_DIR)\version.rc"
	@echo #define VERSION_MAJOR $(VERSION_MAJOR) >> "$(OBJ_DIR)\version.rc"
	@echo #define VERSION_MINOR $(VERSION_MINOR) >> "$(OBJ_DIR)\version.rc"
	@echo #define VERSION_PATCH $(VERSION_PATCH) >> "$(OBJ_DIR)\version.rc"
	@echo #define VERSION_BUILD $(VERSION_BUILD) >> "$(OBJ_DIR)\version.rc"
	windres "$(RESOURCES_FILE)" -O coff -o "$(OBJ_DIR)\snake.res" -I $(OBJ_DIR)

clean:
	$(MAKE) clean -C "$(TESTS_MAKEFILE_DIR)" COMPILER=$(COMPILER) OS="$(OS)"
	if exist "$(OBJ_DIR)" rmdir /Q /S "$(OBJ_DIR)"

debug:
	@echo "Compiler (COMPILER): $(COMPILER)"
	@echo "Tests makefile directory (TESTS_MAKEFILE): $(TESTS_MAKEFILE)"
	@echo "Source main file (SRC_MAIN): $(SRC_MAIN)"
	@echo "Executable file (EXE_FILE): $(EXE_FILE)"
	@echo "Object files directory (OBJ_DIR): $(OBJ_DIR)"
	@echo "Resources file (RESOURCES_FILE): $(RESOURCES_FILE)"
	@echo "Version file (VERSION_FILE): $(VERSION_FILE)"
	@echo "Modules (MODULES): $(MODULES)"