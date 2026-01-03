#!/bin/bash

if [[ $# -eq 0 ]]; then
	echo "Usage: $0 <arg1> <arg2> <arg3> .."
	exit 1
fi

while [[ $# -ne 0 ]]; do 
	if file $1 | grep -q "C source"; then
		grep -Eo "#include\s<.*\.h>" $1
	fi
	shift
done | sort -u > "dir/includes.txt"
