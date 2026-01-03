#!/bin/bash

if [[ $# -eq 0 ]]; then
	echo "Usage: $0 <arg1> <arg2> <arg3> .."
	exit 1
fi

while [[ $# -ne 0 ]]; do
	if [[ -e $1 ]]; then
		du -b $1
	fi	
	shift
done | sort -rn 
