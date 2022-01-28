###########################################################
#  Assignment #: 4
#  Name: Tyler Fichiera
#  ASU email: tfichier@asu.edu
#  Course: CSE/EEE230, TTh 1:30pm
#  Description: 
###########################################################

# data declarations: declare variable names used in program, storage allocated in RAM
.data
    # create strings with the specified values
    msg1: .asciiz "How many T-shirts would you like to order?\n"
    msg2: .asciiz "Do you have a discount coupon? Enter 1 for yes. (any other integer will indicate no discount)\n"
    msg3: .asciiz "Your total payment is $"
    msg4: .asciiz "Invalid Number of T-shirts.\n"

# program code is contained below under .text
.text
    .globl main # define a global function main

# the program begines execution at main()
main:
    # collect number of t-shirts
    la          $a0, msg1           # $a0 = address of msg1
    li          $v0, 4              # $v0 = 4  --- this is to call print_string()
    syscall                         # call print_string()

    li          $v0, 5              # $v0 = 5
    syscall                         # call read_int()
    move 	    $t0, $v0		    # $t0 = $v0 (number of t-shirts)

    # check if # of shirts is >= 0
    slt		    $t2, $t0, $zero	    # $t0 = $a0 < $zero ? 1 : 0
    bne		    $t2, $zero, invalid_tshirts	# if $t0 != $zero then invalid_tshirts

    # ask the user if they have a discount code
    la          $a0, msg2           # $a0 = address of msg1
    li          $v0, 4              # $v0 = 4  --- this is to call print_string()
    syscall                         # call print_string()

    li          $v0, 5              # $v0 = 5
    syscall                         # call read_int()
    move 	    $t1, $v0		    # $t1 = $v0 (discount code)

    # check if # of shirts is < 50
    slti	    $t2, $t0, 50		# $t2 = ($t0 < 50) ? 1 : 0
    bne		    $t2, $zero, pricing_tier1	# if $t0 != $zero then pricing_tier1

    # check if # of shirts is < 100
    slti	    $t2, $t0, 100		# $t2 = ($t0 < 100) ? 1 : 0
    bne		    $t2, $zero, pricing_tier2	# if $t0 != $zero then pricing_tier2

    # else (# of shirts > 100) jump to pricing_tier3
    j		    pricing_tier3		# jump to pricing_tier3

    jr		    $ra				    # return

invalid_tshirts:
    # if not valid display invalid number msg
    la          $a0, msg4           # $a0 = address of msg4
    li          $v0, 4              # $v0 = 4  --- this is to call print_string()
    syscall                         # call print_string()

    jr		    $ra				    # return

# pricing when less than 50 shirts are bought
pricing_tier1:
    li		    $t3, 7		        # $t3 = 7 
    mult	    $t0, $t3			# $t0 * $t3 = Hi and Lo registers
    mflo	    $t4					# copy Lo to $t4

    # check for discount
    li          $t5, 1
    beq		    $t1, $t5, apply_discount	# if $t1 == $zero then apply_discount

    # else dont apply discount
    j		    no_discount			# jump to no_discount
    
    jr		    $ra				    # return

# pricing when 50-99 shirts are bought
pricing_tier2:
    li		    $t3, 6		        # $t3 = 6
    mult	    $t0, $t3			# $t0 * $t3 = Hi and Lo registers
    mflo	    $t4					# copy Lo to $t4

    # check for discount
    li          $t5, 1
    beq		    $t1, $t5, apply_discount	# if $t1 == $zero then apply_discount

    # else dont apply discount
    j		    no_discount			# jump to no_discount
 
    jr		    $ra				    # return

# pricing when more than 99 shirts are bought
pricing_tier3:
    li		    $t3, 5		        # $t3 = 7 
    mult	    $t0, $t3			# $t0 * $t3 = Hi and Lo registers
    mflo	    $t4					# copy Lo to $t4

    # check for discount
    li          $t5, 1
    beq		    $t1, $t5, apply_discount	# if $t1 == $zero then apply_discount

    # else dont apply discount
    j		    no_discount			# jump to no_discount

    jr		    $ra				    # return

apply_discount:
    # subract 5 dollars
    addi	    $t4, $t4, -5		# $t4 = $t4 + -5

    # display final price
    la          $a0, msg3           # $a0 = address of msg6
    li          $v0, 4              # $v0 = 4  --- this is to call print_string()
    syscall                         # call print_string()

    move 	    $a0, $t4		    # $a0 = $s3
    li          $v0, 1              # $v0 = 1  --- this is to call print_int()
    syscall                         # call print_int()
    
    jr		    $ra					# jump to $ra

no_discount:
    # display final price
    la          $a0, msg3           # $a0 = address of msg6
    li          $v0, 4              # $v0 = 4  --- this is to call print_string()
    syscall                         # call print_string()

    move 	    $a0, $t4		    # $a0 = $s3
    li          $v0, 1              # $v0 = 1  --- this is to call print_int()
    syscall                         # call print_int()

    jr		    $ra					# jump to $ra
