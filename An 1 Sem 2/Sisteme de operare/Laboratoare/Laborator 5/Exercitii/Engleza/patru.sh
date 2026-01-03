#!/bin/bash

if [[ $# -eq 0 ]]; then
	echo "Usage: $0 <arg1> <arg2> .."
	exit 1
fi

while [[ $# -gt 0 ]]; do
	if [[ -f $1 ]]; then
		echo "$1 is a file"
	elif [[ -d $1 ]]; then
		echo "$1 is a directory"
	elif echo "$1" | grep -Eq "^[0-9]+$"; then
		echo "$1 is a number"
	else
		echo "Negro the hell is that"
	fi
	shift
done
