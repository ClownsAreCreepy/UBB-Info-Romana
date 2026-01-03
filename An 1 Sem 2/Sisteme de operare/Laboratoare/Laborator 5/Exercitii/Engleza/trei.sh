#!/bin/bash

if [[ $# -ne 1 ]]; then
	echo "Usage: $0 <arg>"
	exit 1
fi

if [[ ! -d $1 ]]; then
	echo "Argument must be a directory!"
	exit 2
fi

total=0

for file in $(find $1 -type f -name "*.c"); do
	nr_lines=$(grep -Ec "[^\s]+" $file)
	((total += nr_lines))
done

echo "Total: $total"
