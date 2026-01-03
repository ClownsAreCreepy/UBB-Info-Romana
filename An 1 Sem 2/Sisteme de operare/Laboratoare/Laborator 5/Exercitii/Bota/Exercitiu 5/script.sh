#!/bin/bash

# Verificam ca numarul de argumente primite este cel putin 1
if [ $# -eq 0 ]
then
	echo "Usage: $0 <arg1> <arg2> .. <argN>"
	exit 1
fi

# Parcurgem lista de argumente
for file in "$@"
do
	# Verificam daca argumentul este fisier
	if test -f "$file"
	then
		# Afisam numele, nr de caractere si nr de linii
		# Folosim grep -c . pentru a ne conforma la cerinta. In mod real ar fi mai bine wc -l deoarece grep -c . va sari peste linii goale
		echo -e "Fisier: "$file":\nNr caractere: $( wc -c < "$file")\nNr linii: $(grep -c "." "$file")\n"
	
	# Daca nu e fisier, verificam daca e director	
	elif test -d "$file"
	then
		# Numaram cate fisiere gaseste find-ul (nr de linii)
		count=$(find "$file" -type f | wc -l)

		# Afisam numele si nr de fisiere din director
		echo -e "Director: "$file":\nNr fisiere: $count\n"
	else
		echo -e ""$file": Habar nu am ce e asta :(\n"
	fi
done
