CC = g++
CFLAGS = -std=c++17 -Wall -Werror -Wextra
EXECUTABLE = ./test
SRC_LIST_TEST = ./tests/*test.cc
SOURCE = $(SRC_LIST_TEST)
TEST_FLAGS = -lgtest
IGNORE=
INCLUDE_FILES = \
    --include "$(PWD)/s21_list.h" \
    --include "$(PWD)/s21_queue.h" \
    --include "$(PWD)/s21_set.h" \
	--include "$(PWD)/s21_multiset.h" \
    --include "$(PWD)/s21_stack.h" \
    --include "$(PWD)/s21_tree.h" \
    --include "$(PWD)/s21_vector.h" \
	--include "$(PWD)/s21_map.h" \
	--include "$(PWD)/s21_array.h"
#++++

UNAME = $(shell uname)

ifeq ($(UNAME), Linux)
OPEN_REPORT += xdg-open
LEAKS += CK_FORK=no valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all -s --track-origins=yes
endif

ifeq ($(UNAME), Darwin)
OPEN_REPORT += open
LEAKS += leaks -atExit --
IGNORE += --ignore-errors inconsistent
endif

all:  test

test: clean
	@$(CC) $(CFLAGS) $(SOURCE) -o $(EXECUTABLE) $(TEST_FLAGS) && $(EXECUTABLE)


gcov_report: clean
	@$(CC) $(CFLAGS) $(SOURCE) -lgtest_main -lgtest -o $(EXECUTABLE) --coverage
	@./$(EXECUTABLE)
	mkdir report

	lcov -t "Report" -c -d ./ --output-file ./report/coverage.info $(INCLUDE_FILES)  $(IGNORE)
	genhtml ./report/coverage.info --output-directory ./report $(IGNORE)
	rm -f *.gcda *.gcno
	$(OPEN_REPORT) ./report/index.html
#	gcovr -r . --html --html-details -o ./report/coverage_report.html
#	rm -f *.gcda *.gcno
#	$(OPEN_REPORT) ./report/coverage_report.html

format:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -n *.h tests/*.cc tests/*.h

fix:
	clang-format -i *.h tests/*.cc tests/*.h

leaks_check: test
	@$(LEAKS) ./$(EXECUTABLE)

clean:
	@echo "Deleting unnecessary files..."
	@rm -rf obj *.a *.o  *.log ./report *.gcno *.gcda  *.gcov  $(EXECUTABLE)