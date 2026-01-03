#!/bin/bash

if [ $# -eq 0 ]; then
	echo "Usage: $0 <arg1> <arg2> <arg3> <arg4> ..." 
	exit 1
fi

directories=0
files=0
other=0

for input; do
	if [ -d "$input" ]; then
		max=0
		while read -r file; do
			size=$(ls -l "$file" | awk '{print $5}')
			
			if [ $size -gt $max ]; then
				max_file="$file"
				max="$size"
			fi
		done < <(find "$input" -type f)

		echo "In $input, the largest file is $max_file"
		((directories++))

	elif [ -f "$input" ]; then
		echo So the lines starting with capital letters in "$input" are:
		sort "$input" | grep -E "^[A-Z]"
		((files++))
	else
		echo "Nigga the hell is $input?"
		((other++))
	fi
	echo
	echo
done

perc_d=$(( ($directories * 100) / $# ))
perc_f=$(( ($files * 100) / $# ))
perc_o=$(( ($other * 100) / $# ))

echo "Total input: Directories: $perc_d%, Files: $perc_f%, Other: $perc_o%"

