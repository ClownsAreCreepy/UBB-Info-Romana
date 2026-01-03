#!/bin/bash


while read -r file; do
	echo "$file"

	chmod a-w "$file"
done < <(find . -type f  -perm -222)
