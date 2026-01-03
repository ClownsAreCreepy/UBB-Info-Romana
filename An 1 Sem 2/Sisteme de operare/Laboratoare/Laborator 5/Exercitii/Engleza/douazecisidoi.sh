#!/bin/bash

if [ $# -eq 0 ]; then
	users=$(ps -ef | grep -v "UID" | awk '{print $1}' | sort -u)
else
	users="$@"
fi

while :; do
	echo New iteration:
	for user in $users; do
		nr=$(ps -ef | grep -Ec "^$user")
		echo "$nr : for $user"
	done | sort -rn
	sleep 1
	echo
done
