#!/bin/bash


make clean
set -e
make bin/c_compiler

bin/c_compiler -S test_program.c -o test_program.s
