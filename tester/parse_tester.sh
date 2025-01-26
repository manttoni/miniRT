#!/bin/bash

if [[ -z "$1" ]]; then
    echo "Usage: $0 <input_file>"
    exit 1
fi

tests="$1"

if [[ ! -f "$tests" ]]; then
    echo "Error: File '$tests' not found."
    exit 1
fi

# file has to end with a newline, otherwise last line can't be read
if [[ $(tail -c1 "$tests") != "" ]]; then
    echo "" >> "$tests"
fi

# make a program that tries to parse an object specified by a line in the file
make

# it sorts the inputs into these files
>valid.txt
>invalid.txt

valgrind_log=valgrind_log.txt

while read line; do
    echo "------------------------"
    echo -e "test input: $line\n"

    valgrind -q --leak-check=full --log-file=$valgrind_log ./testmain "$line"
    exit_code=$?
    if [[ $exit_code -eq 0 ]]; then
        echo "$line" >> valid.txt 
    else
        echo "$line" >> invalid.txt
    fi
done < "$tests"

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