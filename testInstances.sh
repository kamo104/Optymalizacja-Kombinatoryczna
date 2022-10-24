#!/bin/bash

# arg1 is file name
# arg2 is range from 1 to n
for ((number=1;number<=$2;number++))
do
    echo "$1""$number.txt"
    "$PWD/build/Debug/outDebug.exe" "-r" "$1""$number.txt"
    echo
done

read -p "Press enter to continue"