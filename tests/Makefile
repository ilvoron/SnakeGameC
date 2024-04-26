COMPILER = x86_64-w64-mingw32-gcc
BIN_DIR = bin
CLEAN_DIR = temp
CLEAN_FILES = *.txt
MODULES = controller interface board snake

main: $(MODULES)

$(MODULES):
	if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)"
	$(MAKE) exe -C "../src/$@/tests" COMPILER="$(COMPILER)" OS="$(OS)" BUILD_DIR="$(abspath $(BIN_DIR))" BUILD_FILE_EXE="lib$@_test.exe"
	"$(BIN_DIR)\lib$@_test.exe" || @echo. & @echo TEST WAS FAILED... EXITING... & exit \b

clean:
	$(foreach module,$(MODULES),$(MAKE) clean -C "../src/$(module)/tests" COMPILER="$(COMPILER)" OS="$(OS)"&)
	$(foreach module,$(MODULES),$(MAKE) clean -C "../src/$(module)" COMPILER="$(COMPILER)" OS="$(OS)"&)
	if exist "$(BIN_DIR)" rmdir /Q /S "$(BIN_DIR)"
	$(foreach directory,$(CLEAN_DIR),if exist "$(directory)" rmdir /Q /S "$(directory)")
	$(foreach file,$(CLEAN_FILES),if exist "$(file)" del /Q "$(file)")

debug:
	@echo "Compiler: $(COMPILER)"
	@echo "Binary files directory: $(BIN_DIR)"
	@echo "Directories to clean up: $(CLEAN_DIR)"
	@echo "Files to clean up: $(CLEAN_FILES)"
	@echo "Modules: $(MODULES)"