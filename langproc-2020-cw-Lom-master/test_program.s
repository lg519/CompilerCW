	
.globl main

main:
addiu   $sp,$sp,-8
sw      $fp,8($sp)
move    $fp,$sp
li       $8,5
addiu    $sp,$sp,-4
sw       $8,0($sp)
li       $8,9
addiu    $sp,$sp,-4
sw       $8,0($sp)
li       $8,2
addiu    $sp,$sp,-4
sw       $8,0($sp)
lw      $8,0($sp)
addiu    $sp,$sp,4
lw      $9,0($sp)
addiu    $sp,$sp,4
mult    $9,$8
mflo    $10
addiu    $sp,$sp,-4
sw       $10,0($sp)
lw      $8,0($sp)
addiu    $sp,$sp,4
lw      $9,0($sp)
addiu    $sp,$sp,4
add    $10,$9,$8
addiu    $sp,$sp,-4
sw       $10,0($sp)
lw      $8,0($sp)
addiu    $sp,$sp,4
move    $2,$8
move    $sp,$fp
lw      $fp,8($sp)
addiu   $sp,$sp,8
jr       $31
nop
