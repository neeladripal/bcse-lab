#!/usr/bin/env bash

# get input for the dates
read -p "Enter date 1: " DATE1
read -p "Enter date 2: " DATE2

# extract full weekday name
DAY1=$(date -j -f '%d/%m/%Y' $DATE1 +'%A')
DAY2=$(date -j -f '%d/%m/%Y' $DATE2 +'%A')

# check if the weekdays are equal
if [ $DAY1 = $DAY2 ]
then
	echo "Both days are equal to $DAY1"
else
	echo "Days are unequal"
fi