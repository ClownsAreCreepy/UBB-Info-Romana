#!/bin/bash


#verificam sa fie exact un argument
if [ $# -ne 1 ]; then
	echo "Usage: $0 <filename>"
       	exit 1
fi

input_file="$1"

#verificam ca fisierul sa existe
if [ ! -f $input_file ]; then
	echo "Error: File '$input_file' not found!"
	exit 2
fi

awk 'BEGIN {
printf "Nume\t\t\tPrenume\t\tData nasterii\tTelefon\t\tSalariu\n"
printf "----------------------------------------------------------------------------------\n"} 

{printf "%s   \t\t%s    \t%s\t%s\t%s\n", $2, $1, $3, $4, $5}

END {
printf "----------------------------------------------------------------------------------\n"
printf "Numarul total de angajati: %d\n", NR}' $input_file 
