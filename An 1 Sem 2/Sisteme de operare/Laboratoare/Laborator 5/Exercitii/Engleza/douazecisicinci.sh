#!/bin/bash

if [ $# -eq 0 ]; then
	echo "Usage: $0 <arg1> <arg2> <arg3> ..."
	exit 1
fi

for arg; do
	if [ -d "$arg" ]; then
		name=`basename "$arg"`
		ls -ld "$arg" > "$arg/$name.info"
	elif [ -f "$arg" ]; then
		head "$arg"
	else
		echo "Nigga what is this $arg"
	fi
done
