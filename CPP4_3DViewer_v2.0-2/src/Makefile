.PHONY: all install uninstall clean dvi dist launch tests style valgrind

CFLAGS = -Wall -Werror -Wextra -std=c++17 -pedantic -g
LDFLAGS = $(shell pkg-config --cflags --libs gtest)
APP_NAME = 3DViewer
IGNORE=
INCLUDE_FILES = \
    --include "$(PWD)/model/model.cc" \
    --include "$(PWD)/model/tranformation.cc" 


OS := $(shell uname -s)
ifeq ($(OS), Linux)
  OPEN = ./build/$(APP_NAME)
  OPEN_REPORT += xdg-open
  LEAKS += CK_FORK=no valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all -s --track-origins=yes
endif

ifeq ($(OS), Darwin)
OPEN = open build/$(APP_NAME).app
OPEN_REPORT += open
LEAKS += leaks -atExit --
IGNORE += --ignore-errors inconsistent
endif

all: install launch

install:
	cmake -B build
	make -C build 3DViewer

uninstall:
	$(MAKE) clean
	rm -rf build

clean:
	rm -rf valgrind.txt 3DViewer.tar.gz
	rm -rf test ./report rm -f *.gcda *.gcno ./build


dvi:
	$(OPEN_REPORT) ./README.md

dist:
	$(MAKE) install
	tar -czf $(APP_NAME).tar.gz --directory=build/ .

launch:
	$(OPEN)

tests:
	g++ tests/*.cc model/*.cc $(CFLAGS) $(LDFLAGS) -o test
	./test

style:
	clang-format -style=Google -n controller/*.cc controller/*.h model/*.cc model/*.h
	clang-format -style=Google -n view/*.cc view/*.h tests/*.cc tests/*.h
	clang-format -style=Google -n view/QtGifImage/gifimage/* view/QtGifImage/giflib/*
	clang-format -style=Google -n main.cc

gcov_report: clean
	g++  tests/*.cc model/*.cc $(CFLAGS) -lgtest_main -lgtest -o test --coverage
	@./test
	mkdir report

	lcov -t "Report" -c -d ./ --output-file ./report/coverage.info $(INCLUDE_FILES)  $(IGNORE)
	genhtml ./report/coverage.info --output-directory ./report $(IGNORE)
	rm -f *.gcda *.gcno
	$(OPEN_REPORT) ./report/index.html

leaks_check: clean tests
	@$(LEAKS) ./test