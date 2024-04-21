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

main: make_interface copy $(OBJfs)
	ar rcs $(OUTf) $(OBJfs)

exe: make_interface copy $(OBJfs)
	${GCC} ${OBJfs} -o ${EXEf} -L $(SRCd_imp)/*
	
make_interface:
	make -C $(MAKEf)

$(OBJd)/%.o: $(SRCd)/%.c
	mkdir -p $(dir $@)
	$(GCC) -c $< -o $@ -I $(SRCd) -I $(SRCd_imp) -I $(SRCd_core) -I $(SRCd_mimic)

copy:
	mkdir -p $(SRCd_imp)
	cp $(CPYfs) $(SRCd_imp)

clean_full: clean
	rm -rf $(SRCd_imp)

clean:
	rm -rf $(OBJd) $(TMPd) $(OUTf) $(EXEf)

debug:
	@echo "Source files: $(SRCfs)"
	@echo "Object files: $(OBJfs)"
	@echo "Copy files: $(CPYfs)"
