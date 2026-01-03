#/bin/bash

if [[ $# -ne 1 ]]; then
	echo "Usage: $0 <arg>"
	exit 1
fi

if [[ ! -d $1 ]]; then
	echo "Argument must be a directory!"
	exit 2
fi

sum=0

while read -r file; do
	if [[ -f $file ]]; then
		size=$(du -b $file| awk '{print $1}')
		((sum += size))
	fi
done < <(find $1 -maxdepth 1)

echo "Sum: $sum"
