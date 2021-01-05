#!/bin/bash
unzip -u kundert_test_matrices.zip
rm -f summary.out
for f in *.mat 
do
    echo $f >> summary.out
    ./KLDemo $f >> summary.out
done
