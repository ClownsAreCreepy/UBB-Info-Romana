#!/bin/bash


while read -r user; do
	ip=$(grep -E "^$user" dir/last.fake | awk '{print $3}')
	if [ -n "$ip" ]; then
		echo "$ip" | sort -u > "dir/for_21/$user"
	fi
done < <(awk -F: '{print $1}' dir/passwd.fake | sort -u)
