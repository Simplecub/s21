TARGET = s21_matrix_oop.a
CC = g++
CFLAGS = -Wall -Werror -Wextra -std=c++17 
TEST_FLAGS = -lgtest -pthread
TEST_TARGET = s21_matrix_test
TEST_A=test_s21_matrix_oop.a
CCOVTEST=-fprofile-arcs -ftest-coverage 
TEST_SRC=./tests_files/test_s21_*.cpp

all:  clean test gcov_report 

build: $(TARGET)

rebuild: clean $(TARGET)

$(TARGET): 
	gcc $(CFLAGS) -O3 -lstdc++ -c *.cpp 
	ar rc $(TARGET)  *.o 
	ranlib $(TARGET)  
	rm -f *.o 

build_coverage:
	$(CC) $(CFLAGS) $(CCOVTEST) -c *.cpp 
	ar rc $(TARGET)  *.o
	ranlib $(TARGET) 

build_test_lib:
	$(CC) $(CFLAGS)  -c ./tests_files/*.cpp
	ar rc $(TEST_A) *.o
	ranlib $(TEST_A)
	rm -f *.o 


test: build_coverage  build_test_lib
	$(CC) $(CFLAGS) $(TEST_A) $(TEST_FLAGS) $(CCOVTEST) $(TARGET) -o $(TEST_TARGET) 
		rm -f *.o
	./s21_matrix_test 

gcov_report:
	mkdir ./report 
	gcov *.gcda  
	gcovr -b 
	gcovr --html-details -o ./report/report.html 
	open ./report/report.html
 
format:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -n *.cpp *.h
	clang-format -n tests_files/*.cpp

fix:
	clang-format -i *.cpp *.h
	clang-format -i tests_files/*.cpp

leaks: test
	@leaks -atExit -- tests/$(TEST_TARGET)

valgrind:
	@CK_FORK=no valgrind --vgdb=no --leak-check=full \
	--show-leak-kinds=all --track-origins=yes --log-file="valgrind.log" -v --verbose -q --quiet -s  ./s21_matrix_test


clean:
	@echo "Deleting unnecessary files..."
	@rm -rf obj *.a *.o  *.log ./report *.gcno *.gcda  *.gcov $(TEST_TARGET) 
