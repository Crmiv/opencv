#!/bin/bash
for i in *.c; do
	echo "compiling $i"
	gcc -ggdb `pkg-config --cflags opencv` -o `basename $i .c` $i `pkg-config --libs opencv`;
done

