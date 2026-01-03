#!/bin/bash

if [[ $# -eq 0 ]]; then
	echo "Usage: $0 <arg1> <arg2> <arg3> .."
	exit 1
fi

while [[ $# -ne 0 ]]; do
	user=$(grep -E "^$1:" passwd.fake)
	if [[ -n $user ]]; then
		echo "$user" | awk -F: '{print $5}'
		if grep -q "^$1" who.fake;then
			grep "^$1" ps.fake | wc -l
		else
			last=$(grep -m 1 "^$1" last.fake)
			echo "$last" | awk '{print $7}'
			echo "$last" | awk '{print $3}'
			echo "$last" | awk '{print $NF}' | sed -E 's/[()]//g'
		fi
	fi

	if [[ -f "$1" ]]; then
		if ls -l "$1" | awk '{print $1}' | grep "rw.rw.rw"; then
			sed -Ei 's/-[0-9]+[.,]*[0-9]*/ERROR/g' $1
		fi
	fi

	if [[ -d "$1" ]]; then
		ls -ld $1 | awk '{print $5}'
	fi

	echo ""
	echo ""
	shift
done
