#!/bin/bash

#month=$(date | awk '{print $2}')
# In cazul nostru e doar martie
month="Mar"

users=$(grep "$month" last_1.fake)

each_user=$(echo "$users" | awk '{print $1}' | sort -u)

for user in $each_user; do
	echo "$(echo "$users" | grep -E "$user" | wc -l) - $user"
done | sort -nr
