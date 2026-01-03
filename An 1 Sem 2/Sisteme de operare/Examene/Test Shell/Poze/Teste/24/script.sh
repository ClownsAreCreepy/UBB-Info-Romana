#!/bin/bash

if [[ $# -lt 2 ]]; then
	echo "Usage: $0 <arg1> <arg2> <arg3> ..."
	exit 1
fi

name=$1
shift

while [[ $# -ne 0 ]]; do
	if [[ -d "$1" ]]; then
		while read -r file; do
			nume=$(basename $file)
			if [[ $nume = $name ]]; then
				echo "$1"
				break
			fi
		done < <(find "$1" -type f -size 0)
	fi

	shift
done
