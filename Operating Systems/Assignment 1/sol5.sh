#!/usr/bin/env bash

dir=my-deleted-files

# this is the switch or the file to be deleted
oldfile=$(basename -- $1)

# check if the file exists
if [ -f $oldfile ]
then
	# delete the shortest occurence of .* from back of file
	oldfilename="${oldfile%.*}"

	# delete the longest occurence of *. from front of file
	extension="${oldfile##*.}"
	
	# initialise the version as 0
	version=-1
	newfile="$oldfile"

	# change directory to trash folder
	cd $dir

	firstfile="${oldfilename}-0.${extension}"
	
	# check if some version of the file is already existing
	if [ -f $oldfile -o -f $firstfile ]; then
		
		# if already only one instance of the file exists in trash, assign version 0 to it
		if [ -f $oldfile ]; then
			mv $oldfile $firstfile
		fi

		# extract the file with the greatest version number
		for file in $(find . -type f -name "${oldfilename}*.${extension}")
		do
		    filename="${file%.*}"
		    curver=${filename#*-}
		    if [ $curver -gt $version ]; then
		    	version=$curver
		    fi
		done
	fi

	# return back to main directory
	cd ..

	# check if the version needs to be incremnted
	if [ $version -ge 0 ]; then
		version=$(($version + 1))
		# rename the old file
		newfile="${oldfilename}-${version}.${extension}"
		mv $oldfile $newfile
	fi

	# move the file inside the trash folder
	mv $newfile $dir
	echo "Successfully deleted."

elif [ "$oldfile" = "-c" ]
then
	# clear the trash
	rm $dir/*
	echo "Trash cleaned."
else
	echo "Error: \"$oldfile\" not found."
fi