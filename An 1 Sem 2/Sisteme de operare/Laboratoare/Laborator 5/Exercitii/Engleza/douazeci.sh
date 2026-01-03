#!/bin/bash

if [[ $# -eq 0 ]]; then
	echo "Usage: $0 <arg1> <arg2> <arg3> ..."
	exit 1
fi

declare -A words

for word in $@; do
	words[$word]=0
done

ok=1

while [[ $ok -ne 0 ]]; do
	read -r file
	
	if [[ ! -f "$file" ]]; then
		echo "$file is not a file!"
	else
		ok=0
		for word in $@; do
			if grep -Eq "\<$word\>" "$file"; then
				words[$word]=1
			fi

			if [[ ${words[$word]} -eq 0 ]]; then
				ok=1
			fi
		done
	
		for word in $@; do
			if [[ ${words[$word]} -eq 0 ]]; then
				echo "To find: $word"
			fi
		done
	fi


	echo ""
	echo ""
done
