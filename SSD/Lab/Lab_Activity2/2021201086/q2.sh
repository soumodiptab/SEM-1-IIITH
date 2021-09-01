#!/bin/bash
#1
grep -v -w "threatened" hamlet.txt | grep -w "is"
#2
mid=$( wc -l hamlet.txt | awk '{print $1}' )
((mid/=2))
((right=$mid+5))
cat hamlet.txt | head -n $right | tail -n 10
#3
awk '{print $3,$5}' hamlet.txt
