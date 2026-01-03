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

while read -r file; do
	nr_lines=$(grep -Ec "[^ ]+" $file)
	((total += nr_lines))
done < <(find $1 -maxdepth 1 -type f -name "*.c")

echo "Total: $total"
