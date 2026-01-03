#!/bin/bash

sed '1d' df.fake | awk '$2 < 1024 || $5 < 20 {print $6}'
