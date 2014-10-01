#!/bin/bash
for d in pipe ipc;
do
	cd $d
	echo $(pwd)
	rm *~
	rm *.out
	rm *.fifo
	cd ..
done
