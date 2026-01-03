#!/bin/bash

if [[ $# -eq 0 ]]; then
	echo "Numar insuficient de argumente"
	echo "Utilizare: $0 fisier_comenzi fisier_propozitii"
	exit 1
fi

while read -r command; do
	if echo "$command" | grep -q "^INSERT LINE"; then
		line_nr=$(echo "$command" | awk '{print $3}')
		line=$(echo "$command" | awk '{print $4}')

		sed -Ei "${line_nr}i $line" "$2"

	elif echo "$command" | grep -q "^REPLACE CHAR"; then
		to_be_replaced=$(echo "$command" | awk '{print $3}')
		replacement=$(echo "$command" | awk '{print $4}')

		if [[ -z "$replacement" ]]; then
			replacement=" "
		fi

		sed -Ei "s/$to_be_replaced/$replacement/g" "$2"

	elif echo "$command" | grep -q "^REPLACE WORD"; then
		to_be_replaced=$(echo "$command" | awk '{print $3}')
		replacement=$(echo "$command" | awk '{print $4}')

		if [[ -z "$replacement" ]]; then
			replacement=" "
		fi

		sed -Ei "s/$to_be_replaced/$replacement/g" "$2"

	elif echo "$command" | grep -q "^APPEND LINE"; then
		line=$(echo "$command" | awk '{print $3}')

		sed -Ei "\$a $line" "$2"

	fi
done < <(cat "$1")
