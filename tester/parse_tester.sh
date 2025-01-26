#!/bin/bash

make
>valid.txt
>invalid.txt
man_tests=input.txt
#gen_tests=generated.txt

while read -r line; do
    input=$(echo -e "$line") # if line ends with '\n' (written out like that), it is now part of the input

    echo "------------------------"
    echo "test input: $input"
    echo "------------------------"

    valgrind -q --leak-check=full ./testmain "$input"
    exit_code=$?
    if [[ $exit_code -eq 0 ]]; then
        echo "$input" >> valid.txt 
    else
        echo "$input" >> invalid.txt
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