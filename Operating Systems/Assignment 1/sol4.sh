#!/usr/bin/env bash

echo "Count of regular files in current directory: $(find . -type f | wc -l | awk '{ print $1 }')"