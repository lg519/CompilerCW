#!/bin/bash
echo "Compiling to MIPS..."
cat $2 | ./bin/compiler 2> ./cerr.o 1> $4
