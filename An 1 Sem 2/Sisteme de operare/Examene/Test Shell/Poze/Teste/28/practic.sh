#!/bin/bash
if [ $# -eq 0 ]; then
	echo "Numar insuficient de argumente."
	echo "Utilizare: $0 <arg1> <arg2> <arg3> <arg4> ..."
	exit 1
fi

read -rp "Introduceti cuvantul care se va modifica: " replaced
read -rp "Introduceti cuvantul cu care se va face modificarea: " replacement

for file; do
	if [ -f "$file" ]; then
		echo "Fisier: $(basename $file)"
		if file "$file" | grep -q "text"; then


			vocale=$(grep -Eoi "[aeiou]" "$file" | wc -l)
			consoane=$(grep -Eoi "[qwrtypasdfghjklzxcvbnm]" "$file" | wc -l)
			echo "Vocale/Consoane: $vocale/$consoane"

			sed -Ei "2~2 s/$replaced/$replacement/" "$file"
			echo 
		else
			echo "Fisierul dat nu e de tip text"
		fi
	fi
done
