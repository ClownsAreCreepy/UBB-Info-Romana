#!/bin/bash

# Verificam sa avem un singur argument
if [[ $# -ne 1 ]]; then
	echo "Usage: $0 <arg>"
	exit 1
fi

# Verificam ca argumentul sa fie un director valid
if ! [[ -d $1 ]]; then
	echo "Argument must be a valid directory!"
	exit 2
fi

# Aici putem face in mai multe feluri:
# Metoda 1: find basic + stat
# Folosim for ca altcumva are trebui sa avem un read intr-un while read => sus
for file in $(find "$1" -type f); do

	# stat -c %a ia exact permisiunile fisierului
	perms=$(stat -c %a "$file")

	if [[ "$perms" == "755" ]]; then

# Metoda 2: filtram permisiunile direct in find
#for file in $(find "$1" -type f -perm 755); do

		# Luam doar numele fara sufixe
		echo -n "Modify permissions for $(basename "$file")? (y/n): "
		read -r answer

		# Modificam permisiunile fisierului
		# --verbose iti spune ce modificari a realizat
		if [[ "$answer" == "y" || "$answer" == "Y" ]]; then
			chmod --verbose 744 "$file"
		fi
	fi
done
