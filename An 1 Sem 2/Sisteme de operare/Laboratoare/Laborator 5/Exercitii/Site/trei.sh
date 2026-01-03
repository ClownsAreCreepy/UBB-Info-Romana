#!/bin/bash

while read -r file; do
	sort "$file" > "${file}_sorted.log"
	rm "$file"
	mv "${file}_sorted.log" "$file"
#sau
       #sort "$file" -o "$file"
done < <(find dir -type f -name "*.log")
