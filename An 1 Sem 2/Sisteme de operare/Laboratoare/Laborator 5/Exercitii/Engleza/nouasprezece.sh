#!/bin/bash

if [[ $# -eq 0 ]]; then
	echo "Usage: $0 <arg>"
	exit 1
fi

if [[ ! -f "$1" ]]; then
	echo "Argument must be a file!"
	exit 2
fi

while read -r user; do
	echo "$user"
	string="${string},${user}@scs.ubbcluj.ro"
done < "$1"

echo "$string" | sed 's/^,//'
