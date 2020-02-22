#!/bin/bash

INPUT=2F_binary_file
CORRECT_OUTPUT=ASCII_output

if [[ $# != 1 ]] ; then
   echo "Usage: $0 <c file>"
   exit 1
fi

gcc -o proj2F $1
if [[ $? != 0 ]] ; then
   echo "Compile failure!"
   exit 1
fi

if [[ ! -f $INPUT ]] ; then
   echo "Cannot find file $INPUT to open."
   exit 1
fi

rm -f ./my_ASCII_output
./proj2F $INPUT my_ASCII_output

if [[ ! -f my_ASCII_output ]] ; then
   echo "You did not generate the correct file output name."
   exit 1
fi

diff $CORRECT_OUTPUT my_ASCII_output
if [[ $? != 0 ]] ; then
   echo "Your output is not correct."
   exit 1
fi

echo "Your program appears to be working correctly."
echo "It compiles, runs, and generates the correct output."
echo "Please upload this c file to Canvas, as per the instructions in the 2F prompt."
echo "Grading will consist of the steps performed by this script, complemented by inspection of your code."

