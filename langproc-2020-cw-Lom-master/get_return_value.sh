#!/bin/bash

mips-linux-gnu-gcc -mfp32 -o test_program.o -c test_program.s

mips-linux-gnu-gcc -mfp32 -static -o test_program test_program.o

./test_program

echo $?