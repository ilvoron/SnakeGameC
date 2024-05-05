COMPILER = x86_64-w64-mingw32-gcc
BIN_DIR = bin
CLEAN_DIRS = temp
CLEAN_FILES = *.txt
MODULES = controller interface board snake

main: $(MODULES)
	@echo --^> All tests have been successfully completed

$(MODULES):
	@if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)"
	@echo --^> Making an executable file to test module "$@"...
	@$(MAKE) -s exe -C "../src/$@/tests" COMPILER="$(COMPILER)" OS="$(OS)" BUILD_DIR="$(abspath $(BIN_DIR))" BUILD_FILE_EXE="lib$@_test.exe"
	@echo --^> Testing module "$@"...
	@"$(BIN_DIR)\lib$@_test.exe" || @echo --^> Test was failed... Exiting... & exit \b
	@echo --^> Testing module "$@"... Success!

clean:
	$(foreach module,$(MODULES),$(MAKE) clean -C "../src/$(module)/tests" COMPILER="$(COMPILER)" OS="$(OS)"&)
	$(foreach module,$(MODULES),$(MAKE) clean -C "../src/$(module)" COMPILER="$(COMPILER)" OS="$(OS)"&)
	if exist "$(BIN_DIR)" rmdir /Q /S "$(BIN_DIR)"
	$(foreach directory,$(CLEAN_DIRS),if exist "$(directory)" rmdir /Q /S "$(directory)")
	$(foreach file,$(CLEAN_FILES),if exist "$(file)" del /Q "$(file)")

debug:
	@echo "Compiler (COMPILER): $(COMPILER)"
	@echo "Binary files directory (BIN_DIR): $(BIN_DIR)"
	@echo "Directories to clean up (CLEAN_DIRS): $(CLEAN_DIRS)"
	@echo "Files to clean up (CLEAN_FILES): $(CLEAN_FILES)"
	@echo "Modules (MODULES): $(MODULES)"