#!/bin/bash

if [[ $# -eq 0 ]]; then
	echo "Usage: $0 <arg1> <arg2> <arg3> <arg4>"
	exit 1
fi

if (( $# % 2 != 0)); then
	echo "Arguments must be in pairs!"
	exit 2
fi

while [[ $# -ne 0 ]]; do
	nr_aparitii=$(grep -Eo "$2" "$1" | wc -l)
	if [[ $nr_aparitii -ge 3 ]]; then
		echo "\"$2\" apare de 3 sau mai multe ori in $1"
	else
		echo "\"$2\" NU apare de 3 sau mai multe ori in $1"
	fi
	shift 2
done
