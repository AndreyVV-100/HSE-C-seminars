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
	@echo "═══ 01-array-to-pointer.c — массив decay в указатель, a[i] это *(a + i)"
	@$(CC) $(FLAGS) 01-array-to-pointer.c -o $(BIN)/01-arrays && ./$(BIN)/01-arrays
	@echo "═══ 01-array-to-pointer.c — gcc: массивы лежат в другом порядке (сравнение и разность — UB)"
	@$(GCC) $(FLAGS) 01-array-to-pointer.c -o $(BIN)/01-arrays-gcc && ./$(BIN)/01-arrays-gcc
	@echo
	@echo "═══ 02-pointer-to-array.c — a и &a, шаг 4 байта против 20; int *a[3] и int (*b)[3]"
	@$(CC) $(FLAGS) 02-pointer-to-array.c -o $(BIN)/02-pointer && ./$(BIN)/02-pointer
	@echo
	@echo "═══ 03-2d-layout.c — sizeof таблицы/строки/элемента, три способа достать m[1][2], транспонирование"
	@$(CC) $(FLAGS) 03-2d-layout.c -o $(BIN)/03-2d && ./$(BIN)/03-2d
	@echo
	@echo "═══ 04-vla.c — размер из stdin, sizeof считается во время работы"
	@$(CC) $(FLAGS) 04-vla.c -o $(BIN)/04-vla && printf '5\n' | ./$(BIN)/04-vla
	@echo "═══ 04-vla.c с -DTRY_INIT: VLA нельзя инициализировать (ожидаемая ошибка компиляции)"
	@$(CC) $(FLAGS) -DTRY_INIT 04-vla.c -o $(BIN)/04-tryinit 2> $(BIN)/tryinit.log; cat $(BIN)/tryinit.log
	@echo "═══ 04-vla.c с -DBIG: 4 ГБ в стеке"
	@$(CC) $(FLAGS) -DBIG 04-vla.c -o $(BIN)/04-big && printf '5\n' | (./$(BIN)/04-big > $(BIN)/big.log 2>&1; echo "[код выхода $$?]"; cat $(BIN)/big.log)
	@echo "═══ 04-vla.c с -DBIG под AddressSanitizer: stack-overflow"
	@$(CC) $(FLAGS) -fsanitize=address -DBIG 04-vla.c -o $(BIN)/04-big-asan && printf '5\n' | (./$(BIN)/04-big-asan > $(BIN)/big-asan.log 2>&1; echo "[код выхода $$?]"; sed -n '1,3p;/SUMMARY/p' $(BIN)/big-asan.log)
	@echo
	@echo "═══ 05-functions.c — параметр-копия, запись через адрес, sizeof внутри функции"
	@$(CC) $(FLAGS) 05-functions.c -o $(BIN)/05-func && ./$(BIN)/05-func
	@echo "═══ 05-functions.c с -DSTAR_STAR: clang предупреждает и падает (int ** не подходит к int m[3][4])"
	@$(CC) $(FLAGS) -DSTAR_STAR 05-functions.c -o $(BIN)/05-starstar && (timeout 5 ./$(BIN)/05-starstar > $(BIN)/starstar.log 2>&1; echo "[код выхода $$?]"; cat $(BIN)/starstar.log)
	@echo "═══ 05-functions.c с -DSTAR_STAR в gcc: incompatible pointer types — отказ компилировать"
	@$(GCC) $(FLAGS) -DSTAR_STAR 05-functions.c -o $(BIN)/05-starstar-gcc 2> $(BIN)/starstar-gcc.log; sed -n '/error:/,+2p' $(BIN)/starstar-gcc.log
	@echo
	@echo "═══ 06-scope-static.c — одно имя три переменные (-Wshadow), static-счётчик"
	@$(CC) $(FLAGS) -Wshadow 06-scope-static.c -o $(BIN)/06-scope && ./$(BIN)/06-scope
	@echo "═══ 06-scope-static.c с -DNO_STATIC: счётчик 1 1 1"
	@$(CC) $(FLAGS) -DNO_STATIC 06-scope-static.c -o $(BIN)/06-no-static && ./$(BIN)/06-no-static
	@echo
	@echo "═══ 07-recursion.c — базовый случай, шаг к нему"
	@$(CC) $(FLAGS) 07-recursion.c -o $(BIN)/07-rec && ./$(BIN)/07-rec
	@echo "═══ 07-recursion.c с -DBASELESS, -Werror: компилятор видит бесконечную рекурсию"
	@$(CC) $(FLAGS) -Werror -DBASELESS 07-recursion.c -o $(BIN)/07-baseless-werror 2> $(BIN)/baseless-werror.log; cat $(BIN)/baseless-werror.log
	@echo "═══ 07-recursion.c с -DBASELESS без -Werror: предупреждение, потом stack overflow"
	@$(CC) $(FLAGS) -DBASELESS 07-recursion.c -o $(BIN)/07-baseless && (timeout 10 ./$(BIN)/07-baseless > $(BIN)/baseless.log 2>&1; echo "[код выхода $$?]"; cat $(BIN)/baseless.log)
	@echo
	@echo "═══ Итоги: -Wshadow, -Wincompatible-pointer-types, -Winfinite-recursion, -fsanitize=address"
	@echo "═══ Ошибка компиляции — это тоже результат: её текст выше"
