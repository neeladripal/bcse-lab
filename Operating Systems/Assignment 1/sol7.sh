#!/usr/bin/env bash

# get input for the number
read -p "Enter a number: " NUM

# initialize multiplier
COUNTER=1

# print multiplication table
echo "Multiplication table of $NUM -->"
while [ $COUNTER -le 10 ]
do
	echo "$NUM x $COUNTER = $(($NUM * $COUNTER))"
	COUNTER=$(($COUNTER + 1))
done