#!/usr/bin/awk -f 
func MAX(val1, val2) { 
        if (val1 > val2)
	        return val1 
        else 
	        return val2
	                 } 
BEGIN {largest = 0}
{largest = MAX(largest, $1)} 
END {print largest}
