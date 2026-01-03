#!/bin/bash

if [ $# -eq 0 ]; then
	echo "Numar insuficient de argumente"
	echo "Utilizare: $0 fisier_comenzi"
	exit 1
fi

if [ ! -f "$1" ]; then
	echo "Argumentul trebuie sa fie un fisier valid!"
	exit 2
fi

while read -r line; do
	if echo "$line" | grep -q "^CREATE DIR";then
		dir=$(echo "$line" | awk '{print $3}')

		mkdir "$dir"
	
	elif echo "$line" | grep -q "^CREATE FILE";then
		file=$(echo "$line" | awk '{print $3}')

		touch "$file"

	elif echo "$line" | grep -q "^MOVE DIR";then
		obj=$(echo "$line" | awk '{print $3}')
		dest=$(echo "$line" | awk '{print $4}')

		mv "$obj" "$dest"
	
	elif echo "$line" | grep -q "^SET PERM";then
		file=$(echo "$line" | awk '{print $3}')
		perm=$(echo "$line" | awk '{print $4}')
	
		chmod "$perm" "$file"
	fi
done < "$1"
