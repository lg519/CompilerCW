#!/bin/bash

make clean
make bin/c_compiler

for x in compiler_tests/default/*
do 
    if [[ ${x} == *"driver.c" ]]
    then
        #driver file
        DRIVER=${x}
        echo -e "DRIVER FILE IS \n" ${DRIVER}

        FILE=${DRIVER%_driver.c}

        echo -e "FILE IS \n" ${FILE}

        
        bin/c_compiler -S   ${FILE}.c -o  ${FILE}.s
        mips-linux-gnu-gcc -mfp32 -o ${FILE}.o -c ${FILE}.s
        mips-linux-gnu-gcc -mfp32 -static -o ${FILE} ${FILE}.o ${DRIVER}
        qemu-mips ${FILE}

        echo -e "TEST RESULT IS" $? "\n \n \n"
        
    
    fi

    #bin/c_compiler -S   ${CFILE} -o  test_program.s

    #mips-linux-gnu-gcc -mfp32 -o test_program.o -c test_program.s

    #mips-linux-gnu-gcc -mfp32 -static -o test_program test_program.o ${DRIVER}

    #qemu-mips test_program

    #echo "PROGRAM TESTED IS" ${CFILE}
    #echo "TEST RESULT IS" $?

    #rm test_program.s 
    #rm test_program
    #rm test_program.o

done