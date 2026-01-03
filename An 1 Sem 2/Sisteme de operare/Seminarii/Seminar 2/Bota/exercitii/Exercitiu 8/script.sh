#!/bin/bash

if [ $# -eq 0 ]
then
	echo "Usage: $0 <filename1> <filename2> .."
	exit 1
fi

linii=""

while [ $# -ne 0 ]
do
	if [ ! -f "$1" ]
	then
		echo "$1 nu e un fisier valid!"
		shift 1
		continue
	fi

	
	highest_freq=$(sort "$1" | uniq -c | sort -rn | head -n 1)
	
	freq=$(echo "$highest_freq" | awk '{print $1}')
	line=$(echo "$highest_freq" | sed -E 's/^[[:space:]]*[0-9]+[[:space:]]*//')

	linii="$linii$freq $1: $line"$'\n'

	shift 1
done

echo "$linii" | sort -rn
