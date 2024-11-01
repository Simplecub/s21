CC=g++ 
CFLAG=  -Wall -Werror -Wextra -std=c++17  -Wpedantic
TEST_DIR = build_test
BUILD_DIR := build
CCOVTEST=-fprofile-arcs -ftest-coverage 
IGNORE=
INCLUDE_FILES = \
	--include "$(PWD)/brick_game/snake/snake_back.cpp"\
	--include "$(PWD)/brick_game/tetris/tetris_back.cpp*" 


OS := $(shell uname)
ifeq ($(OS), Darwin)
OPEN_REPORT += open
LIB_FLAGS := $(shell pkg-config --static --cflags --libs gtest ncurses)
IGNORE += --ignore-errors inconsistent
LEAKS += leaks -atExit --
else
OPEN_REPORT += xdg-open
LIB_FLAGS := $(shell pkg-config --static --cflags --libs gtest ncursesw)
LEAKS += CK_FORK=no valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all -s --track-origins=yes
endif

all:  clean install

install: tetris.a snake.a
	$(CC) $(CFLAG) main_cli.cpp gui/cli/front.cpp controller/controller.cpp build/tetris_back.a -o build/tetris_cli $(LIB_FLAGS) -DTETRIS=1
	$(CC) $(CFLAG) main_cli.cpp gui/cli/front.cpp controller/controller.cpp build/snake_back.a -o build/snake_cli $(LIB_FLAGS) -DSNAKE=1
	sed -i '3s/^/#define SNAKE\n/' controller/controller.h
	rm -rf tmp && mkdir tmp && cd tmp && cmake ../cmake_snake_desktop && make && cp snake_desktop ../build/snake_desktop
	sed -i '3d' controller/controller.h
	rm -rf tmp && mkdir tmp && cd tmp && cmake ../cmake_tetris_desktop && make && cp tetris_desktop ../build/tetris_desktop
	rm -rf tmp
	rm -rf $(BUILD_DIR)/tetris_back.a
	rm -rf $(BUILD_DIR)/snake_back.a


run1:
	build/tetris_cli

run2: 
	build/snake_cli

run3:
	build/tetris_desktop

run4: 
	build/snake_desktop

tetris.a: 
	mkdir -p build
	$(CC) $(CFLAG) -c brick_game/tetris/tetris_back.cpp -o $(BUILD_DIR)/tetris_back.o
	ar rc $(BUILD_DIR)/tetris_back.a $(BUILD_DIR)/tetris_back.o
	ranlib $(BUILD_DIR)/tetris_back.a
	rm -rf $(BUILD_DIR)/tetris_back.o 

snake.a: 
	mkdir -p build
	$(CC) $(CFLAG) -c brick_game/snake/snake_back.cpp -o $(BUILD_DIR)/snake_back.o
	ar rc $(BUILD_DIR)/snake_back.a $(BUILD_DIR)/snake_back.o
	ranlib $(BUILD_DIR)/snake_back.a
	rm -rf $(BUILD_DIR)/snake_back.o 

uninstall: clean

dvi:
	mkdir -p docs
	doxygen
	cd docs/latex && make all
	open docs/latex/refman.pdf

dist: clean install dvi
	mkdir -p ./dist
	tar cvzf BrickGame-2.0.tar.gz $(BUILD_DIR) docs/latex/refman.pdf README.md pic
	cp BrickGame-2.0.tar.gz ./dist
	rm -f  BrickGame-2.0.tar.gz

tests: clean tetris.a snake.a
	mkdir -p $(TEST_DIR)
	$(CC) $(CFLAGS) tests_files/main_tests.cpp tests_files/tetris_test.cpp tests_files/snake_test.cpp  $(BUILD_DIR)/tetris_back.a $(BUILD_DIR)/snake_back.a  -o $(TEST_DIR)/tests $(LIB_FLAGS) 
	rm -rf $(BUILD_DIR)/tetris_back.a
	rm -rf $(BUILD_DIR)/snake_back.a
	./$(TEST_DIR)/tests

build_coverage:
	mkdir -p $(TEST_DIR)
	$(CC) $(CFLAG) $(CCOVTEST) -c brick_game/tetris/tetris_back.cpp -o $(TEST_DIR)/backt_cov.o $(LIB_FLAGS)
	ar rc $(TEST_DIR)/backt_cov.a $(TEST_DIR)/backt_cov.o
	ranlib $(TEST_DIR)/backt_cov.a
	rm -f $(TEST_DIR)/backt_cov.o
	$(CC) $(CFLAG) $(CCOVTEST) -c brick_game/snake/snake_back.cpp -o $(TEST_DIR)/backs_cov.o $(LIB_FLAGS)
	ar rc $(TEST_DIR)/backs_cov.a $(TEST_DIR)/backs_cov.o
	ranlib $(TEST_DIR)/backs_cov.a
	rm -f $(TEST_DIR)/backs_cov.o

gcov_report: clean build_coverage 
	$(CC) $(CFLAGS) tests_files/main_tests.cpp tests_files/tetris_test.cpp tests_files/snake_test.cpp  $(TEST_DIR)/backt_cov.a $(TEST_DIR)/backs_cov.a  -o $(TEST_DIR)/test_back $(LIB_FLAGS) -lgcov
	$(TEST_DIR)/test_back
	mkdir -p ./report 

	lcov -t "Report" -c -d ./ --output-file ./report/coverage.info $(INCLUDE_FILES)  $(IGNORE)
	genhtml ./report/coverage.info --output-directory ./report $(IGNORE)
	rm -f *.gcda *.gcno
	$(OPEN_REPORT) ./report/index.html
	rm -f $(TEST_DIR)/*.gcda $(TEST_DIR)/*.gcno *.gcov

leaks_check: tests
	@$(LEAKS) $(TEST_DIR)/tests

format:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -n *.cpp */*.cpp */*.h */*/*.cpp */*/*.h

fix:
	clang-format -i *.cpp */*.cpp */*.h */*/*.cpp */*/*.h

clean:
	rm -rf ./report ./build $(TEST_DIR) ./dist ./docs *score  *.gcno *.gcda  *.gcov 

rebuild: clean install