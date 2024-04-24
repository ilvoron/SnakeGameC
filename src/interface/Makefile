GCC = x86_64-w64-mingw32-gcc
SRCd = src
SRCf_global = ../global.h
OBJd = obj
OUTf = libinterface.a
SRCfs = $(wildcard $(SRCd)/*.c $(SRCd_global)/*.c)
OBJfs = $(patsubst $(SRCd)/%,$(OBJd)/%,$(SRCfs:.c=.o))

main: copy $(OBJfs)
ifeq ($(OS),Windows_NT)
	ar rcs "$(subst /,\,$(OUTf))" $(foreach file,$(OBJfs),"$(subst /,\,$(file))")
else
	ar rcs "$(OUTf)" $(foreach file,$(OBJfs),"$(file)")
endif

copy:
ifeq ($(OS),Windows_NT)
	xcopy /Y /Q "$(subst /,\,$(SRCf_global))" "$(subst /,\,$(SRCd))"
else
	cp "$(SRCf_global)" "$(SRCd)"
endif

$(OBJd)/%.o: $(SRCd)/%.c
ifeq ($(OS),Windows_NT)
	if not exist "$(subst /,\,$(dir $@))" mkdir "$(subst /,\,$(dir $@))"
	$(GCC) -c "$(subst /,\,$<)" -o "$(subst /,\,$@)"
else
	mkdir -p "$(dir $@)"
	$(GCC) -c "$<" -o "$@"
endif

clean:
ifeq ($(OS),Windows_NT)
	if exist "$(subst /,\,$(OBJd))" rmdir /Q /S "$(subst /,\,$(OBJd))"
	if exist "$(subst /,\,$(OUTf))" del /Q "$(subst /,\,$(OUTf))"
	if exist "$(subst /,\,$(SRCd)\$(notdir $(SRCf_global)))" del /Q "$(subst /,\,$(SRCd)\$(notdir $(SRCf_global)))"
else
	rm -rf "$(OBJd)" "$(OUTf)"
endif

debug:
	@echo "Source files: $(SRCfs)"
	@echo "Object files: $(OBJfs)"