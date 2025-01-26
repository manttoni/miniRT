#!/bin/bash

make
>valid.txt
>invalid.txt
man_tests=input.txt
valgrind_log=valgrind_log.txt
#gen_tests=generated.txt

while read -r line; do

    echo "------------------------"
    echo "test input: $line"
    echo ""

    valgrind -q --leak-check=full --log-file=$valgrind_log ./testmain "$line"
    exit_code=$?
    if [[ $exit_code -eq 0 ]]; then
        echo "$line" >> valid.txt 
    else
        echo "$line" >> invalid.txt
    fi
done < $man_tests

echo "------------------------"

echo -n "Valid inputs: "
cat valid.txt | wc -l
cat valid.txt

echo "------------------------"

echo -n "Invalid inputs: "
cat invalid.txt | wc -l
cat invalid.txt

echo "------------------------"

make clean
rm -f valid.txt
rm -f invalid.txt