###########################################################
#  Assignment #: 7
#  Name: Tyler Fichiera
#  ASU email: tfichier@asu.edu
#  Course: CSE/EEE230, TTh 1:30pm
#  Description: This program asks the user for an integer
#       and then computes a value based on the recursive
#       function:
#       function1(n) = (n % 3) + 5 if n <= 5
#       = function1(n-3)/n + function1(n-4)*6 - n
###########################################################

# data declarations: declare variable names used in program, storage allocated in RAM
.data
    # create strings with the specified values
    msg1: .asciiz "Enter an integer:\n"
    msg2: .asciiz "The solution is: "
    newLine: .asciiz "\n"

    val: .asciiz "value here: "

# program code is contained below under .text
.text
    .globl main

############################################################################
# Procedure/Function main
# Description: Where the program begins execution
# parameters: none
# return value: none
# registers to be used: $a0, $v0, $s0, $sp, $ra
############################################################################
main:
    # collect first integer
    la          $a0, msg1           # $a0 = address of msg1
    li          $v0, 4              # $v0 = 4  --- this is to call print_string()
    syscall                         # call print_string()

    li          $v0, 5              # $v0 = 5
    syscall                         # call read_int()
    move 	    $s0, $v0		    # $s0 = $v0 (first inputted integer)

    move        $a0, $s0            # $a0 = $s0 (used as first param for function)

    addi	    $sp, $sp, -4        # $sp = $sp - 4
    sw          $ra, 0($sp)
    
    jal         function1           # jump and link to function1

    lw          $ra, 0($sp)
    addi	    $sp, $sp, 4         # $sp = sp + 4

    move        $s0, $v0            # $s0 = $v0

    # print solution
    la          $a0, msg2           # $a0 = address of msg2
    li          $v0, 4              # $v0 = 4  --- this is to call print_string()
    syscall                         # call print_string()

    move        $a0, $s0            # $a0 = $s0
    li          $v0, 1              # $v0 = 4  --- this is to call print_int()
    syscall                         # call print_int()

    la          $a0, newLine        # $a0 = address of newLine
    li          $v0, 4              # $v0 = 4  --- this is to call print_string()
    syscall                         # call print_string()

    jr		    $ra				    # return

############################################################################
# Procedure/Function function1
# Description: this function defines the recursive method used for the assignment
# parameters: $a0 (user inputted value)
# return value: $v0 (current value)
# registers to be used: $sp, $ra, $a0, $s1, $t0, $t1
############################################################################
function1:    
    addi	    $sp, $sp, -12	    # $sp = $sp - 12
    sw		    $ra, 0($sp)		    # store $ra to the stack
    sw		    $a0, 4($sp)		    # store $a0 to the stack
    sw		    $s1, 8($sp)		    # store $s1 to the stack

    # if $a0 > 5 then function1else
    li          $t0, 5
    bgt		    $a0, $t0, function1else

    ###### Test ####
    # la          $a0, test            # $a0 = address of msg2
    # li          $v0, 4              # $v0 = 4  --- this is to call print_string()
    # syscall                         # call print_string()
    ###### Test ####

    li          $t0, 3
    div         $a0, $t0            # $a0 / $t0
    mfhi        $t1                 # $t1 = upper 32 bits of division (remainder / modulo)

    addi	    $t1, $t1, 5			# $t1 += 5

    move        $v0, $t1            # return $t1

    # undo everything that was done at the top of function1
    lw		    $s1, 8($sp)
    lw		    $a0, 4($sp)
    lw		    $ra, 0($sp)
    addi	    $sp, $sp, 12	    # $sp += 12

    jr		    $ra				    # return

############################################################################
# Procedure/Function function1else
# Description: handles the conditional statement in function1
# parameters: $a0 (user inputted value)
# return value: $v0 (current value)
# registers to be used: $sp, $ra, $a0, $s1, $t0, $t1
############################################################################
function1else:
    addi	    $a0, $a0, -3		# $a0 -= 3
    jal         function1

    addi	    $a0, $a0, 3		    # $a0 += 3 (original value)
    div		    $v0, $a0	        # $v0 / $a0
    mflo        $s1                 # $s1 = lower 32 bits of division (quotient)

    addi	    $a0, $a0, -4		# $a0 -= 4
    jal         function1

    addi	    $a0, $a0, 4		    # $a0 += 4 (original value)

    li          $t1, 6              # $t1 = 6
    mult		$v0, $t1	        # $v0 * 6
    mflo        $t2                 # $t1 = lower 32 bits of multiplication

    add         $s1, $s1, $t2       # $s1 = $s1 + $t2
    sub         $v0, $s1, $a0       # $v0 (return val) = $s1 - $a0

    # undo everything that was done at the top of function1
    lw		    $s1, 8($sp)
    lw		    $a0, 4($sp)
    lw		    $ra, 0($sp)
    addi	    $sp, $sp, 12	    # $sp += 12

    jr		    $ra				    # return
