#!/bin/bash

if [[ $# -eq 0 ]]; then
	echo "Usage: $0 <arg1> <arg2> .. "
	exit 1
fi

while true; do
	for danger in "$@"; do
		echo "Monitoring for $danger"
		while read -r user pid rest; do
			if [[ "$rest" == *"$danger"* ]]; then
				echo "DANGEROUS PROGRAM DETECTED: $danger (PID $pid) - killing it!"
				kill -9 "$pid"
			fi
		done < <(cat ps_1.fake)
	sleep 2
	done
done	
