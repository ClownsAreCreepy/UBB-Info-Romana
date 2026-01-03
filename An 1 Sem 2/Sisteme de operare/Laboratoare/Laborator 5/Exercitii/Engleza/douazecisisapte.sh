#!/bin/bash

for arg; do
	if [ -d "$arg" ]; then
		while read -r x; do
			if [ -d "$x" ]; then
				if ls $x | grep -q "."; then
					echo "Directory contains files: $x"
				fi
			fi

			if [ -f "$x" ]; then
				nr=`grep -Ec "^.+$" "$x"`
				if [ $nr -ge 10 ]; then
					echo "File with at least 10 lines: $x"
				fi
			fi
		done < <(find "$arg")
	fi
done
