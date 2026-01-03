#!/bin/bash

if [[ $# -ne 1 ]]; then
	echo "Usage: $0 <arg>"
	exit 1
fi

if [[ ! -d $1 ]]; then
	echo "Argument must be a directory!"
	exit 2
fi

all_files=$(find -type f -exec basename -a {} + | sort | uniq -c | awk '{print $1, $2}')
dup_files=$(echo "$all_files" | grep "^[^1]")

while read -r line; do
	nr=$(echo "$line" | awk '{print $1}')
	name=$(echo "$line" | awk '{print $2}')
	echo "$(($nr-1)) $name"
done < <(echo "$dup_files")
