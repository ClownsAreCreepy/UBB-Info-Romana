#!/bin/bash

sum=0

for arg; do
	if [ -f "$arg" ];then
		cuvinte=`echo "$arg" | grep -Eo "[^ ]*" | wc -l`
		sum=$((sum + cuvinte))
	fi
done

echo "$sum"
