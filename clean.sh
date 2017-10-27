#!/bin/bash

if [ -e "*.*~" ]
then 
    rm *.*~
fi

for i in $(find . -name '*.cc');
do
    basei=$(basename $i)
    filei="${basei%.cc}"
    if [ -e $filei ]
    then
	rm $filei
    fi
done
