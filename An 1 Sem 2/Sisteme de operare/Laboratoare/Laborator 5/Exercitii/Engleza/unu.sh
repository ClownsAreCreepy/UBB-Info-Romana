#!/bin/bash

if [[ $# -ne 1 ]]; then
	echo "Usage: $0 <arg>"
	exit 1
fi

if [[ ! -d $1 ]]; then
	echo "Argument must be a directory"
	exit 2
fi

find $1 -type f -name "*.c" | grep -c "."
