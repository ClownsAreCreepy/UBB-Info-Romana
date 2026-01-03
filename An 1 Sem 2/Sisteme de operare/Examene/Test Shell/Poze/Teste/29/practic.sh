#!/bin/bash

if [ $# -eq 0 ]; then
	echo "Numar insuficient de argumente."
	echo "Utilizare: $0 file1 file2 ..."
	exit 1
fi

read -rp "Introducetii cuvantul: " word

for file; do
	if [ -f "$file" ]; then
		echo "Fisier: $(basename $file)"
		if file "$file" | grep -qw "text"; then

			total=$(grep -wc "$word" "$file")
			echo "Total linii: $total"
			
			paritate=$(( $total % 2 ))
			if [[ $paritate -eq 0 && $total -ne 0 ]]; then
				
				line=$(grep -w "$word" "$file" | tail -n 1)
				echo "$line" >> "$file"
				echo "Am adaugat o linie."
			fi
		else
			echo "Fisierul dat nu e de tip text"
		fi
	fi
done
