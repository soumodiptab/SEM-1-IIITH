#!/bin/bash
echo $#
file=$1
#awk 'BEGIN { 
#   for (i = 0; i < ARGC - 1; ++i) { 
#      printf "ARGV[%d] = %s\n", i, ARGV[i] 
#   } 
#}' one two three four
awk '{if($4 > 86)print $0}' $file
