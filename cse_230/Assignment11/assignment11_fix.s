###########################################################
#  Assignment #: 11
#  Name: Tyler Fichiera
#  ASU email: tfichier@asu.edu
#  Course: CSE/EEE230, TTh 1:30pm
#  Description: TODO
###########################################################

# data declarations: declare variable names used in program, storage allocated in RAM
.data
    # create strings with the specified values
    msg1: .asciiz "Specify how many numbers should be stored in the array (at most 12):\n"
    msg2: .asciiz "First Array:\n"
    msg3: .asciiz "Enter a number:\n"
    msg4: .asciiz "First Array Content:\n"
    msg5: .asciiz "Please enter a number:\n"
    msg6: .asciiz "Second Array Content:\n"
    
    newLine: .asciiz "\n"

    maxArrayLenght: .word 12

    array1: .float 0.0
    array2: .float 0.0

    val: .asciiz "\nvalue here: \n" # for testing

# program code is contained below under .text
.text
    .globl main

# s0 = number of integers to read
# t0 = counter for reading numbers
# s1 = array of ints ??

main:
    # load variables
    lw          $s0, maxArrayLenght # $s0 = maxArrayLength
    li          $t0, 0              # t0 = 0
    la          $t1, array1         # $t1 = array1
    la          $t5, array2         # $t5 = array2

    li          $t2, 0              # $t2 = 0 (for loop counter)
    li          $t3, 3              # $t3 = 3 (for loop max)

    # collect length of array
    la          $a0, msg1           # $a0 = address of msg1
    li          $v0, 4              # $v0 = 4  --- this is to call print_string()
    syscall                         # call print_string()

    li          $v0, 5              # $v0 = 5
    syscall                         # call read_int()
    move 	    $s1, $v0		    # $s1 = $v0 (first inputted integer)

    la          $a0, msg2           # $a0 = address of msg2
    li          $v0, 4              # $v0 = 4  --- this is to call print_string()
    syscall                         # call print_string()

readArrayWhileLoop:
    beq         $t0, $s0, printArray    # if $t0 == $s0 then printArray (maxArrayLength)
    beq		    $t0, $s1, printArray    # if $t0 == $s1 then printArray (inputted counter)

    # collect number
    la          $a0, msg3           # $a0 = address of msg3
    li          $v0, 4              # $v0 = 4  --- this is to call print_string()
    syscall                         # call print_string()

    li          $v0, 6              # $v0 = 6
    syscall                         # call read_float()

    s.s         $f0, 0($t1)

    addi	    $t0, $t0, 1			# $t0++
    addi        $t1, $t1, 4         # $t1 += 4

    j           readArrayWhileLoop

printArray:
    la          $a0, msg4           # $a0 = address of msg4
    li          $v0, 4              # $v0 = 4  --- this is to call print_string()
    syscall                         # call print_string()

    li          $t0, 0              # $t0 = 0 (reset counter to 0)
    la          $t1, array1         # $t1 = float1

printArray1WhileLoop:
    beq         $t0, $s0, function1  # if $t0 == $s0 then function1 (maxArrayLength)
    beq		    $t0, $s1, function1  # if $t0 == $s1 then function1 (inputted counter)

    l.s         $f12, 0($t1)        # $f12 = float at index
    li          $v0, 2              # $v0 = 2  --- this is to call print_float()
    syscall                         # call print_float()

    la          $a0, newLine        # $a0 = address of newLine
    li          $v0, 4              # $v0 = 4  --- this is to call print_string()
    syscall                         # call print_string()

    addi	    $t0, $t0, 1			# $t0++
    addi        $t1, $t1, 4         # $t1 += 4

    j           printArray1WhileLoop

function1:
    beq         $t2, $t3, exit      # if $t2 == $t3 then exit

    # collect number
    la          $a0, msg5           # $a0 = address of msg5
    li          $v0, 4              # $v0 = 4  --- this is to call print_string()
    syscall                         # call print_string()

    li          $v0, 6              # $v0 = 6
    syscall                         # call read_float() (result stored in $f0)

    addi	    $t2, $t2, 1			# $t0++

    li          $t0, 0              # $t0 = 0 (reset counter to 0)
    la          $t1, array1         # $t1 = array1
    la          $t5, array2         # $t5 = array2

function1if:
    beq         $t0, $s0, printArray2  # if $t0 == $s0 then printArray2 (maxArrayLength)
    beq		    $t0, $s1, printArray2  # if $t0 == $s1 then printArray2 (inputted counter)

    l.s         $f10, 0($t1)        # $f10 = float at index (array1 value)

    s.s         $f10, 0($t5)

    addi	    $t0, $t0, 1			# $t0++
    addi        $t1, $t1, 4         # $t1 += 4

    addi        $t5, $t5, 4         # $t5 += 4

    c.le.s      $f0, $f10
    bc1t        function1if

    add.s       $f10, $f10, $f0

    addi        $t5, $t5, -4        # $t5 -= 4

    s.s         $f10, 0($t5)

    addi        $t5, $t5, 4         # $t5 += 4

    j           function1if

printArray2:
    la          $a0, msg6           # $a0 = address of msg6
    li          $v0, 4              # $v0 = 4  --- this is to call print_string()
    syscall                         # call print_string()

    li          $t0, 0              # $t0 = 0 (reset counter to 0)
    la          $t5, array2         # $t5 = array2

printArray2WhileLoop:
    beq         $t0, $s0, function1  # if $t0 == $s0 then function1 (maxArrayLength)
    beq		    $t0, $s1, function1  # if $t0 == $s1 then function1 (inputted counter)

    l.s         $f12, 0($t5)        # $f12 = float at index
    li          $v0, 2              # $v0 = 2  --- this is to call print_float()
    syscall                         # call print_float()

    la          $a0, newLine        # $a0 = address of newLine
    li          $v0, 4              # $v0 = 4  --- this is to call print_string()
    syscall                         # call print_string()

    addi	    $t0, $t0, 1			# $t0++
    addi        $t5, $t5, 4         # $t5 += 4

    j           printArray2WhileLoop

exit:
    jr		    $ra				    # return
