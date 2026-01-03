#!/bin/bash

if [[ $# -lt 2 ]]; then
	echo "Numar insuficient de argumente."
	echo "Utilizare: $0 rw- dir1 dir2 ..."
	exit 1
fi

permisiuni=$1
shift

while [[ $# -ne 0 ]]; do
	
	if [[ ! -d $1 ]]; then
		echo "Director: $1"
		echo "Directorul dat nu exista"
	else
		while read -r file; do
			perm=$(ls -l "$file" | awk '{print $1}' | sed -E 's/^-(...).*$/\1/')
			
			if [[ $perm == $permisiuni ]]; then
			
				cp "$file" "$file.bak"

				chmod 400 "$file.bak"

				echo "Permisiuni: $permisiuni"
				echo "Director: $1"
				echo " Fisier: $1"
				echo " Permisiuni: $(ls -l "$file" | awk '{print $1}')"
				echo " Copie: $file.bak"
				echo " Fisier: $(ls -l "$file.bak" | awk '{print $1}')"
				echo ""
			fi
		done < <(find $1 -maxdepth 1 -type f)
	fi
	echo ""
	shift
done
