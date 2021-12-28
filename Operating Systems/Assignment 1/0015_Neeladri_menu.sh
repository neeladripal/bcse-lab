#!/usr/bin/env bash

# function to check if an user exists
find_user() {
    if (id "$1" &>/dev/null); then
        echo "User exists."
    else
        echo "User does not exist."
    fi
}

# function to list files greater than a given size in bytes
list_large_files () {
    echo "Files with size greater than $1 bytes -->"
    printf "File Size\t\tFile Name\n"
    find . -type f -size +"$1"c -print0 | xargs -0 ls -lh | awk '{print $5,"\t\t",$9}'
}

# function to view disk usage by sub-directories
view_disk_usage () {
    echo "Disk Usage -->"
    du -h
}

# function to view the logs
view_log_file () {
    echo 'Log file -->'
    cat logfile.txt
}

# function to update the log file after some action
update_log_file () {
    list=$1
    ch=${list[2]}
    printf '%s%%%s%%%s\n' "$(whoami)" "${ch// /_}" "$(date)" >> logfile.txt
}

# create the log file if it doesn't exist
touch logfile.txt

# keep the menu items in an array
declare -a list=("Find user" "List large files" "View disk usage" "View log file" "Exit")
# intialialize choice
choice=-1

# keep loop running until it choice is 5
while [ ! "$choice" -eq 5 ]
do
    echo "----------------"
    echo "Menu -->"
    counter=1

    # display the menu to the user
    for item in "${list[@]}"
    do
        printf '%d. %s\n' "$counter" "$item"
        counter=$(($counter + 1))
    done
    echo "----------------"

    # take choice input
    read -p "Enter your choice: " choice

    case $choice in
        1)
        # check for the user and update log
        read -p "Enter user name: " username
        find_user "$username"
        update_log_file "$list" "$choice"
        ;;

        2)
        # list large files and update log
        read -p "Enter file size in bytes: " filesize
        list_large_files "$filesize"
        update_log_file "$list" "$choice"
        ;;

        3)
        # view disk usage and update log
        view_disk_usage
        update_log_file "$list" "$choice"
        ;;

        4)
        # view the log file
        view_log_file
        ;;

        5)
        echo "Exiting.."
        ;;

        *)
        echo "Not a valid choice."
        ;;

    esac
done
