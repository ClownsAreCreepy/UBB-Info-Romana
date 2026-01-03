#!/bin/bash

#verificam sa existe un singur argument
if [ $# -ne 1 ]; then
	echo "Usage: $0 <filename>"
	exit 1
fi


input_file="$1"


#Verificam daca fisierul exista
if [ ! -f "$input_file" ]; then
	echo "Error: File '$input_file' not found!"
	exit 2
fi


#Insereaza deasupra primei linii textul 'DATE DESPRE PERSONAL'
sed '1i DATE DESPRE PERSONAL' $input_file |


#Sterge salariile care se termina cu 49
#sed -E 's/[0-9]+49$//' |
#Sterge liniile care au salarii care se termian cu 49
sed -E '/[0-9]+49$/d' |

#Tipareste continutul fisierului cu numele angajatului pe prima pozitie si prenumele pe a doua pozitie
sed -E 's/^([A-Za-z]+) ([A-Za-z]+)/\2 \1/' |

#Adauga la sfarsitul fisierului textul 'TERMINAT'
sed '$a TERMINAT'
