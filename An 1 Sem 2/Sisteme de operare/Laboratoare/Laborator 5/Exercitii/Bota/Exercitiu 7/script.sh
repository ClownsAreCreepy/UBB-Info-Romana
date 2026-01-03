#!/bin/bash

# Verificam sa fie cel putin un argument
if [[ $# -eq 0 ]]; then
	echo "Usage: $0 <arg1> <arg2> <arg3> .. <argN>"
	exit 1
fi

# Verificam ca toate argumentele date sa fie fisiere valide
for arg in "$@"; do
	if ! [[ -f "$arg" ]]; then
		echo "All arguments must be valid filenames!"
		exit 2
	fi
done

# Citim doua cuvinte de la tastatura (punem -r pentru a avea si backslash)
read -r replaced
read -r replacement


# Schimbam in fiecare fisier cuvintele
for file in "$@"; do
	# Folosim sed -i pentru a modifica continutul fisierului
	sed -i "s/"$replaced"/"$replacement"/g" "$file"
done
