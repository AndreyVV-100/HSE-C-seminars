CC = clang
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
	@echo
	@echo "═══ 01-hello-world.c — простейшая программа"
	@$(CC) $(FLAGS) 01-hello-world.c -o $(BIN)/01-hello-world && ./$(BIN)/01-hello-world
	@echo
	@echo "═══ 02-type-sizes.c — типы, размеры, promotions"
	@$(CC) $(FLAGS) 02-type-sizes.c -o $(BIN)/02-type-sizes && ./$(BIN)/02-type-sizes
	@echo
	@echo "═══ 03-int-arith.c — целочисленная арифметика, преобразования, литералы"
	@$(CC) $(FLAGS) 03-int-arith.c -o $(BIN)/03-int-arith && ./$(BIN)/03-int-arith
	@echo
	@echo "═══ 04-bit-ops.c — битовые операции и приоритет"
	@$(CC) $(FLAGS) 04-bit-ops.c -o $(BIN)/04-bit-ops && ./$(BIN)/04-bit-ops
	@echo
	@echo "═══ 05-signed-unsigned.c — знаковость и беззнаковое переполнение"
	@$(CC) $(FLAGS) 05-signed-unsigned.c -o $(BIN)/05-signed-unsigned && ./$(BIN)/05-signed-unsigned
	@echo
	@echo "═══ 06-ub-overflow.c при -O0: знаковое переполнение заметно"
	@$(CC) $(FLAGS) -O0 06-ub-overflow.c -o $(BIN)/06-ub-overflow-o0 && ./$(BIN)/06-ub-overflow-o0
	@echo "═══ 06-ub-overflow.c при -O2: компилятор считает, что UB не бывает"
	@$(CC) $(FLAGS) -O2 06-ub-overflow.c -o $(BIN)/06-ub-overflow-o2 && ./$(BIN)/06-ub-overflow-o2
	@echo "═══ greater() в машинном коде при -O2:"
	@objdump -d $(BIN)/06-ub-overflow-o2 | grep -A2 '<greater>:'
	@echo "═══ 06-ub-overflow.c при -O2 -fwrapv: переполнение сделано определённым"
	@$(CC) $(FLAGS) -O2 -fwrapv 06-ub-overflow.c -o $(BIN)/06-ub-overflow-wrapv && ./$(BIN)/06-ub-overflow-wrapv
	@echo
	@echo "═══ 07-ub-infinite-loop.c при -O0: зависается (таймаут 2 с)"
	@$(CC) $(FLAGS) -O0 07-ub-infinite-loop.c -o $(BIN)/07-loop-o0 && (timeout 2 ./$(BIN)/07-loop-o0; echo "[код выхода $$?]")
	@echo "═══ 07-ub-infinite-loop.c при -O2: цикл удалён, код выхода — мусор"
	@$(CC) $(FLAGS) -O2 07-ub-infinite-loop.c -o $(BIN)/07-loop-o2 && (timeout 2 ./$(BIN)/07-loop-o2; echo "[код выхода $$?]")
