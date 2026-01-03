#!/bin/bash

while read -r link; do
	if [[ -L "$link" ]] && [[ ! -e "$link" ]]; then
		echo "Broken link: $link"
	fi
done < <(find dir -type l)

# -e returns false if the target to which the link points to does not exist
# -L checks if its a symbolic link
