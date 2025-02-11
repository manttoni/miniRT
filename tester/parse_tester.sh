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
>out.log

valgrind_log=valgrind.log

len=$(wc -l < $tests)
i=1

while read line; do

	if [ -t 1 ]; then
		percent=$(( 100 * i / len ))
		echo -ne "[                        ]\r"
		echo -ne "           $percent%\r"
		echo -ne "[----------$percent%----------]" | head -c $((1 + percent * 24 / 100))
		echo -ne "\r"
		i=$((i + 1))
	fi

    if [[ -z "$line" || "$line" =~ ^[[:space:]]*$ ]]; then
        continue
    fi

    valgrind -q --leak-check=full --log-file=$valgrind_log ./testmain "$line" >> out.log
    exit_code=$?
    if [[ $exit_code -eq 0 ]]; then
        echo "$line" >> valid.txt 
    else
        echo "$line" >> invalid.txt
    fi
done < "$tests"

echo "--------------------------"

echo -n "valid.txt lines: "
cat valid.txt | wc -l

echo "--------------------------"

echo -n "invalid.txt lines: "
cat invalid.txt | wc -l

echo "--------------------------"


if [[ $(grep -c "L" valid.txt) -ne 1 ]]; then
    echo "Wrong amount of light"
fi
if [[ $(grep -c "C" valid.txt) -ne 1 ]]; then
    echo "Wrong amount of camera"
fi
if [[ $(grep -c "A" valid.txt) -ne 1 ]]; then
    echo "Wrong amount of ambient"
fi
if [[ $(grep -v "[LCA]" valid.txt | wc -l) -le 0 ]]; then
    echo "Wrong amount of objects"
fi


make clean