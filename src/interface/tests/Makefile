GCC = x86_64-w64-mingw32-gcc
SRCd = src
SRCd_imp = $(SRCd)/imported
SRCd_core = $(SRCd)/core
SRCd_mimic = $(SRCd)/mimic
OBJd = obj
TMPd = tmp
OUTf = interface_ut.a
EXEf = interface_ut.exe
CPYfs = ../interface.a ../src/interface.h ../../global.h
MAKEf = ../
SRCfs = $(wildcard $(SRCd_imp)/*.c $(SRCd_core)/*.c $(SRCd_mimic)/*.c)
OBJfs = $(patsubst $(SRCd)/%,$(OBJd)/%,$(SRCfs:.c=.o))

ifeq ($(OS),Windows_NT)
	COPY_CMD = copy
else
	COPY_CMD = cp
endif

main: make_interface copy $(OBJfs)
	ar rcs $(OUTf) $(OBJfs)

exe: make_interface copy $(OBJfs)
	${GCC} ${OBJfs} -o ${EXEf} -L $(SRCd_imp)/*
	
make_interface:
	make -C $(MAKEf)

$(OBJd)/%.o: $(SRCd)/%.c
ifeq ($(OS),Windows_NT)
	mkdir $(dir $@)
else
	mkdir -p $(dir $@)
endif
	$(GCC) -c $< -o $@ -I $(SRCd) -I $(SRCd_imp) -I $(SRCd_core) -I $(SRCd_mimic)

copy:
ifeq ($(OS),Windows_NT)
	mkdir "$(abspath $(SRCd_imp))"
	$(foreach file,$(CPYfs),copy "$(abspath $(file))" "$(abspath $(SRCd_imp)\$(notdir $(file)))")
else
	mkdir -p $(SRCd_imp)
	cp $(CPYfs) $(SRCd_imp)
endif

clean:
ifeq ($(OS),Windows_NT)
	rmdir /S /Q $(SRCd_imp) $(OBJd) $(TMPd) $(OUTf) $(EXEf)
else
	rm -rf $(SRCd_imp) $(OBJd) $(TMPd) $(OUTf) $(EXEf)
endif

debug:
	@echo "Source files: $(SRCfs)"
	@echo "Object files: $(OBJfs)"
	@echo "Copy files: $(CPYfs)"