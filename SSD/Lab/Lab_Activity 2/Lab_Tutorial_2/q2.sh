#!/bin/bash

for num in {1..30}; do
  if [[ $(( $num % 3 )) == 0 ]]; then
    continue
  fi
  echo $num
done
