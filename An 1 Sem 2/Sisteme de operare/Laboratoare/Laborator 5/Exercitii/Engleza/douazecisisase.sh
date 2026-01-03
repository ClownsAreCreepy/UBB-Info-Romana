#!/bin/bash

for dir; do
	if [ -d "$dir" ]; then
		while read -r thing; do
			if [ -d "$thing" ]; then
				files=$(ls -l "$thing")
				if [ -z "$files" ]; then
					echo "Empty dir: $thing"
				fi
			elif [ -f "$thing" ]; then
				if ! grep -Eqv "^\s*$" "$thing"; then
					echo "Empty file: $thing"
				fi
			fi
		done < <(find "$dir")
	fi
done
