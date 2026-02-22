#/bin/bash

if [ $# -ne 1 ]
then
	echo "Usage: $0 <folder>"
	exit 1
fi

dir="src/main/java/scs/$1"

if [ ! -d "$dir" ]
then
	echo "Parameter must exist and be a folder inside src/main/java/scs!"
	exit 2
fi

> package_file

find "$dir" -type f | while read -r file; do
  cat "$file" >> package_file
  echo "" >> package_file     # adds newline
done

# project is 8 000 lines of code long