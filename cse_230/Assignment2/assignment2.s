###########################################################
# Assignment #: 2
#  Name: Tyler Fichiera
#  ASU email: tfichier@asu.edu
#  Course: CSE/EEE230, TTh 1:30pm
#  Description: This program takes two numbers, displays,
#           adds, and subtracts them. The output is
#           printed to the console.
###########################################################

# data declarations: declare variable names used in program, storage allocated in RAM
.data  
    num1: .word 69482               # create a word initialized to 69482 (base 10)
    num2: .word 0xBC7               # create a word initialized to BC7 (base 16)

    msg1: .asciiz "num1 is: "       # create a string containing "num1 is: "  
    msg2: .asciiz "\nnum2 is: "     # create a string containing "\nnum2 is: "  
    msg3: .asciiz "\nnum1+num2 = "  # create a string containing "\nnum1+num2 = "
    msg4: .asciiz "\nnum1-num2 = "  # create a string containing "\nnum1-num2 = "

# program code is contained below under .text
.text
    .globl main # define a global function main

# the program begins execution at main()
main:
    lw		$t0, num1		    # load num1 to temp register 0
    lw		$t1, num2		    # load num2 to temp register 1

    add		$t2, $t0, $t1		# $t2 = $t0 + $t1
    sub		$t3, $t0, $t1		# $t3 = $t0 - $t1
    
    la          $a0, msg1       # $a0 = address of msg1
    li          $v0, 4          # $v0 = 4  --- this is to call print_string()
    syscall                     # call print_string()

    move 	    $a0, $t0		# $a0 = $t0
    li          $v0, 1          # $v0 = 1  --- this is to call print_int()
    syscall                     # call print_int()
    
    la          $a0, msg2       # $a0 = address of msg2
    li          $v0, 4          # $v0 = 4  --- this is to call print_string()
    syscall                     # call print_string()

    move 	    $a0, $t1		# $a0 = $t1
    li          $v0, 1          # $v0 = 1  --- this is to call print_int()
    syscall                     # call print_int()

    la          $a0, msg3       # $a0 = address of msg3
    li          $v0, 4          # $v0 = 4  --- this is to call print_string()
    syscall                     # call print_string()

    move 	    $a0, $t2		# $a0 = $t2
    li          $v0, 1          # $v0 = 1  --- this is to call print_int()
    syscall                     # call print_int()

    la          $a0, msg4       # $a0 = address of msg4
    li          $v0, 4          # $v0 = 4  --- this is to call print_string()
    syscall                     # call print_string()

    move 	    $a0, $t3		# $a0 = $t3
    li          $v0, 1          # $v0 = 1  --- this is to call print_int()
    syscall                     # call print_int()
    
    jr		$ra					# return