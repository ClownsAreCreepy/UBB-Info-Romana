#!/bin/bash

input_file="$1"

#1
echo "Frecvența numelor imaginilor: "
awk '{count[$2]++} END {
	for (img in count) 
		print img, 
		count[img]
	}' "$input_file"

#2
echo -e "\nMedia CPU: "
awk '{sum+=$9; count++} END{
	if (count > 0) 
		print sum/count; 
	else 
		print "0"
	}' "$input_file"

#3
echo -e "\nNumarul de IP-uri care incept cu 120 si se termia cu .10: "
awk '{print $4}' "$input_file" |  grep -E "^120\..*\.10$" | wc -l   
