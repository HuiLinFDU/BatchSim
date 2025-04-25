#! /bin/bash
# for compiling the C programs of BPS.
# Note: must keep them in the same directory!

# Check if the number of arguments is correct
if [ "$#" -ne 1 ]; then
    echo "Error: Please provide the source code."
    exit 1
fi

echo "Begin to compile:" $1

# Compile the C program
gcc -o $1 $1.c

echo "Compile Done!" 


