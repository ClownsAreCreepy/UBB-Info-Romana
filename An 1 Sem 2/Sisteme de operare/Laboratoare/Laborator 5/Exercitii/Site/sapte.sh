#!/bin/bash

fisier=$(cat $1)
output=""

for thing in $fisier; do
	nume_curent=$(echo $thing | sed 's/.*/&@scs.ubbcluj.ro/');
	output="${output}${nume_curent},"
done



echo "${output:0:${#output}-1}"
