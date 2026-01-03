#!/bin/bash

count=0

while read -r user_pid; do
	name=$(echo "$user_pid" | cut -d, -f1)	
	pid=$(echo "$user_pid" | cut -d, -f2)
	if [[ $name != $prev ]]; then
		if [[ $count -gt 0 ]]; then
			echo "Average processes for user $prev is $((sum/count))"
		fi
		prev=$name
		sum=0
	fi
	((sum += pid))
	((count += 1))
done < <(awk 'NR > 1 {print $1","$2}' dir/ps.fake | grep -v "^[,]" | sort)
