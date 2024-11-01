CC = gcc
FLAGS = -std=c11 -Wall -Werror -Wextra 
FLAG_COV = --coverage
FLAG_O = -o
s21_STRING_C = s21_*.c 
s21_STRING_O = s21_*.o 
TEST_CASES_C = suite_*.c
TEST_CASES_O = suite_*.o
BUILD =./

OS= $(shell uname)
ifeq ($(OS), Darwin)
 TEST_FLAGS=-lcheck
else
 TEST_FLAGS=-lcheck -lpthread -pthread -lrt -lm -lsubunit
endif

all: clean gcov_report

s21_string.a: 
	$(CC) -c $(FLAGS) $(s21_STRING_C)
	ar rc s21_string.a $(s21_STRING_O) 
	ranlib s21_string.a

test: s21_string.a 
	$(CC) -c $(FLAGS) $(TEST_CASES_C) main.c 
	ar rc test_cases.a $(TEST_CASES_O)
	ranlib test_cases.a
	$(CC) $(FLAGS) $(FLAG_COV) -o tests main.o $(TEST_FLAGS) s21_string.a test_cases.a   $(s21_STRING_C) 
	./tests


	
gcov_report: test
	gcov *.gcda
	gcovr --html-details -o report.html
#	xdg-open report.html

valgrind_tests:
	valgrind  --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose  --log-file=log.txt ./tests 



clean:
	rm -rf $(BUILD)roots *.o *.gcno *.gcda *.html *.css *.a  tests *.gcov log.txt
open:
	firefox $(BUILD)report.html
	
rebuild: clean all

