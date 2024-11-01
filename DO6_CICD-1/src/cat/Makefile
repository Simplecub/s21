CC=gcc
CFLAGS=-Wall -Werror -Wextra

all: s21_cat

s21_cat: s21_cat.o cat_tools.o
	$(CC) $(CFLAGS) cat_tools.o s21_cat.o -o s21_cat 

s21_cat.o: s21_cat.c
	$(CC) $(CFLAGS) -c s21_cat.c -o s21_cat.o

cat_tools.o: cat_tools.c cat_tools.h
	$(CC) $(CFLAGS) -c cat_tools.c -o cat_tools.o

test: s21_cat
	chmod +x test_cat.sh
	./test_cat.sh

clean:
	rm -rf *.o s21_cat

rebuild: clean all