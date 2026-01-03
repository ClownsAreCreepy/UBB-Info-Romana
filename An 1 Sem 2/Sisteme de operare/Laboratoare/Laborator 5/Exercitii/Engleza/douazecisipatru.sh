#!/bin/bash

if [[ $# -eq 0 ]]; then
	echo "Usage: $0 <arg1> <arg2> <arg3> <arg4> ..."
	exit 1
fi

if (( $# % 2 != 0 )); then
	echo "Arguments must be in pairs!"
	exit 2
fi

while [[ $# -ne 0 ]]; do
	a=$1
	b=$2

	if echo "$a" | grep -Eq "$b"; then
		echo "String $b is found in string $a"
	fi

	shift 2
done
