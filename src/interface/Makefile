GCC = x86_64-w64-mingw32-gcc
SRCd = src
SRCd_global = ..
OBJd = obj
OUTf = interface.exe
SRCfs = $(wildcard $(SRCd)/*.c $(SRCd_global)/*.c)
OBJfs = $(patsubst $(SRCd)/%,$(OBJd)/%,$(SRCfs:.c=.o))

main: $(OBJfs)
	ar rcs $(OUTf) $(OBJfs)

$(OBJd)/%.o: $(SRCd)/%.c
	mkdir -p $(dir $@)
	$(GCC) -c $< -o $@ -I $(SRCd) -I $(SRCd_global)

clean:
	rm -rf $(OBJd) $(OUTf)

debug:
	@echo "Source files: $(SRCfs)"
	@echo "Object files: $(OBJfs)"