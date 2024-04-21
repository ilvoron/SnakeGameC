GCC = x86_64-w64-mingw32-gcc
SRCd = src
SRCf_global = ../global.h
OBJd = obj
OUTf = interface.a
SRCfs = $(wildcard $(SRCd)/*.c $(SRCd_global)/*.c)
OBJfs = $(patsubst $(SRCd)/%,$(OBJd)/%,$(SRCfs:.c=.o))

ifeq ($(OS),Windows_NT)
	COPY_CMD = copy
else
	COPY_CMD = cp
endif

main: copy $(OBJfs)
	ar rcs $(OUTf) $(OBJfs)

copy:
	$(COPY_CMD) "$(abspath $(SRCf_global))" "$(abspath $(SRCd)/$(notdir $(SRCf_global)))"

$(OBJd)/%.o: $(SRCd)/%.c
ifeq ($(OS),Windows_NT)
	mkdir $(dir $@)
else
	mkdir -p $(dir $@)
endif
	$(GCC) -c $< -o $@

clean:
	rmdir $(OBJd) $(OUTf)

debug:
	@echo "Source files: $(SRCfs)"
	@echo "Object files: $(OBJfs)"