#!/bin/bash
function int_to_rom()
{
	local numeral=""
	local num=$1
	local rom=(M CM D CD C XC L XL X IX V IV I)
    	local dec=(1000 900 500 400 100 90 50 40 10 9 5 4 1)
    	local i=0
    	while [ $num -gt 0  ]
    	do
    		local val=${dec[$i]}
    		local r=${rom[$i]}
    		local div=$(( num / val ))
    		num=$(( num % val ))
    		while [ $div -gt 0 ]
    		do
    			numeral=$numeral$r
    			((div--))
    		done
    		((i++))
    	done
    	echo $numeral
}
function rom_to_int()
{
	local num=$(
    echo $1 |
    sed 's/CM/DCD/g' |
    sed 's/M/DD/g' |
    sed 's/CD/CCCC/g' |
    sed 's/D/CCCCC/g' |
    sed 's/XC/LXL/g' |
    sed 's/C/LL/g' |
    sed 's/XL/XXXX/g' |
    sed 's/L/XXXXX/g' |
    sed 's/IX/VIV/g' |
    sed 's/X/VV/g' |
    sed 's/IV/IIII/g' |
    sed 's/V/IIIII/g' |
    tr -d '\n' |
    wc -m)
	echo $num
}
if [[ $# == 1 ]]
then
	numeral=$(int_to_rom $1)
	echo $numeral
elif [[ $# == 2 ]]
then
	x=$1
	y=$2
	if [[ "${x//[IVXLCDM]/}" == "" && "${y//[IVXLCDM]/}" == "" ]]
	then
		num1=$(rom_to_int $x)
		num2=$(rom_to_int $y)
		sum=$(( num1 + num2 ))
		echo $sum
    elif [[ "${x//[IVXLCDM]/}" == "" || "${y//[IVXLCDM]/}" == "" ]]
    then
        exit 
    else
        sum=$(( x + y ))
        numeral=$(int_to_rom $sum)
		echo $numeral
    fi
else
	exit
fi
#rom_to_int $1