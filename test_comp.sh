#!/bin/bash

for i in test/*.c
do
	BASE=$(basename $i .c);
	
	mips-linux-gnu-gcc -ansi -static $i -o ./testdump/"$BASE"_ref_test
	qemu-mips testdump/"$BASE"_ref_test
	REF_TEST=$(echo $?)

	cat $i | bin/c_compiler > testdump/"$BASE".s
	mips-linux-gnu-gcc -static testdump/"$BASE".s -o testdump/"$BASE"_my_test
	qemu-mips testdump/"$BASE"_my_test
	COMPILER_TEST=$(echo $?)

	if [ "$REF_TEST" = "$COMPILER_TEST" ];
		then
		echo "$BASE passed: $COMPILER_TEST";
		rm testdump/"$BASE"_ref_test;
		rm testdump/"$BASE"_my_test;
		else
		echo "$BASE failed:"
		echo "gcc: $REF_TEST"
		echo "me: $COMPILER_TEST";
		fi
done
