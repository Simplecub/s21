#!/bin/sh
DIFF_RES=0


for file in test1.txt test2.txt test3.txt; do
    for option in b e n s t v; do
        echo "TEST $file, option $option"
        ./s21_cat -"$option" "$file" > "s21_cat_result_$$.tmp"
        cat -"$option" "$file" > "cat_result_$$.tmp"
         diff -rup "s21_cat_result_$$.tmp" "cat_result_$$.tmp" 
         status=$?
         [ $status -ne 0 ] && DIFF_RES="FAIL"

        rm -f "s21_cat_result_$$.tmp" "cat_result_$$.tmp" 
    done
done

if [ $DIFF_RES != 0 ]
then
    echo "FAIL"
    exit 1
else 
echo "Success, no differences"
exit 0
fi

