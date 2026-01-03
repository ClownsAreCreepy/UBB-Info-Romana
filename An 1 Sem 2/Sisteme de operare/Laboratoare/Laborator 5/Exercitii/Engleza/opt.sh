#!/bin/bash

filename=""

while read -rp "Enter a file: " filename; do
	if file $filename | grep -q "text"; then  			
       		sed -n '1p' $filename | wc -w
	fi
	if [[ $filename == "stop" ]]; then
		break
	fi
done
