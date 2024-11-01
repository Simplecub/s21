#!/bin/bash

for file in test{1,2,3}.txt; do
    for option in b e n s t v; do
        echo "TEST $file, option $option"
        ./s21_cat -"$option" "$file" > "s21_cat_result_$$.tmp"
        cat -"$option" "$file" > "cat_result_$$.tmp"
        diff -s "s21_cat_result_$$.tmp" "cat_result_$$.tmp"
        rm -f "s21_cat_result_$$.tmp" "cat_result_$$.tmp"
    done
done
