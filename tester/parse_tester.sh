#!/bin/bash

# Check if a file was provided as an argument
if [[ -z "$1" ]]; then
    echo "Usage: $0 <input_file>"
    exit 1
fi

# Assign the input file from the first argument
tests="$1"

# Ensure the input file exists
if [[ ! -f "$tests" ]]; then
    echo "Error: File '$tests' not found."
    exit 1
fi

# Ensure the input file ends with a newline
if [[ $(tail -c1 "$tests") != "" ]]; then
    echo "" >> "$tests"
fi

make
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