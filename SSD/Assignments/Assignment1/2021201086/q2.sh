#!/bin/bash
# $1 = input.txt $2 = output.txt
grep -owi "\w*ing" $1 | tr A-Z a-z > $2