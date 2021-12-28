#!/usr/bin/env bash

LINES=$(wc -l demo.txt | awk '{ print $1 }')
echo "No of lines in demo.txt: $LINES"
