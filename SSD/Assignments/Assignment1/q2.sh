#!/bin/bash
# $1 = input.txt $2 = output.txt
grep -oh -w "\w*ing" $1 > $2
