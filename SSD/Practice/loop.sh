#!/bin/bash
if[[ $# != 2 ]]
	exit
fi
for(( i=$1 ; i<=$2 ; i++ ))
do
	echo "$i"
done
echo "END"
