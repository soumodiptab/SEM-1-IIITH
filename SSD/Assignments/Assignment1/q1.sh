#!/bin/bash
# Assumption : no spaces in folder names
#Strategy : extract bytes and folder names -> use number sort -> format bytes to nearest multiple -> do some formatting
du -b --max-depth=1 | sort -n -r | sed '1d' | numfmt  --field=1 --to=iec | sed 's/.\///' | awk ' BEGIN {OFS="\t"} {print $2,$1"B"}'
