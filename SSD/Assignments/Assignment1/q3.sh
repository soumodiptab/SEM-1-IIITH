#!/bin/bash
perm() {
  local items="$1"
  local out="$2"
  local i
  [[ "$items" == "" ]] && echo "$out" && return
  for (( i=0; i<${#items}; i++ )) ; do
    perm "${items:0:i}${items:i+1}" "$out${items:i:1}"
  done
  }
flag=0
perm $1 > tmp
while read p; do
	x=$($p --help 2>/dev/null)
	[[ ! -z $x ]] && flag=1 && out+=($p)
done < tmp
rm tmp
if [ $flag == 0 ]
then
	echo "NO"
else
	printf "\nYES "
	printf '%s\t' "${out[@]}"
fi
