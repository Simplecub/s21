#!/bin/bash

echo "comparing single flags"
for file in test{1,2,3}.txt; do
    for option in i v c l n h ; do
        for arg in test TesT hh AA 123 ha; do
        echo "TEST $file, option -$option, arg $arg"
        ./s21_grep -"$option" "$arg" "$file" > "s21_grep_result_$$.tmp"
        grep -"$option" "$arg" "$file" > "grep_result_$$.tmp"
        diff -s "s21_grep_result_$$.tmp" "grep_result_$$.tmp"
        rm -f "s21_grep_result_$$.tmp" "grep_result_$$.tmp"
        done
    done
done

echo "comparing combinations"
flags=(i v c l n h)
for ((i=0; i<${#flags[@]}; i++)); do
    for ((j=i+1; j<${#flags[@]}; j++)); do
        flag1=${flags[i]}
        flag2=${flags[j]}
        for file in test{1,2,3}.txt; do
            for arg in test TesT hh AA 123 ha; do
                echo "TEST $file, flags -$flag1 -$flag2, arg $arg"
                ./s21_grep -"$flag1" -"$flag2" "$arg" "$file" > "s21_grep_result_$$.tmp"
                grep -"$flag1" -"$flag2" "$arg" "$file" > "grep_result_$$.tmp"
                diff -s "s21_grep_result_$$.tmp" "grep_result_$$.tmp"
                rm -f "s21_grep_result_$$.tmp" "grep_result_$$.tmp"
            done
        done
    done
done
