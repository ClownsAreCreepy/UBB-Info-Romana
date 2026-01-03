#!/bin/bash

if [[ $# -ne 1 ]]; then
	echo "Usage: $0 <arg>"
	exit 1
fi

if [[ ! -d $1 ]]; then
	echo "Argument must be a directory"
	exit 2
fi

prev=$(ls -l $1)

while true; do
	state=$(ls -l $1)
	if [[ $prev != $state ]]; then
		echo "!!"
	fi
	prev=$state
	sleep 1
done
