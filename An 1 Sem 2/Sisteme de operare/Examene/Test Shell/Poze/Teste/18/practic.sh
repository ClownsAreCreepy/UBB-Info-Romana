#!/bin/bash

if [[ $# -eq 0 ]]; then
	echo "Numar insuficient de argumente"
	echo "Utilizare: $0 fisier_date"
	exit 1
fi


while read -r data; do
	zi=$(echo "$data" | awk '{print $1}')
	luna=$(echo "$data" | awk '{print $2}')
	ora=$(echo "$data" | awk '{print $3}' | sed 's/\./:/')

	usernames=""
	while read -r user; do
		current=$(echo "$user" | awk '{print $1}')
		usernames="$usernames\n$current"
		
		info=$(grep -E "^$current" passwd.fake)
	
		grupa=$(echo "$info" | awk -F: '{print $6}' | grep -Eo "/gr[0-9]{3}/" | sed -E 's_/gr([0-9]+)/_\1_g')
		nume=$(echo "$info" | awk -F: '{print $5}')

		echo "$nume" >> ${grupa}.txt

	done < <(cat last.fake | grep -E "$luna\s+$zi\s+$ora[^)]")
	
	usernames_format=$(echo -e "$usernames" | sed '1d')
	echo "In data $data s-au gasit" 
	echo "$usernames_format"
	
	echo ""
	echo "Deci, avem"
	echo "Data: $zi $luna"
	echo "Orele: $ora"
	echo "Total studenti: $(echo "$usernames_format" | wc -l) "
	echo ""
	echo "======================================================================================"
	echo ""

done < <(cat $1)
