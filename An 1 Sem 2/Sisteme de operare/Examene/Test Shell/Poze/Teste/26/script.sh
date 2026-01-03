#!/bin/bash

if [[ $# -ne 1 ]]; then
	echo "Usage: $0 <arg>"
	exit 1
fi

if [[ ! -d $1 ]]; then
	echo "Argument must be a directory"
	exit 2
fi

total=0

while read -r file; do
	if file "$file" | grep -q "C source"; then
		if echo "$file" | grep -Eq ".*\.c$"; then
			echo $file
		else
			linii=$(wc -l < "$file")
			total=$((linii + total))
		fi
	fi
done < <(find "$1" -type f)

echo "$total"
