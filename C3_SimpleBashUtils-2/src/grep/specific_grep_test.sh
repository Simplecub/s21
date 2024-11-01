#!/bin/bash

echo "comparing flag -e"
./s21_grep -e test -e TEST -e hh -e AA -e 123 test1.txt > "s21_grep_result_$$.tmp"
grep -e test -e TEST -e hh -e AA -e 123 test1.txt > "grep_result_$$.tmp"
diff -s "s21_grep_result_$$.tmp" "grep_result_$$.tmp"
        rm -f "s21_grep_result_$$.tmp" "grep_result_$$.tmp"

echo "comparing flag -e with few files"
./s21_grep -e test -e TEST -e hh -e AA -e 123 test1.txt test2.txt test3.txt > "s21_grep_result_$$.tmp"
grep -e test -e TEST -e hh -e AA -e 123 test1.txt test2.txt test3.txt > "grep_result_$$.tmp"
diff -s "s21_grep_result_$$.tmp" "grep_result_$$.tmp"
        rm -f "s21_grep_result_$$.tmp" "grep_result_$$.tmp"

echo "comparing using flag -f and flag -e with few files"
./s21_grep -f pattern.txt -e AA -e 123 test1.txt test2.txt test3.txt > "s21_grep_result_$$.tmp"
grep -f pattern.txt -e AA -e 123 test1.txt test2.txt test3.txt > "grep_result_$$.tmp"
diff -s "s21_grep_result_$$.tmp" "grep_result_$$.tmp"
        rm -f "s21_grep_result_$$.tmp" "grep_result_$$.tmp"

echo "comparing flag -o"
./s21_grep -o test test1.txt test2.txt test3.txt > "s21_grep_result_$$.tmp"
grep -o test test1.txt test2.txt test3.txt > "grep_result_$$.tmp"
diff -s "s21_grep_result_$$.tmp" "grep_result_$$.tmp"
        rm -f "s21_grep_result_$$.tmp" "grep_result_$$.tmp"


echo "comparing using -f with -n"
./s21_grep -f pattern.txt -n  test1.txt test2.txt test3.txt > "s21_grep_result_$$.tmp"
grep -f pattern.txt -n  test1.txt test2.txt test3.txt > "grep_result_$$.tmp"
diff -s "s21_grep_result_$$.tmp" "grep_result_$$.tmp"
        rm -f "s21_grep_result_$$.tmp" "grep_result_$$.tmp"

echo "comparing -s"
./s21_grep -s test test.txt > "s21_grep_result_$$.tmp"
grep -s test test.txt > "grep_result_$$.tmp"
diff -s "s21_grep_result_$$.tmp" "grep_result_$$.tmp"
        rm -f "s21_grep_result_$$.tmp" "grep_result_$$.tmp"