#!/bin/bash
if [ "$#" == 3 ]
then
	echo "$1+$2-$3" | bc
else
	echo "Provide correct arguments"
fi
