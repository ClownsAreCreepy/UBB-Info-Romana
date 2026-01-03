#!/bin/bash

i=0
while read -r file; do
	nr_lines=$(wc -l < $file)
	if [[ $nr_lines -gt 500 ]]; then
		i=$(expr $i + 1)
		echo "$file"
	fi
	if [[ $i -ge 2 ]]; then
		break
	fi
done < <(find dir -type f -name *.c)
