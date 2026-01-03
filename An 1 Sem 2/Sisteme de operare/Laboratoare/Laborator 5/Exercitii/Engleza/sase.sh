#!/bin/bash

if [[ $# -eq 0 ]]; then
	echo "Usage: $0 <arg1> <arg2> .."
	exit 1
fi

for file in $@; do
	if [[ -f $file ]]; then
		du -b $file
	fi
done | sort -n
