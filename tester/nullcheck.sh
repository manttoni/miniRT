#!/bin/bash
vfile=tester/logs/valgrind.log
> $vfile
cd ..
for file in sources/*; do
  if [ -f "$file" ]; then
    echo $file >> $vfile
    i=0
    # Process the file, line by line
    while IFS= read -r line; do
        ((i++))
        if echo "$line" | grep -q "malloc("; then
            echo "-----" >> $vfile
            echo "$i: $line" >> $vfile
            # Temporarily modify malloc to NULL;///
            sed -i 's/malloc(/NULL;\/\//' "$file"
            make
            ./valrun.sh rt_files/test.rt >> $vfile 2>&1
            # Restore malloc after testing
            sed -i 's/NULL;\/\//malloc(/' "$file"
        fi
    done < "$file"
  fi
done
for file in libft/sources/*/*; do
  if [ -f "$file" ]; then
    echo $file >> $vfile
    i=0
    # Process the file, line by line
    while IFS= read -r line; do
        ((i++))
        if echo "$line" | grep -q "malloc("; then
            echo "-----" >> $vfile
            echo "$i: $line" >> $vfile
            # Temporarily modify malloc to NULL;///
            sed -i 's/malloc(/NULL;\/\//' "$file"
            make re
            ./valrun.sh rt_files/test.rt >> $vfile 2>&1
            # Restore malloc after testing
            sed -i 's/NULL;\/\//malloc(/' "$file"
        fi
    done < "$file"
  fi
done