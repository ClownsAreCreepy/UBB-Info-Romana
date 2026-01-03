#/bin/bash

if [ $# -ne 1 ]
then
	echo "Usage: $0 <folder>"
	exit 1
fi

if [ ! -d $1 ]
then
	echo "Parameter must exist and be a folder!"
	exit 2
fi

for fila in $(find $1 -type f -perm 755); do
	
	read -p "Change permissions from 755 to 744? (y,n)" answer

	if [ "$answer" = "y" ] || [ "answer" = "Y" ]
	then
		chmod 744 $fila
		echo "Changed for $(basename $fila)"
	else
		echo "Skipped"
	fi
	echo ""
done
