#!/bin/bash

if [[ $# -eq 0 ]]; then
	echo "Usage: $0 <arg1> <arg2> <arg3> .."
	exit 1
fi

while :; do
	echo "Monitoring..."
	for name in $@; do 
		while read -r line; do
			uid=$(echo "$line" | awk '{print $1}')	
			pid=$(echo "$line" | awk '{print $2}')
			cmd=$(echo "$line" | awk '{print $NF}')
			if echo "$line" | grep -q "\<$name"; then
				kill -9 $pid
				echo "ELIMINATED PROCESS FROM UID $uid WITH CMD $cmd"
			fi
		done < <(sed "1d" dir/ps.fake)
	done
done
