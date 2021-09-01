#!/bin/bash
if [ "$#" -ne 2 ]; then
    echo "You must enter exactly 2 command line arguments"
fi
echo $#
echo $@
