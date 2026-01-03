#!/bin/bash

string=""

while [[ ! -f "$string" ]]; do
	read -rp "Enter a string: " string
done
