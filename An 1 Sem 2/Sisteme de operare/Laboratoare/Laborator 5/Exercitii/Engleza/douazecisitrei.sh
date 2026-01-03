#!/bin/bash

dir="."
if [ $# -eq 1 ]; then
	dir="$1"
fi

while read -r file; do
	if file "$file" | grep -q "text";then
		filesize=$(ls -l "$file" | awk '{print $5}')
		permissions=$(ls -l "$file" | awk '{print $1}' | sed 's/-//')
		nr_unique=$(sort "$file" | uniq -u | wc -l)

		echo "For $(basename $file) we have size $filesize, permissions $permissions, with $nr_unique unique lines"
	fi
done < <(find "$dir" -maxdepth 1 -type f)
