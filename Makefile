LIB_NAME = main

CLI_ARGUMENTS = input/glossy.ini

CXX = clang++ -std=c++20
GCOV = gcov
GCOVR = gcovr

COV_FLAGS = -lgcov -coverage
GCOV_FLAGS = -r . --html --html-details
DEBUG_FLAGS = -Wall -Wextra -pedantic -g
RELEASE_FLAGS = -O2 -DNDEBUG -g

SRC_DIR = src
OUT_DIR = build
LIB_DIR = lib
TST_DIR = test
OUTPUT_DIR = output

SRCS = $(shell find $(SRC_DIR) -name '*.cc')
TSTS = $(shell find $(TST_DIR) -name '*.cc')
TESTED = src/vectorUtils.cc

export OUTDIR = $(OUTPUT_DIR)/

.PHONY: run clean valgrind coverage format gdb

$(LIB_NAME):
	mkdir -p $(OUT_DIR)
	$(CXX) -c $(SRCS) $(RELEASE_FLAGS) 
	$(CXX) *.o -o $(OUT_DIR)/$(LIB_NAME) -lsfml-graphics -lsfml-window -lsfml-system
	rm -f *.o

debug: # analyze
	mkdir -p $(OUT_DIR)
	$(CXX) -c $(SRCS) $(DEBUG_FLAGS) 
	$(CXX) *.o -o $(OUT_DIR)/$(LIB_NAME) -lsfml-graphics -lsfml-window -lsfml-system
	rm -f *.o

analyze:
	$(CXX) --analyze -Xanalyzer -analyzer-output=text $(SRCS)

run: $(LIB_NAME)
	./build/main $(CLI_ARGUMENTS)

runDebug: debug
	./$(OUT_DIR)/main $(CLI_ARGUMENTS)

buildTest:
	$(CXX) $(DEBUG_FLAGS) $(TSTS) -L$(LIB_DIR) -o $(OUT_DIR)/test -lsfml-graphics -lsfml-system -I$(SRC_DIR) $(TESTED)
	rm -f *.o

test: buildTest 
	./$(OUT_DIR)/test

valgrind:  debug
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --track-origins=yes ./$(OUT_DIR)/$(LIB_NAME) 

valgrind-v: debug
	valgrind --tool=memcheck -v --leak-check=full --show-reachable=yes --track-origins=yes ./$(OUT_DIR)/$(LIB_NAME)

callgrind: debug
	rm -f $(OUT_DIR)/callgrind.out.*
	valgrind --tool=callgrind ./$(OUT_DIR)/$(LIB_NAME) 
	mv callgrind.out.* build/
	kcachegrind $(OUT_DIR)/callgrind.out.*
	
format:
	clang-format  -i $(shell find . -name '*.cc') $(shell find . -name '*.hpp' ! -name 'catch_amalgamated.hpp') -style=webkit

clean:
	-rm -rf $(OUT_DIR) $(COV_DIR) 

gdb: debug
	gdb ./$(OUT_DIR)/$(LIB_NAME)
