CC=gcc 
CFLAG=-Wall -Werror -Wextra -std=c11
CHECK=$(shell pkg-config --cflags --libs check) 
TARGET=s21_matrix.a 
TEST_TARGET=s21_matrix_test 
CCOV=-fprofile-arcs  
CCOVTEST=-fprofile-arcs -ftest-coverage 
TEST_A=test_s21_matrix.a
TEST_SRC=./tests_files/test_*.c

all: clean $(TARGET) test gcov_report

s21_matrix.a: 
	$(CC) $(CFLAG) -c *.c 
	ar rc s21_matrix.a *.o 
	ranlib s21_matrix.a 
	rm -f *.o 

build_coverage:
	$(CC) $(CFLAG) $(CCOVTEST) -c *.c 
	ar rc s21_matrix.a *.o
	ranlib s21_matrix.a

build_test_lib:
	$(CC) $(CFLAG) -c $(TEST_SRC)
	ar rc test_s21_matrix.a *.o
	ranlib test_s21_matrix.a
	rm -f *.o 

test: build_coverage build_test_lib
	$(CC) $(TEST_A) $(CHECK) $(CCOV) $(TARGET) -o $(TEST_TARGET) 
	rm -f *.o
	./s21_matrix_test 

gcov_report:
	mkdir ./report 
	gcov s21_*.gcda  
	gcovr -b 
	gcovr --html-details -o ./report/report.html 
	open ./report/report.html
 
format:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -n *.c *.h
	clang-format -n tests_files/*.c tests_files/*.h
	
fix:
	clang-format -i *.c *.h
	clang-format -i tests_files/*.c tests_files/*.h


valgrind_check: #test
	@CK_FORK=no valgrind --vgdb=no --leak-check=full \
	--show-leak-kinds=all --track-origins=yes --log-file="valgrind.log" -v --verbose -q --quiet -s ./$(TEST_TARGET)


clean: 
	@echo "Deleting unnecessary files..."
	rm -rf ./report *.o *.a *.gcda *.gcno *.gcov s21_matrix_test *.log 
