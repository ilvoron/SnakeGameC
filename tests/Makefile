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

main:
ifeq ($(OS),Windows_NT)
	$(foreach module,$(MODULES),\
		$(MAKE) -C "..\src\$(module)\tests" COMPILER=$(COMPILER) OS=$(OS) &\
		if not exist "$(subst /,\,$(OBJ_DIR))\" mkdir "$(subst /,\,$(OBJ_DIR))" &\
		xcopy /Y /Q "..\src\$(module)\tests\lib$(module)_test.a" "$(subst /,\,$(OBJ_DIR))" &\
		if not exist "$(subst /,\,$(EXE_DIR))\" mkdir "$(subst /,\,$(EXE_DIR))" &\
		$(COMPILER) "$(OBJ_DIR)\lib$(module)_test.a" -o "$(subst /,\,$(EXE_DIR)\$(module)_test.exe)" &\
		"$(subst /,\,$(EXE_DIR)\$(module)_test.exe)" || @echo TEST WAS FAILED... EXITING... & exit \b &\
	)
else
	$(foreach module,$(MODULES),\
		$(MAKE) -C "../src/$(module)/tests" COMPILER=$(COMPILER) OS=$(OS) &\
		mkdir -p "$(subst \,/,$(OBJ_DIR))" &\
		cp "../src/$(module)/tests/lib$(module)_test.a" "$(subst \,/,$(OBJ_DIR))" &\
		mkdir -p "$(subst \,/,$(EXE_DIR))" &\
		$(COMPILER) "$(OBJ_DIR)/lib$(module)_test.a" -o "$(subst \,/,$(EXE_DIR)/$(module)_test.exe)" &\
		"$(subst \,/,$(EXE_DIR)/$(module)_test.exe)" || @echo TEST WAS FAILED... EXITING... & exit \b &\
	)
endif


#main: modules tests copy exec
#ifeq ($(OS),Windows_NT)
#	$(foreach lib,$(MODULES),"$(subst /,\,$(EXE_DIR)\$(lib)_test.exe)" || @echo TEST WAS FAILED... EXITING... & exit \b &\)
#else
#	$(foreach lib,$(MODULES),"$(subst \,/,$(EXE_DIR)\$(lib)_test.exe)" || @echo TEST WAS FAILED... EXITING... & exit $$? & )
#endif

modules:
ifeq ($(OS),Windows_NT)
	$(foreach module,$(MODULES_MAKEFILES_DIRS),$(MAKE) -C "$(subst /,\,$(module))" COMPILER=$(COMPILER) OS=$(OS)&)
else
	$(foreach module,$(MODULES_MAKEFILES_DIRS),$(MAKE) -C "$(subst \,/,$(module))" COMPILER=$(COMPILER) OS=$(OS)&)
endif

tests:
ifeq ($(OS),Windows_NT)
	$(foreach test,$(TESTS_MAKEFILES_DIRS),$(MAKE) -C "$(subst /,\,$(test))" COMPILER=$(COMPILER) OS=$(OS)&)
else
	$(foreach test,$(TESTS_MAKEFILES_DIRS),$(MAKE) -C "$(subst \,/,$(test))" COMPILER=$(COMPILER) OS=$(OS)&)
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

exec:
ifeq ($(OS),Windows_NT)
	if not exist "$(subst /,\,$(EXE_DIR))\" mkdir "$(subst /,\,$(EXE_DIR))"
	$(foreach module,$(MODULES),$(COMPILER) "$(subst /,\,$(OBJ_DIR)\lib$(module)_test.a)" "$(subst /,\,$(OBJ_DIR)\lib$(module).a)" -o "$(subst /,\,$(EXE_DIR)\$(module)_test.exe)" &)
else
	mkdir -p "$(subst \,/,$(EXE_DIR))"
	$(foreach module,$(MODULES),$(COMPILER) "$(subst \,/,$(OBJ_DIR)\lib$(module)_test.a)" "$(subst \,/,$(OBJ_DIR)/lib$(module).a)" -o "$(subst /,\,$(EXE_DIR)\$(module)_test.exe)" &)
endif

clean:
ifeq ($(OS),Windows_NT)
	$(foreach module,$(MODULES_MAKEFILES_DIRS),$(MAKE) clean -C "$(subst /,\,$(module))" COMPILER=$(COMPILER) OS=$(OS)&)
	$(foreach test,$(TESTS_MAKEFILES_DIRS),$(MAKE) clean -C "$(subst /,\,$(test))" COMPILER=$(COMPILER) OS=$(OS)&)
	$(foreach txtFile,$(wildcard ./*.txt),del /Q "$(subst /,\,$(txtFile))" &)
	if exist "$(subst /,\,$(OBJ_DIR))" rmdir /Q /S "$(subst /,\,$(OBJ_DIR))"
	if exist "$(subst /,\,$(EXE_DIR))" rmdir /Q /S "$(subst /,\,$(EXE_DIR))"
	if exist "$(subst /,\,$(TMP_DIR))" rmdir /Q /S "$(subst /,\,$(TMP_DIR))"
else
	$(foreach module,$(MODULES_MAKEFILES_DIRS),$(MAKE) clean -C "$(subst \,/,$(module))" COMPILER=$(COMPILER) OS=$(OS)&)
	$(foreach test,$(TESTS_MAKEFILES_DIRS),$(MAKE) clean -C "$(subst \,/,$(test))" COMPILER=$(COMPILER) OS=$(OS)&)
	rm -rf "$(subst \,/,$(OBJ_DIR))" "$(subst \,/,$(EXE_DIR))" "$(subst \,/,$(TMP_DIR))" "$(subst \,/,$(wildcard ./*.txt))"
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