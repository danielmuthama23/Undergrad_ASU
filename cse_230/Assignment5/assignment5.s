###########################################################
#  Assignment #: 5
#  Name: Tyler Fichiera
#  ASU email: tfichier@asu.edu
#  Course: CSE/EEE230, TTh 1:30pm
#  Description: This program takes two integers and uses
#       them to change an array and then reprint the
#       changed array
###########################################################

# data declarations: declare variable names used in program, storage allocated in RAM
.data
    # create strings with the specified values
    msg1: .asciiz "Enter an integer:\n"
    msg2: .asciiz "Enter another integer:\n"
    msg3: .asciiz "Result Array Content:\n"

    # create a word list with 12 predetermined integers 
    numbers: .word -4, 23, 15, -26, 27, 8, -21, 31, 15, -17, 11, -7
    # hardcode length of word list "numbers"
    numbers_len: .word 12

    # create new string with line break char
    new_line: .asciiz "\n"

# program code is contained below under .text
.text
    .globl main

# the program begins execution at main
main:
    la          $s0, numbers        # $s0 = address of list `numbers` from .data
    lw          $s1, numbers_len    # $s1 = word `numbers_len` read from .data
    li          $s2, 0              # $s2 = 0 (inital loop counter)
    
    # collect first integer
    la          $a0, msg1           # $a0 = address of msg1
    li          $v0, 4              # $v0 = 4  --- this is to call print_string()
    syscall                         # call print_string()

    li          $v0, 5              # $v0 = 5
    syscall                         # call read_int()
    move 	    $t0, $v0		    # $t0 = $v0 (first inputted integer)

    # collect second integer
    la          $a0, msg2           # $a0 = address of msg2
    li          $v0, 4              # $v0 = 4  --- this is to call print_string()
    syscall                         # call print_string()

    li          $v0, 5              # $v0 = 5
    syscall                         # call read_int()
    move 	    $t1, $v0		    # $t1 = $v0 (second inputted integer)

    j		    base_loop		    # jump to base_loop

    la          $s0, numbers        # $s0 = reset address of list `numbers` from .data
    li          $s2, 0              # $s2 = 0 (reset loop counter)

    j		    print_loop		    # jump to print_loop

base_loop:
    beq		    $s1, $s2, prepare_print	    # if $s1 == $s2 then prepare_print

    lw          $t3, 0($s0)
    div		    $t3, $t0	        # 0($s0) / $t0
    mflo        $t4                 # $t4 = lower 32 bits of division (quotient)

    li          $t5, 3              # $t5 = 3
    blt         $t4, $t5, conditional_branch

    addi	    $s0, $s0, 4			# $s0 += 4
    addi	    $s2, $s2, 1			# $s2++

    j           base_loop           # repeat the loop

conditional_branch:
    div		    $t3, $t1		    # $t3 / $t1
    mfhi	    $t6			        # $t6 = $t3 mod $t1

    sw		    $t6, 0($s0)		    # 

    addi	    $s0, $s0, 4			# $s0 += 4
    addi	    $s2, $s2, 1			# $s2++

    j           base_loop

    jr		    $ra				    # return

prepare_print:
    la          $s0, numbers        # $s0 = reset address of list `numbers` from .data
    li          $s2, 0              # $s2 = 0 (reset loop counter)

    # print array content msg
    la          $a0, msg3           # $a0 = address of msg3
    li          $v0, 4              # $v0 = 4  --- this is to call print_string()
    syscall                         # call print_string()

    j		    print_loop		    # jump to print_loop

print_loop:
    beq		    $s1, $s2, exit	    # if $s1 == $s2 then exit

    # print the elements in the array individually
    lw		    $a0, 0($s0)		    # $a0 = first index at array point
    li          $v0, 1              # $v0 = 1  --- this is to call print_int()
    syscall                         # call print_int()

    # print new line
    la          $a0, new_line       # $a0 = address of new_line
    li          $v0, 4              # $v0 = 4  --- this is to call print_string()
    syscall                         # call print_string()

    addi	    $s0, $s0, 4			# $s0 += 4
    addi	    $s2, $s2, 1			# $s2++

    j           print_loop          # repreat the loop

exit:
    jr		    $ra				    # return
