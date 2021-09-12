#!/bin/bash
function sort_char
{
  local var=$(echo "$1" | grep -o . | sort | tr -d "\n")
  echo $var
}
flag=0
out=()
input=$(echo $1|tr A-Z a-z)
sorted=$(sort_char $input)
compgen -c | sort -u >tmp
while read p; do
	x=$(sort_char $p)
  if [[ $x ==  $sorted ]]
  then
      out+=($p)
      flag=1
  fi
done < tmp
rm tmp
if [ $flag == 0 ]
then
	echo "NO"
else
	printf "YES"
	printf '\t%s' "${out[@]}"
	printf "\n"
fi