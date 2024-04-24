GCC = x86_64-w64-mingw32-gcc
SRCd = src
SRCd_imp = $(SRCd)/imported
SRCd_core = $(SRCd)/core
SRCd_mimic = $(SRCd)/mimic
OBJd = obj
TMPd = tmp
OUTf = libinterface_ut.a
EXEf = interface_ut.exe
CPYfs = ../libinterface.a ../src/interface.h ../../global.h
MAKEd = ..
SRCfs = $(wildcard $(SRCd_imp)/*.c $(SRCd_core)/*.c $(SRCd_mimic)/*.c)
OBJfs = $(patsubst $(SRCd)/%,$(OBJd)/%,$(SRCfs:.c=.o))

main: copy $(OBJfs)
ifeq ($(OS),Windows_NT)
	ar rcs "$(subst /,\,$(OUTf))" $(foreach file,$(OBJfs),"$(subst /,\,$(file))") $(foreach file,$(CPYfs),"$(subst /,\,$(SRCd_imp)/$(notdir $(file)))")
else
	ar rcs "$(OUTf)" $(foreach file,$(OBJfs),"$(file)") $(foreach file,$(CPYfs),"$(SRCd_imp)/$(notdir $(file))")
endif

exe: copy $(OBJfs)
ifeq ($(OS),Windows_NT)
	$(GCC) $(foreach file,$(OBJfs),"$(subst /,\,$(file))") -o "$(subst /,\,$(EXEf))" $(foreach file,$(CPYfs),"$(subst /,\,$(SRCd_imp)\$(notdir $(file)))")
else
	$(GCC) $(foreach file,$(OBJfs),"$(file)") -o "$(EXEf)" $(foreach file,$(CPYfs),"$(SRCd_imp)/$(notdir $(file))")
endif

$(OBJd)/%.o: $(SRCd)/%.c
ifeq ($(OS),Windows_NT)
	if not exist "$(subst /,\,$(dir $@))" mkdir "$(subst /,\,$(dir $@))"
	$(GCC) -c "$(subst /,\,$<)" -o "$(subst /,\,$@)" -I "$(subst /,\,$(SRCd))" -I "$(subst /,\,$(SRCd_imp))" -I "$(subst /,\,$(SRCd_core))" -I "$(subst /,\,$(SRCd_mimic))"
else
	mkdir -p "$(dir $@)"
	$(GCC) -c "$<" -o "$@" -I "$(SRCd)" -I "$(SRCd_imp)" -I "$(SRCd_core)" -I "$(SRCd_mimic)"
endif

copy:
ifeq ($(OS),Windows_NT)
	if not exist "$(subst /,\,$(SRCd_imp))\" mkdir "$(subst /,\,$(SRCd_imp))"
	$(foreach file,$(CPYfs),xcopy /Y /Q "$(subst /,\,$(file))" "$(subst /,\,$(SRCd_imp))" &)
else
	mkdir -p "$(SRCd_imp)"
	cp $(foreach file,$(CPYfs),"$(file)") "$(SRCd_imp)"
endif

clean:
ifeq ($(OS),Windows_NT)
	if exist "$(subst /,\,$(SRCd_imp))" rmdir /Q /S "$(subst /,\,$(SRCd_imp))"
	if exist "$(subst /,\,$(OBJd))" rmdir /Q /S "$(subst /,\,$(OBJd))"
	if exist "$(subst /,\,$(TMPd))" rmdir /Q /S "$(subst /,\,$(TMPd))"
	if exist "$(subst /,\,$(OUTf))" del /Q "$(subst /,\,$(OUTf))"
	if exist "$(subst /,\,$(EXEf))" del /Q "$(subst /,\,$(EXEf))"
else
	rm -rf "$(SRCd_imp)" "$(OBJd)" "$(TMPd)" "$(OUTf)" "$(EXEf)"
endif

interface:
ifeq ($(OS),Windows_NT)
	mingw32-make -C "$(subst /,\,$(MAKEd))"
else
	make -C "$(MAKEd)"
endif

debug:
	@echo "Source files: $(SRCfs)"
	@echo "Object files: $(OBJfs)"
	@echo "Copy files: $(CPYfs)"