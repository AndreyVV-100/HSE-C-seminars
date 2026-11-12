CC = clang
FLAGS = -g -Wall -Wextra
ASAN = -fsanitize=address
DOT = dot
GRAPH = ../graph.c
BIN = bin
FIG = figs

TESTS = test-1 test-2 test-3 test-4

.PHONY: all run figs clean

all: run figs

clean:
	@rm -rf $(BIN) $(FIG)

$(BIN):
	@mkdir -p $(BIN)

$(FIG):
	@mkdir -p $(FIG)

run: | $(BIN)
	@echo "Компилятор: `$(CC) --version | head -1`"
	@echo
	@echo "═══ Тест 1 (план, 3.1) — одна вершина"
	@$(CC) $(FLAGS) $(ASAN) $(GRAPH) test-1.c -o $(BIN)/test-1 && ./$(BIN)/test-1
	@echo
	@echo "═══ Тест 2 (план, 3.2) — три вершины, корень с left и right"
	@$(CC) $(FLAGS) $(ASAN) $(GRAPH) test-2.c -o $(BIN)/test-2 && ./$(BIN)/test-2
	@echo
	@echo "═══ Тест 3 (план, 3.3) — цикл A -> B -> A"
	@$(CC) $(FLAGS) $(ASAN) $(GRAPH) test-3.c -o $(BIN)/test-3 && ./$(BIN)/test-3 2>&1 | sed -n '1,10p;/SUMMARY/p'
	@echo
	@echo "═══ Тест 4 (план, 3.4) — общий сосед: A -> B, A -> C, B -> C, C -> A"
	@$(CC) $(FLAGS) $(ASAN) $(GRAPH) test-4.c -o $(BIN)/test-4 && ./$(BIN)/test-4 2>&1 | sed -n '1,10p;/SUMMARY/p'

figs: | $(FIG)
	@for t in $(TESTS); do $(DOT) -Tpng $$t.dot -o $(FIG)/$$t.png; done
