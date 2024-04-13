GCC = x86_64-w64-mingw32-gcc
SRCd = src
SRCd_imp = ${SRCd}/imported
SRCd_core = ${SRCd}/core
SRCd_mimic = ${SRCd}/mimic
OBJd = obj
TMPd = tmp
EXEf = interface_ut.exe
SRCfs = $(wildcard ${SRCd_imp}/*.c ${SRCd_core}/*.c ${SRCd_mimic}/*.c)
OBJfs = $(patsubst $(SRCd)/%,$(OBJd)/%,$(SRCfs:.c=.o))

main: clean ${OBJfs}
	${GCC} ${OBJfs} -o ${EXEf}

$(OBJd)/%.o: $(SRCd)/%.c
	mkdir -p $(dir $@)
	${GCC} -c $< -o $@ -I ${SRCd_imp} -I ${SRCd_core} -I ${SRCd_mimic}

clean:
	rm -rf ${OBJd} ${TMPd} ${EXEf}

debug:
	@echo "Source files: ${SRCfs}"
	@echo "Object files: ${OBJfs}"