#!/bin/bash

f_tests="./Tests";
f_output="./Output";
prog="a.out";

let count=0;
let errcount=0;

echo "Cleaning up Output folder...";
rm $f_output/*;
echo "done. Testing...";

for t in $(ls $f_tests/*.txt); do 
	./$prog <$t >$f_output/`basename $t .txt`.txt.output;
	count=$((count+1));
done;

for te in $(ls $f_tests/*.expected); do 
	diff -ibadBw $f_output/`basename $te .expected`.output  $te  > $f_output/`basename $te .expected`.diff;
done

for d in $(ls $f_output/*.diff); do
	echo "========================================================";
	echo "TEST: " `basename $d .txt.diff`;
	if [ -s $d ]; then
		errcount=$((errcount+1));
		echo "diff says:";
		cat $d;
	else
		echo "NO ERRORS HERE!";
	fi
done

echo "Test Count:" $count " Error Count:" $errcount;

