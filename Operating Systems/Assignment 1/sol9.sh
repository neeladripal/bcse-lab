#!/usr/bin/env bash

# get the file name
read -p "Enter file name: " FILE

if [ -f "$FILE" ]
then
	# enter the word to be searched
	read -p "Enter search word: " SWORD

	# calculate the no of occurences of the word
	FREQ=$(grep -wo "$SWORD" "$FILE" | wc -l)
    if [ $FREQ -gt 0 ]
    then
    	printf "Total Number of occurences: %s\n" $FREQ
    	
    	# enter the word to be replaced
		read -p "Enter replace word: " RWORD
        
        # replace all occurences of SWORD with RWORD in the original file
        sed -i "s|$SWORD|$RWORD|g" $FILE
        
	echo "Replaced all occurences of \"$SWORD\" with \"$RWORD\""
    else
    	echo "\"$SWORD\" not found in \"$FILE\""
    fi
else
        echo "\"$FILE\" not found"
fi