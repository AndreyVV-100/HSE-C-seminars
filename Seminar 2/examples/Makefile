CC = clang
GCC = gcc
FLAGS = -Wall -Wextra
BIN = bin

.PHONY: all run clean

all: run clean

clean:
	@rm -rf $(BIN)

$(BIN):
	@mkdir -p $(BIN)

run: | $(BIN)
	@echo "Компилятор: `$(CC) --version | head -1`"
	@echo "Компилятор: `$(GCC) --version | head -1`"
	@echo
	@echo "═══ 01-sequence-points.c — clang (-Wunsequenced)"
	@$(CC) $(FLAGS) 01-sequence-points.c -o $(BIN)/01-seq-clang && ./$(BIN)/01-seq-clang
	@echo "═══ 01-sequence-points.c — gcc (-Wsequence-point): те же строки, другие числа"
	@$(GCC) $(FLAGS) 01-sequence-points.c -o $(BIN)/01-seq-gcc && ./$(BIN)/01-seq-gcc
	@echo
	@echo "═══ 02-if-traps.c — присваивание в if, висячий else, пустое тело"
	@$(CC) $(FLAGS) 02-if-traps.c -o $(BIN)/02-if-traps && ./$(BIN)/02-if-traps
	@echo
	@echo "═══ 03-switch-loops.c — clang: проваливание case не заметил"
	@$(CC) $(FLAGS) 03-switch-loops.c -o $(BIN)/03-switch-clang && ./$(BIN)/03-switch-clang
	@echo "═══ 03-switch-loops.c — gcc -Wextra: this statement may fall through"
	@$(GCC) $(FLAGS) 03-switch-loops.c -o $(BIN)/03-switch-gcc && ./$(BIN)/03-switch-gcc
	@echo
	@echo "═══ 04-printf-specs.c — спецификаторы, ширина, модификаторы длины"
	@$(CC) $(FLAGS) 04-printf-specs.c -o $(BIN)/04-printf && ./$(BIN)/04-printf
	@echo "═══ 05-scanf.c — нормальный ввод"
	@$(CC) $(FLAGS) 05-scanf.c -o $(BIN)/05-scanf && printf '12 7 2.5\n' | ./$(BIN)/05-scanf
	@echo "═══ 05-scanf.c — буквенный ввод: scanf вернул 0"
	@printf 'abc\n' | (./$(BIN)/05-scanf; echo "[код выхода $$?]")
	@echo "═══ 05-scanf.c с -DBAD_SCANF: %f вместо %lf, double записан только наполовину"
	@$(CC) $(FLAGS) -DBAD_SCANF 05-scanf.c -o $(BIN)/05-scanf-bad && printf '12 7 2.5\n' | ./$(BIN)/05-scanf-bad
	@echo
	@echo "═══ 06-pointers.c — &x, %p, запись через *p, swap по значению и по указателю"
	@$(CC) $(FLAGS) 06-pointers.c -o $(BIN)/06-pointers && ./$(BIN)/06-pointers
	@echo "═══ 06-pointers.c, -DNULL_DEREF: разыменование NULL"
	@$(CC) $(FLAGS) -DNULL_DEREF 06-pointers.c -o $(BIN)/06-null && (timeout 2 ./$(BIN)/06-null; echo "[код выхода $$?]")
	@echo "═══ 06-pointers.c, -DUNINIT_DEREF: разыменование неинициализированного указателя"
	@$(CC) $(FLAGS) -DUNINIT_DEREF 06-pointers.c -o $(BIN)/06-uninit && (timeout 2 ./$(BIN)/06-uninit; echo "[код выхода $$?]")
	@echo "═══ 06-pointers.c, -DBOGUS_DEREF: разыменование случайного адреса 0x12345678"
	@$(CC) $(FLAGS) -DBOGUS_DEREF 06-pointers.c -o $(BIN)/06-bogus && (timeout 2 ./$(BIN)/06-bogus; echo "[код выхода $$?]")
	@echo "═══ 06-pointers.c, -DUNINIT_DEREF в gcc: тот же мусорный адрес, и предупреждение от компилятора"
	@$(GCC) $(FLAGS) -DUNINIT_DEREF 06-pointers.c -o $(BIN)/06-uninit-gcc && (timeout 2 ./$(BIN)/06-uninit-gcc; echo "[код выхода $$?]")
	@echo
	@echo "═══ 07-arrays.c — адресная арифметика, массив как параметр"
	@$(CC) $(FLAGS) 07-arrays.c -o $(BIN)/07-arrays && ./$(BIN)/07-arrays
	@echo "═══ 07-arrays.c под AddressSanitizer: запись a[5] поймана"
	@$(CC) $(FLAGS) -fsanitize=address 07-arrays.c -o $(BIN)/07-arrays-asan 2>/dev/null; (./$(BIN)/07-arrays-asan 2>&1 | sed -n '1,3p')
