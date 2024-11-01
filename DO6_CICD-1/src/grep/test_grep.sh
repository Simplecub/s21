#!/bin/bash
DIFF_RES=0

echo "comparing single flags"
for file in  test1.txt test2.txt test3.txt; do
    for option in i v c l n h ; do
        for arg in test TesT hh AA 123 ha; do
        echo "TEST ${file}, option -${option}, arg ${arg}"
        ./s21_grep -"${option}" "${arg}" "${file}" > "s21_grep_result_$$.tmp"
        grep -"${option}" "${arg}" "${file}" > "grep_result_$$.tmp"
        diff -rup "s21_grep_result_$$.tmp" "grep_result_$$.tmp"
         status=$?
         [ $status -ne 0 ] && DIFF_RES="FAIL"
        rm -f "s21_grep_result_$$.tmp" "grep_result_$$.tmp"
        done
    done
done

echo "comparing combinations"
flags=(i v c n h)
for ((i=0; i<${#flags[@]}; i++)); do
    for ((j=i+1; j<${#flags[@]}; j++)); do
        flag1=${flags[i]}
        flag2=${flags[j]}
        for file in   test1.txt test2.txt test3.txt; do
            for arg in test TesT hh AA 123 ha; do
                echo "TEST ${file}, flags -${flag1} -${flag2}, arg ${arg}"
                ./s21_grep -"${flag1}" -"${flag2}" "${arg}" "${file}" > "s21_grep_result_$$.tmp"
                grep -"${flag1}" -"${flag2}" "${arg}" "${file}" > "grep_result_$$.tmp"
                diff -rup "s21_grep_result_$$.tmp" "grep_result_$$.tmp"
         status=$?
         [ $status -ne 0 ] && DIFF_RES="FAIL"
                rm -f "s21_grep_result_$$.tmp" "grep_result_$$.tmp"
            done
        done
    done
done

echo "comparing flag -e"
./s21_grep -e test -e TEST -e hh -e AA -e 123 test1.txt > "s21_grep_result_$$.tmp"
grep -e test -e TEST -e hh -e AA -e 123 test1.txt > "grep_result_$$.tmp"
diff -rup "s21_grep_result_$$.tmp" "grep_result_$$.tmp"
 status=$?
         [ $status -ne 0 ] && DIFF_RES="FAIL"
        rm -f "s21_grep_result_$$.tmp" "grep_result_$$.tmp"

echo "comparing flag -e with few files"
./s21_grep -e test -e TEST -e hh -e AA -e 123 test1.txt test2.txt test3.txt > "s21_grep_result_$$.tmp"
grep -e test -e TEST -e hh -e AA -e 123 test1.txt test2.txt test3.txt > "grep_result_$$.tmp"
diff -rup "s21_grep_result_$$.tmp" "grep_result_$$.tmp"
 status=$?
         [ $status -ne 0 ] && DIFF_RES="FAIL"
        rm -f "s21_grep_result_$$.tmp" "grep_result_$$.tmp"

echo "comparing using flag -f and flag -e with few files"
./s21_grep -f pattern.txt -e AA -e 123 test1.txt test2.txt test3.txt > "s21_grep_result_$$.tmp"
grep -f pattern.txt -e AA -e 123 test1.txt test2.txt test3.txt > "grep_result_$$.tmp"
diff -rup "s21_grep_result_$$.tmp" "grep_result_$$.tmp"
 status=$?
         [ $status -ne 0 ] && DIFF_RES="FAIL"
        rm -f "s21_grep_result_$$.tmp" "grep_result_$$.tmp"

echo "comparing flag -o"
./s21_grep -o test test1.txt test2.txt test3.txt > "s21_grep_result_$$.tmp"
grep -o test test1.txt test2.txt test3.txt > "grep_result_$$.tmp"
diff -rup "s21_grep_result_$$.tmp" "grep_result_$$.tmp"
 status=$?
         [ $status -ne 0 ] && DIFF_RES="FAIL"
        rm -f "s21_grep_result_$$.tmp" "grep_result_$$.tmp"


echo "comparing using -f with -n"
./s21_grep -f pattern.txt -n  test1.txt test2.txt test3.txt > "s21_grep_result_$$.tmp"
grep -f pattern.txt -n  test1.txt test2.txt test3.txt > "grep_result_$$.tmp"
diff -rup "s21_grep_result_$$.tmp" "grep_result_$$.tmp"
 status=$?
         [ $status -ne 0 ] && DIFF_RES="FAIL"
        rm -f "s21_grep_result_$$.tmp" "grep_result_$$.tmp"

echo "comparing -s"
./s21_grep -s test test1.txt > "s21_grep_result_$$.tmp"
grep -s test test1.txt > "grep_result_$$.tmp"
diff -rup "s21_grep_result_$$.tmp" "grep_result_$$.tmp"
 status=$?
         [ $status -ne 0 ] && DIFF_RES="FAIL"
        rm -f "s21_grep_result_$$.tmp" "grep_result_$$.tmp"



if [ $DIFF_RES != 0 ]
then
    echo "FAIL"
    exit 1
else 
echo "Success, no differences"
exit 0
fi
