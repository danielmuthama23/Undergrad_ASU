###########################################################
#  Assignment #: 6
#  Name: Tyler Fichiera
#  ASU email: tfichier@asu.edu
#  Course: CSE/EEE230, TTh 1:30pm
#  Description: This program asks a user to input 14 integers
#       and then changes the array multiple times
###########################################################

# data declarations: declare variable names used in program, storage allocated in RAM
.data
    # create strings with the specified values
    msg1: .asciiz "Enter an integer:\n"
    msg2: .asciiz "Enter another integer:\n"
    msg3: .asciiz "Enter 12 integers.\n"
    msg4: .asciiz "The number of changed items is "
    msg5: .asciiz "Array Content:\n"
    msg6: .asciiz "The maximum number of changed items is "

    test: .asciiz "test 12345: "

    # create placeholder lists with 12 integers
    numbers1: .word 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    numbers2: .word 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

    # hardcode length of word list "numbers"
    numbers_len: .word 12

    # create new string with line break char
    new_line: .asciiz "\n"

    # create new string with colon
    colon: .asciiz ":\n"

# program code is contained below under .text
.text
    .globl main

############################################################################
# Procedure/Function function1
# Description: Where the program begins execution
# parameters: none
# return value: none
# registers to be used: $s0-$s2, $t5-6
############################################################################
main:
    la          $s0, numbers1       # $s0 = address of list `numbers1` from .data
    la          $s1, numbers2       # $s1 = address of list `numbers2` from .data
    lw          $s2, numbers_len    # $s2 = word `numbers_len` read from .data

    li          $s3, 0              # global max count
    li          $s4, 0              # global function1 run counter
    li          $s5, 4              # number of times to run function1

    # collect first integer
    la          $a0, msg1           # $a0 = address of msg1
    li          $v0, 4              # $v0 = 4  --- this is to call print_string()
    syscall                         # call print_string()

    li          $v0, 5              # $v0 = 5
    syscall                         # call read_int()
    move 	    $t5, $v0		    # $t0 = $v0 (first inputted integer)

    # collect second integer
    la          $a0, msg2           # $a0 = address of msg2
    li          $v0, 4              # $v0 = 4  --- this is to call print_string()
    syscall                         # call print_string()

    li          $v0, 5              # $v0 = 5
    syscall                         # call read_int()
    move 	    $t6, $v0		    # $t1 = $v0 (second inputted integer)

    # move        $a0, $s0            # $a0 = $s0 (first param)
    move        $a1, $s2            # $a1 = $s2 (second param)
    jal		    readArray			# jump to readArray and save position to $ra

    jr		    $ra				    # return


############################################################################
# Procedure/Function readArray
# Description: This funct asks the user to input 12 integers
# parameters: $a0 = address of numbers arr, $a1 = length of array
# return value: none
# registers to be used: $s0, $t2-$t3
############################################################################
readArray:
    li          $t2, 0              # $t2 = 0 (counter)

    # display "Enter 12 integers.\n"
    la          $a0, msg3           # $a0 = address of msg3
    li          $v0, 4              # $v0 = 4  --- this is to call print_string()
    syscall                         # call print_string()

    j		    readWhileLoop		# jump to readLoop

    jr		    $ra				    # return

readWhileLoop:
    beq		    $t2, $s2, startFunction1	    # if $t2 == $s2 then startFunction1

    # display "Enter an integer:\n"
    la          $a0, msg1           # $a0 = address of msg1
    li          $v0, 4              # $v0 = 4  --- this is to call print_string()
    syscall                         # call print_string()

    li          $v0, 5              # $v0 = 5
    syscall                         # call read_int()
    move 	    $t3, $v0		    # $t0 = $v0 (inputted integer)

    sw		    $t3, 0($s0)         #

    addi	    $s0, $s0, 4			# $s0 += 4
    addi	    $t2, $t2, 1			# $t2++

    j		    readWhileLoop		# repeat the loop

############################################################################
# Procedure/Function printArray
# Description: This prints out the ints in numbers1 ($s1)
# parameters: $a0 = address of numbers arr, $a1 = length of array
# return value: none
# registers to be used: $s1, $t2-$t3
############################################################################
printArray:
    la          $s1, numbers2       # $s1 = address of list `numbers2` from .data

    li          $t2, 0              # $t2 = 0 (counter)

    # display "Array Content:\n"
    la          $a0, msg5           # $a0 = address of msg5
    li          $v0, 4              # $v0 = 4  --- this is to call print_string()
    syscall                         # call print_string()

    j		    printWhileLoop		# jump to printWhileLoop

    jr		    $ra				    # return

printWhileLoop:
    beq		    $t2, $s2, calculateMaxCount	    # if $t2 == $s2 then exit

    # print the elements in the array individually
    lw		    $a0, 0($s1)		    # $a0 = index at array pointer
    li          $v0, 1              # $v0 = 1  --- this is to call print_int()
    syscall                         # call print_int()

    # print new line
    la          $a0, new_line       # $a0 = address of new_line
    li          $v0, 4              # $v0 = 4  --- this is to call print_string()
    syscall                         # call print_string()

    addi	    $s1, $s1, 4			# $s1 += 4
    addi	    $t2, $t2, 1			# $t2++

    j           printWhileLoop      # repreat the loop

    jr		    $ra				    # return

startFunction1:
    li      $t7, 0
    beq		$s4, $t7, callFunction1_1	# if $t0 == $t1 then target

    li      $t7, 1
    beq		$s4, $t7, callFunction1_2	# if $t0 == $t1 then target

    li      $t7, 2
    beq		$s4, $t7, callFunction1_3	# if $t0 == $t1 then target

    li      $t7, 3
    beq		$s4, $t7, callFunction1_4	# if $t0 == $t1 then target
    
    
callFunction1_1:
    move        $t0, $t5
    move        $t1, $t6

    j           function1

callFunction1_2:
    move        $t0, $t6
    move        $t1, $t5

    j           function1

callFunction1_3:
    move        $t0, $t5
    move        $t1, $t5

    j           function1

callFunction1_4:
    move        $t0, $t6
    move        $t1, $t6

    j           function1

############################################################################
# Procedure/Function function1
# Description: This funct uses conditionals to change the values of the array
#       based on the first two inputted integers
# parameters: $a0 = address of numbers arr, $a1 = length of array
# return value: count
# registers to be used: $s1,$s2,$t1-$t4
############################################################################
function1:
    la          $s0, numbers1       # $s0 = reset address of list `numbers1` from .data
    la          $s1, numbers2       # $s0 = reset address of list `numbers1` from .data

    li          $t2, 0              # $t2 = 0 (index counter)
    li          $t4, 0              # $t2 = 0 (change counter)

    j		    function1Loop       # jump to function1Loop

function1Loop:
    beq		    $t2, $s2, function1End	    # if $t2 == $s2 then function1End

    lw		    $t3, 0($s0)		    # $a0 = index at array pointer

    blt		    $t3, $t0, function1LoopConditional	# if $t3 < $t1 then function1LoopConditional

    # else:
    sw		    $t3, 0($s1)		    # 

    addi	    $s0, $s0, 4			# $s0 += 4
    addi	    $s1, $s1, 4			# $s1 += 4
    addi	    $t2, $t2, 1			# $t2++

    j		    function1Loop       # jump to function1Loop         

function1LoopConditional:
    sub		    $t3, $t3, $t1		# $t3 = $t3 - $t1
    
    sw		    $t3, 0($s1)         #

    addi	    $s0, $s0, 4			# $s0 += 4
    addi	    $s1, $s1, 4			# $s1 += 4
    addi	    $t2, $t2, 1			# $t2++
    addi	    $t4, $t4, 1			# $t4++

    j		    function1Loop       # jump to function1Loop

function1End:
    # dispay "The number of changed items is "
    la          $a0, msg4           # $a0 = address of msg4
    li          $v0, 4              # $v0 = 4  --- this is to call print_string()
    syscall                         # call print_string()

    move 	    $a0, $t4		    # $a0 = $t0
    li          $v0, 1              # $v0 = 1  --- this is to call print_int()
    syscall                         # call print_int()

    # print ":\n"
    la          $a0, colon          # $a0 = address of colon
    li          $v0, 4              # $v0 = 4  --- this is to call print_string()
    syscall                         # call print_string()

    j           printArray          # jump to printArray

calculateMaxCount:
    addi        $s4, $s4, 1         # $s4++

    bgt		    $t4, $s3, updateMaxCount	# if $t4 > $s3 then updateMaxCount

    blt		    $s4, $s5, startFunction1	# if $s4 < $s5 then startFunction1
    
    j           exit                # jump to exit


updateMaxCount:
    move        $s3, $t4            # $s3 = $t4

    blt		    $s4, $s5, startFunction1	# if $s4 < $s5 then startFunction1

    j		    exit                # jump to exit
         
exit:
    # display "The maximum number of changed items is "
    la          $a0, msg6           # $a0 = address of msg6
    li          $v0, 4              # $v0 = 4  --- this is to call print_string()
    syscall                         # call print_string()

    move 	    $a0, $s3		    # $a0 = $s3
    li          $v0, 1              # $v0 = 1  --- this is to call print_int()
    syscall                         # call print_int()

    # print ":\n"
    la          $a0, colon          # $a0 = address of colon
    li          $v0, 4              # $v0 = 4  --- this is to call print_string()
    syscall                         # call print_string()

    jr		    $ra				    # return
