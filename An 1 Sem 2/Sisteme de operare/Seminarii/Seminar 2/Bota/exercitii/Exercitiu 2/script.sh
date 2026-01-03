#!/bin/bash

if [ $# -eq 0 ]; then
	echo "Usage: $0 <filename1> <filename2> .."
	exit 1
fi

for arg in $@
do
	if test -f $arg 
	then
		echo "$arg e fisier!"
		echo "Numar de caractere: $(awk '{print $0}' $arg | wc -m)"
		echo "Numarul de linii: $(awk 'END{print NR}' $arg)"
	elif test -d $arg
	then
		echo "$arg e director!"
		echo "Numarul de fisiere continute: $(find $arg -type f | wc -l)"
	else
		echo "Habar nu am.."
	fi
done
