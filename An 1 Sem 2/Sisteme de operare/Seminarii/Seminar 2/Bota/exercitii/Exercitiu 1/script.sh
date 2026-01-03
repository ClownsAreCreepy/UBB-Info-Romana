#!/bin/bash

if [ $# -ne 1 ]; then
	echo "Usage: $0 <argument>"
	exit 1
fi

if [[ ! $1 =~ [0-9]+ ]]; then
	echo "The argument must be a natural number!"
	exit 1
fi


for ((i=1;i<=$1;++i))
do
	sed -n "$i,$((i+5))p" passwd.fake > file_$i.txt
done
