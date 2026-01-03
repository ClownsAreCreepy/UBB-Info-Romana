#!/bin/bash

awk '{print $1}' who.fake | while read -r user; do
	aparitii=$(grep "^$user" ps_1.fake | wc -l)
	echo "$user $aparitii"
done


