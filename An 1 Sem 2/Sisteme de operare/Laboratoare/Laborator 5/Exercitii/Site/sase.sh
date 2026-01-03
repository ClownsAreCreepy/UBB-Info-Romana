#!/bin/bash

while read -r file; do
	#ls -l "$file" | awk '{print $1}'
	echo "$(ls -l $file | awk '{print $1}') $file"
	chmod o-w "$file"	
	echo "$(ls -l $file | awk '{print $1}') $file"
done < <(find ~/fisiere_pentru_lab5_site_sase -type f -perm -002)

#punem -002 ca sa aratam ca vrem CEL PUTIN 002

#generam permisiuni for reload

find ~/fisiere_pentru_lab5_site_sase -type f | while read -r file; do
    # generate random permissions between 000 and 777
    r=$(( RANDOM % 8 ))
    g=$(( RANDOM % 8 ))
    o=$(( RANDOM % 5 ))
    perm="${r}${g}${o}"

    chmod "$perm" "$file"
done

