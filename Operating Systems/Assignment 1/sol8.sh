#!/usr/bin/env bash

# get the file name
read -p "Enter file name: " FILE

if [ -f "$FILE" ]
then
	# enter the word to be searched
	read -p "Enter word: " WORD

	# calculate the frequency of the word
	FREQ=$(grep -wo "$WORD" "$FILE" | wc -l)
    if [ $FREQ -gt 0 ]
    then
        printf "Total Number of occurences: %s\n" $FREQ
        printf "Line No\t\tFrequency\n"
        echo "--------------------------"
        
        # get the line numbers and find the count of duplicates among them
        grep -won "$WORD" "$FILE" | cut -d : -f 1 | uniq -c | awk '{print $2,"\t\t",$1}'
        echo "--------------------------"
    else
    	echo "\"$WORD\" not found in \"$FILE\""
    fi
else
        echo "\"$FILE\" not found"
fi