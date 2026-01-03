#!/bin/bash

# Verificam sa avem un singur argument
if [[ $# -ne 1 ]]; then
	echo "Usage: $0 <arg>"
	exit 1
fi

# Verificam ca argumentul sa fie un director
if ! [[ -d $1 ]]; then
	echo "Argument must be a valid directory!"
	exit 2
fi

# Mergem prin toate fisierele din director
for file in $(find $1 -type f); do
	
	# Luam lungimea numelui cu wc -c
	# Folosim basename pentru a elimina directoarele si sufixele din numele fisierelor
	name_length=$(echo "$(basename $file)" | wc -c)

	# Scadem cu 1 pentru a elimina /0
	((name_length--))
	
	if [[ $name_length -lt 8 ]]; then
		echo "$file"

		# Daca e fisier text, tiparim primele 10 linii
		if file $file | grep -q "text"; then
			head $file
		fi

		echo ""
	fi

done
