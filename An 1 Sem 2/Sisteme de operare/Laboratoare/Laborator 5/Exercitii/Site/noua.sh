#!/bin/bash

# get all files recursively, compute checksum and path (\; means we execute for each file found, + means we do them all at once (and we do that, since md5sum can handle it))
find dir -type f -exec md5sum {} \; | sort -u > TEMP_sums.txt

# print checksums that appear more than once
awk '{count[$1]++} END {for (sum in count) if (count[sum]>1) print sum}' TEMP_sums.txt > TEMP_dupes.txt

while read -r sum; do
    echo "== Files with checksum $sum =="
    grep "^$sum" TEMP_sums.txt | awk '{$1=""; print}'
    echo
done < TEMP_dupes.txt

