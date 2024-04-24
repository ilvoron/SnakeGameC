COMPILER = x86_64-w64-mingw32-gcc
SRC_MAIN = ../src/main.c
SRC_GLOBAL = ../src/global.h
OBJ_DIR = obj
EXE_DIR = exe
TMP_DIR = temp
MODULES = board controller interface snake
MODULES_MAKEFILES_DIRS = $(foreach lib,$(MODULES),../src/$(lib))
MODULES_LIBS = $(foreach lib,$(MODULES),../src/$(lib)/lib$(lib).a)
MODULES_LIBS_CURRENT = $(foreach lib,$(MODULES),$(OBJ_DIR)/lib$(lib).a)
TESTS_MAKEFILES_DIRS = $(foreach lib,$(MODULES),../src/$(lib)/tests)
TESTS_LIBS = $(foreach lib,$(MODULES),../src/$(lib)/tests/lib$(lib)_test.a)
TESTS_LIBS_CURRENT = $(foreach lib,$(MODULES),$(OBJ_DIR)/lib$(lib)_test.a)

main: modules tests copy exe
ifeq ($(OS),Windows_NT)
	$(foreach lib,$(MODULES), cmd /c "$(subst /,\,$(EXE_DIR)\$(lib)_test.exe)" || exit /b $$? & )
else
	$(foreach lib,$(MODULES), "$(subst \,/,$(EXE_DIR)\$(lib)_test.exe)" || exit $$? & )
endif

modules:
ifeq ($(OS),Windows_NT)
	$(foreach module,$(MODULES_MAKEFILES_DIRS),$(MAKE) -C "$(subst /,\,$(module))" &)
else
	$(foreach module,$(MODULES_MAKEFILES_DIRS),$(MAKE) -C "$(subst \,/,$(module))" &)
endif

tests:
ifeq ($(OS),Windows_NT)
	$(foreach test,$(TESTS_MAKEFILES_DIRS),$(MAKE) -C "$(subst /,\,$(test))" &)
else
	$(foreach test,$(TESTS_MAKEFILES_DIRS),$(MAKE) -C "$(subst \,/,$(test))" &)
endif

copy:
ifeq ($(OS),Windows_NT)
	if not exist "$(subst /,\,$(OBJ_DIR))\" mkdir "$(subst /,\,$(OBJ_DIR))"
	$(foreach lib,$(MODULES_LIBS),xcopy /Y /Q "$(subst /,\,$(lib))" "$(subst /,\,$(OBJ_DIR))" &)
	$(foreach lib,$(TESTS_LIBS),xcopy /Y /Q "$(subst /,\,$(lib))" "$(subst /,\,$(OBJ_DIR))" &)
else
	mkdir -p "$(subst \,/,$(OBJ_DIR))"
	cp $(foreach lib,$(MODULES_LIBS),"$(subst \,/,$(lib))") "$(OBJ_DIR)"
	cp $(foreach lib,$(TESTS_LIBS),"$(subst \,/,$(lib))") "$(OBJ_DIR)"
endif

exe:
ifeq ($(OS),Windows_NT)
	if not exist "$(subst /,\,$(EXE_DIR))\" mkdir "$(subst /,\,$(EXE_DIR))"
	$(foreach i,$(words $(MODULES)),$(COMPILER) "$(subst /,\,$(word $(i),$(TESTS_LIBS_CURRENT)))" "$(subst /,\,$(word $(i),$(MODULES_LIBS_CURRENT)))" -o "$(subst /,\,"$(EXE_DIR)\$(word $(i),$(MODULES))_test.exe))
else
	mkdir -p "$(subst \,/,$(EXE_DIR))"
	$(foreach i,$(words $(MODULES)),$(COMPILER) "$(subst \,/,$(word $(i),$(TESTS_LIBS_CURRENT)))" "$(subst \,/,$(word $(i),$(MODULES_LIBS_CURRENT)))" -o "$(subst \,/,"$(EXE_DIR)/$(word $(i),$(MODULES))_test.exe))
endif

clean:
ifeq ($(OS),Windows_NT)
	$(foreach module,$(MODULES_MAKEFILES_DIRS),$(MAKE) clean -C "$(subst /,\,$(module))" &)
	$(foreach test,$(TESTS_MAKEFILES_DIRS),$(MAKE) clean -C "$(subst /,\,$(test))" &)
	if exist "$(subst /,\,$(OBJ_DIR))" rmdir /Q /S "$(subst /,\,$(OBJ_DIR))"
	if exist "$(subst /,\,$(EXE_DIR))" rmdir /Q /S "$(subst /,\,$(EXE_DIR))"
	if exist "$(subst /,\,$(TMP_DIR))" rmdir /Q /S "$(subst /,\,$(TMP_DIR))"
else
	$(foreach module,$(MODULES_MAKEFILES_DIRS),$(MAKE) clean -C "$(subst \,/,$(module))" &)
	$(foreach test,$(TESTS_MAKEFILES_DIRS),$(MAKE) clean -C "$(subst \,/,$(test))" &)
	rm -rf "$(subst \,/,$(OBJ_DIR))" "$(subst \,/,$(EXE_DIR))" "$(subst \,/,$(TMP_DIR))"
endif

debug:
	@echo "Compiler: $(COMPILER)"
	@echo "Source main file: $(SRC_MAIN)"
	@echo "Source global file: $(SRC_GLOBAL)"
	@echo "Object files directory: $(OBJ_DIR)"
	@echo "Executable files directory: $(EXE_DIR)"
	@echo "Modules: $(MODULES)"
	@echo "Modules makefiles directories: $(MODULES_MAKEFILES_DIRS)"
	@echo "Modules libs: $(MODULES_LIBS)"
	@echo "Modules libs for overall test: $(MODULES_LIBS_CURRENT)"
	@echo "Tests makefiles directories: $(TESTS_MAKEFILES_DIRS)"
	@echo "Tests libs: $(TESTS_LIBS)"
	@echo "Tests libs for overall test: $(TESTS_LIBS_CURRENT)"