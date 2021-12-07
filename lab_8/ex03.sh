#!/bin/sh

if [ $# -ne 2]
then 
  echo "Usage : $0 directory"
  exit 1
fi

for i in 'ls $1'
do 
  mv $1/$i $1/'echo $i | tr A-Z a-z'
done