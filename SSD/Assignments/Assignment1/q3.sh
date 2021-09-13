#!/bin/bash
function sort_char
{
  local var=$(echo "$1" | grep -o . | sort | tr -d "\n")
  echo $var
}
flag=0
out=()
#input converting upper -> lower case
input=$1
sorted=$(sort_char $input)
compgen -c | sort -u >temp
#optimization to reduce running time
awk -v d=${#input} '{ if ( length == d ) print $0 }' temp > temp2
rm temp
while read p; do
	x=$(sort_char $p)
  if [[ $x ==  $sorted ]]
  then
      out+=($p)
      flag=1
  fi
done < temp2
rm temp2
if [ $flag == 0 ]
then
	echo "NO"
else
	printf "YES"
	printf '\t%s' "${out[@]}"
    printf "\n"
fi