CC=gcc 
CFLAG=  -Wall -Werror -Wextra -std=c11  -Wpedantic
TEST_DIR = build_test
BUILD_DIR := build
CHECK=$(shell pkg-config --cflags --libs check) 
CCOVTEST=-fprofile-arcs -ftest-coverage 
CCOV=-fprofile-arcs  

OS := $(shell uname)
ifeq ($(OS), Darwin)
	LIB_FLAGS := $(shell pkg-config --static --cflags --libs check ncurses)
else
	LIB_FLAGS := $(shell pkg-config --static --cflags --libs check ncursesw)
endif


all:  clean install

install: tetris.a
	$(CC) $(CFLAG) tetris.c gui/cli/front.c build/back.a -o build/tetris $(LIB_FLAGS) 

run: clean install
	build/tetris


tetris.a: 
	mkdir -p build
	$(CC) $(CFLAG) -c brick_game/tetris/back.c -o $(BUILD_DIR)/back.o
	ar rc $(BUILD_DIR)/back.a $(BUILD_DIR)/back.o
	ranlib $(BUILD_DIR)/back.a
	rm -rf $(BUILD_DIR)/back.o 

uninstall: clean

dvi :
	mkdir -p docs
	doxygen
	cd docs/latex && make all
	open docs/latex/refman.pdf
#	open docs/html/index.html

dist: clean install
	mkdir -p ./dist
	tar cvzf tetris-1.0.tar.gz Makefile brick_game gui tests_files tetris.c fsm.png
	cp tetris-1.0.tar.gz ./dist
	rm -f  tetris-1.0.tar.gz

build_test_lib:
	mkdir -p $(TEST_DIR)
	$(CC) $(CFLAG) -c tests_files/test*.c
	ar rc $(TEST_DIR)/test_back.a *.o
	ranlib $(TEST_DIR)/test_back.a
	rm -f *.o 

test: clean install build_test_lib
	$(CC) $(TEST_DIR)/test_back.a $(CHECK)  build/back.a -o $(TEST_DIR)/test_back
	rm -f *.o 
	$(TEST_DIR)/test_back

build_coverage:
	mkdir -p $(TEST_DIR)
	$(CC) $(CFLAG) $(CCOVTEST) -c brick_game/tetris/back.c -o $(TEST_DIR)/back_cov.o
	ar rc $(TEST_DIR)/back_cov.a $(TEST_DIR)/back_cov.o
	ranlib $(TEST_DIR)/back_cov.a
	rm -f $(TEST_DIR)/back_cov.o

gcov_report: clean build_coverage build_test_lib
	$(CC) $(TEST_DIR)/test_back.a $(CHECK) $(CCOV) $(TEST_DIR)/back_cov.a -o $(TEST_DIR)/test_back
	rm -f *.o 
	$(TEST_DIR)/test_back
	mkdir -p ./report 
	gcov $(TEST_DIR)/*.gcda  
	gcovr -b 
	gcovr --html-details -o ./report/report.html 
	open ./report/report.html
	rm -f $(TEST_DIR)/*.gcda $(TEST_DIR)/*.gcno *.gcov

valgrind-test : test
	CK_FORK=no valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all -s --track-origins=yes $(TEST_DIR)/test_back

format:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -n *.c */*.c */*.h */*/*.c */*/*.h

fix:
	clang-format -i *.c */*.c */*.h */*/*.c */*/*.h

clean:
	rm -rf ./report ./build $(TEST_DIR) ./dist ./docs score