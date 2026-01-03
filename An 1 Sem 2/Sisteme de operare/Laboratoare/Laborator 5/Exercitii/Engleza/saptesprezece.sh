#!/bin/bash

if [[ $# -eq 0 ]]; then
	echo "Usage: $0 <arg>"
	exit 1
fi

if [[ ! -d $1 ]]; then
	echo "Argument must be a directory!"
	exit 2
fi

i=0

while read -r file; do
	if echo "$file" | grep -Eq ".*\.c"; then
		((i++))
		#rm $file
	elif file "$file" | grep -q "text"; then
		echo "$(basename $file)"
	fi
done < <(find $1 -type f) | sort  
