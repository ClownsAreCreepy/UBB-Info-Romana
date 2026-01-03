#!/bin/bash

if [[ $# -ne 3 ]]; then
	echo "Usage: $0 <arg1> <arg2> <arg3>"
	exit 1
fi

if [[ ! -d $1 ]]; then
	echo "First argument must be a directory!"
	exit 2
fi

if [[ ! $2 =~ ^[1-9][0-9]*$ ]]; then
	echo "Third argument must be a number!"
	exit 3
fi

while read -r file; do
	details=$(ls -l $file)
	owner=$(echo "$details" | awk '{print $3}')
	size=$(echo "$details" | awk '{print $5}')

	if [[ $owner == $3 && $size -lt $2 ]]; then
		cuvinte=$(sed -E 's/[,.!?:;"()+=-\\/\#<>]/ /g' $file | sed -E 's/ /\n/g')
		rezultat=$(echo "$cuvinte" | grep -Ev "^[ ]*$" | sort | uniq -c | sort -rn | head | awk '{print $2}')

		echo "For $file: Top 10 most used words:"
		echo -e "$rezultat"
		echo ""
		echo ""
	fi
done < <(find $1 -type f)
