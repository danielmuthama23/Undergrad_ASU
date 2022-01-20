###########################################################
#  Assignment #: 3
#  Name: Tyler Fichiera
#  ASU email: tfichier@asu.edu
#  Course: CSE/EEE230, TTh 1:30pm
#  Description: Program asks for 4 number inputs and then
#       computes six equations and displays the results
###########################################################

# data declarations: declare variable names used in program, storage allocated in RAM
.data  
    msg1: .asciiz "Enter a value:\n"        # create a string containing "Enter a value:\n"
    msg2: .asciiz "Enter another value:\n"  # create a string containing "Enter another value:\n"
    msg3: .asciiz "Enter one more value:\n" # create a string containing "Enter one more value:\n"
    msg4: .asciiz "\nnum2+num4="            # create a string containing "\nnum2+num4="
    msg5: .asciiz "\nnum4-num1="            # create a string containing "\nnum4-num1="
    msg6: .asciiz "\nnum2*num3="            # create a string containing "\nnum2*num3"
    msg7: .asciiz "\nnum1/num4="            # create a string containing "\nnum1/num4="
    msg8: .asciiz "\nnum4 mod num3="        # create a string containing "\nnum4 mod num3="
    # create a string containing "\n((num3 / num2) - 7) * (num4 mod num1)="
    msg9: .asciiz "\n((num3 / num2) - 7) * (num4 mod num1)="

    newLine: .asciiz "\n"                   # create a string the contains the new line char "\n"

# program code is contained below under .text
.text
    .globl main # define a global function main

# the program begins execution at main()
main:
    # collect first number
    la          $a0, msg1       # $a0 = address of msg1
    li          $v0, 4          # $v0 = 4  --- this is to call print_string()
    syscall                     # call print_string()

    li          $v0, 5          # $v0 = 5
    syscall                     # call read_int()
    move 	    $t1, $v0		# $t1 = v0

    # collect second number
    la          $a0, msg2       # $a0 = address of msg2
    li          $v0, 4          # $v0 = 4  --- this is to call print_string()
    syscall                     # call print_string()

    li          $v0, 5          # $v0 = 5
    syscall                     # call read_int()
    move 	    $t2, $v0		# $t2 = v0

    # collect third number
    la          $a0, msg3       # $a0 = address of msg3
    li          $v0, 4          # $v0 = 4  --- this is to call print_string()
    syscall                     # call print_string()

    li          $v0, 5          # $v0 = 5
    syscall                     # call read_int()
    move 	    $t3, $v0		# $t3 = v0

    # collect fourth number
    la          $a0, msg3       # $a0 = address of msg3
    li          $v0, 4          # $v0 = 4  --- this is to call print_string()
    syscall                     # call print_string()

    li          $v0, 5          # $v0 = 5
    syscall                     # call read_int()
    move 	    $t4, $v0		# $t4 = v0

    # compute equations and store in temp registry
    add		    $s1, $t2, $t4	# $s1 = $t2 + $t4

    sub		    $s2, $t4, $t1	# $s2 = $t4 - $t1

    mult		$t2, $t3	    # $t2 * $t3
    mflo        $s3             # $s3 = lower 32 bits of multiplication

    div		    $t1, $t4	    # $t1 / $t4
    mflo        $s4             # $s4 = lower 32 bits of division (quotient)

    div         $t4, $t3        # $t4 / $t3
    mfhi        $s5             # $s5 = upper 32 bits of division (remainder / modulo)

    # final equation
    div		    $t3, $t2	    # $t3 / $t2
    mflo	    $t5		        # $t5 = floor($t3 / $t2) 
    # mfhi	    $t3			    # $t3 = $t3 mod $t2 

    addi	    $t6, $t5, -7	# $t6 = $t5 - 7

    div		    $t4, $t1		# $t4 / $t1
    mfhi	    $t7			    # $t7 = $t4 mod $t1 

    mult	    $t6, $t7		# $t6 * $t7 = Hi and Lo registers
    mflo	    $s6			    # $s6 = lower 32 bits of division (quotient)
    
    # display first equation
    la          $a0, msg4       # $a0 = address of msg4
    li          $v0, 4          # $v0 = 4  --- this is to call print_string()
    syscall                     # call print_string()

    move 	    $a0, $s1		# $a0 = $s1
    li          $v0, 1          # $v0 = 1  --- this is to call print_int()
    syscall                     # call print_int()

    # print new line
    la          $a0, newLine    # $a0 = address of newLine
    li          $v0, 4          # $v0 = 4  --- this is to call print_string()
    syscall                     # call print_string()

    # display second equation
    la          $a0, msg5       # $a0 = address of msg5
    li          $v0, 4          # $v0 = 4  --- this is to call print_string()
    syscall                     # call print_string()

    move 	    $a0, $s2		# $a0 = $s2
    li          $v0, 1          # $v0 = 1  --- this is to call print_int()
    syscall                     # call print_int()

    # print new line
    la          $a0, newLine    # $a0 = address of newLine
    li          $v0, 4          # $v0 = 4  --- this is to call print_string()
    syscall                     # call print_string()

    # display third equation
    la          $a0, msg6       # $a0 = address of msg6
    li          $v0, 4          # $v0 = 4  --- this is to call print_string()
    syscall                     # call print_string()

    move 	    $a0, $s3		# $a0 = $s3
    li          $v0, 1          # $v0 = 1  --- this is to call print_int()
    syscall                     # call print_int()

    # print new line
    la          $a0, newLine    # $a0 = address of newLine
    li          $v0, 4          # $v0 = 4  --- this is to call print_string()
    syscall                     # call print_string()

    # display fourth equation
    la          $a0, msg7       # $a0 = address of msg7
    li          $v0, 4          # $v0 = 4  --- this is to call print_string()
    syscall                     # call print_string()

    move 	    $a0, $s4		# $a0 = $s4
    li          $v0, 1          # $v0 = 1  --- this is to call print_int()
    syscall                     # call print_int()

    # print new line
    la          $a0, newLine    # $a0 = address of newLine
    li          $v0, 4          # $v0 = 4  --- this is to call print_string()
    syscall                     # call print_string()

    # display fith equation
    la          $a0, msg8       # $a0 = address of msg8
    li          $v0, 4          # $v0 = 4  --- this is to call print_string()
    syscall                     # call print_string()

    move 	    $a0, $s5		# $a0 = $s5
    li          $v0, 1          # $v0 = 1  --- this is to call print_int()
    syscall                     # call print_int()

    # print new line
    la          $a0, newLine    # $a0 = address of newLine
    li          $v0, 4          # $v0 = 4  --- this is to call print_string()
    syscall                     # call print_string()

    # display sixth equation
    la          $a0, msg9       # $a0 = address of msg9
    li          $v0, 4          # $v0 = 4  --- this is to call print_string()
    syscall                     # call print_string()

    move 	    $a0, $s6		# $a0 = $s9
    li          $v0, 1          # $v0 = 1  --- this is to call print_int()
    syscall                     # call print_int()

    jr		$ra				    # return