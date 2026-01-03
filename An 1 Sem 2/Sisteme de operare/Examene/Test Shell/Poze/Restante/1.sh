#!/bin/bash

while read -r line; do
	cerere=$(echo "$line" | awk '{print $4}')
	#echo "$line" >> "$cerere.txt"
	cereri="$cerere\n$cereri"
done < "a.log"

for req in $(echo -e "$cereri" | sort -u); do
	nr_errors=$(grep -Ec "error $req" "a.log")
	echo "$nr_errors $req"
done | sort -rn

# Sau asa
#grep -Eo "error req[0-9]+" "a.log" | awk '{print $2}'| sort | uniq -c | sort -rn

