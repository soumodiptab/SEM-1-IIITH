#!/bin/bash
func (){
echo " This is a demo function "
}
line_count (){
wc -l $1 | awk ‘{ print $1 } ’
}
func
num = $ ( line_count $1 )
echo " File $1 has $num lines ."
