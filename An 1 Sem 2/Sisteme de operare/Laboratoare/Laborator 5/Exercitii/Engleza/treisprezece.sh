#!/bin/bash

while read -r link; do
	if [[ ! -e "$link" ]]; then
		echo "Link $link is not valid"
	fi
done < <(find "$1" -type l)
