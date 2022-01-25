#------------------------------------------------------------------------
# Created by:  Wang, Edwin
#              Ekwang
#              25 November 2019 
#
# Assignment:  Lab 5: Subroutines
#              CSE 12, Computer Systems and Assembly Language
#              UC Santa Cruz, Fall 2019
# 
# Description: Library of subroutines used to convert an array of
#              numerical ASCII strings to ints, sort them, and print
#              them.
# 
# Notes:       This file is intended to be run from the Lab 5 test file.
#------------------------------------------------------------------------

.text

j  exit_program                # prevents this file from running
                               # independently (do not remove)

#------------------------------------------------------------------------
# MACROS
#------------------------------------------------------------------------

#------------------------------------------------------------------------
# print new line macro

.macro lab5_print_new_line
    addiu $v0 $zero   11
    addiu $a0 $zero   0xA
    syscall
.end_macro

#------------------------------------------------------------------------
# print string

.macro lab5_print_string(%str)

    .data
    string: .asciiz %str

    .text
    li  $v0 4
    la  $a0 string
    syscall
    
.end_macro

#------------------------------------------------------------------------
# add additional macros here

#------------------------------------------------------------------------
# push regs used in syscalls so values are not overwritten
#------------------------------------------------------------------------
.macro lab5_push_a0_v0

    subi  $sp    $sp   8
    sw    $a0   ($sp)
    sw    $v0  4($sp)

.end_macro

#------------------------------------------------------------------------
# pop regs used in syscalls so values are not overwritten
#------------------------------------------------------------------------
.macro lab5_pop_a0_v0

    lw    $a0   ($sp)
    lw    $v0  4($sp)
    addi  $sp    $sp   8

.end_macro

#------------------------------------------------------------------------
# main_function_lab5_19q4_fa_ce12:
#
# Calls print_str_array, str_to_int_array, sort_array,
# print_decimal_array.
#
# You may assume that the array of string pointers is terminated by a
# 32-bit zero value. You may also assume that the integer array is large
# enough to hold each converted integer value and is terminated by a
# 32-bit zero value
# 
# arguments:  $a0 - pointer to integer array
#
#             $a1 - double pointer to string array (pointer to array of
#                   addresses that point to the first characters of each
#                   string in array)
#
# returns:    $v0 - minimum element in array (32-bit int)
#             $v1 - maximum element in array (32-bit int)
#-----------------------------------------------------------------------
# REGISTER USE
# $s0 - pointer to int array
# $s1 - double pointer to string array
# $s2 - length of array
# $s3 - Edwin's buffer of various uses
#-----------------------------------------------------------------------

.text
main_function_lab5_19q4_fa_ce12: nop
    
    subi  $sp    $sp   20       # decrement stack pointer
    sw    $ra 16($sp)           # push return address to stack
    sw    $s0 12($sp)           # push save registers to stack
    sw    $s1  8($sp)
    sw    $s2  4($sp)
    sw    $s3  0($sp)
    
    move  $s0    $a0            # save ptr to int array
    move  $s1    $a1            # save ptr to string array
    
    move  $a0    $s1            # load subroutine arguments
    jal   get_array_length      # determine length of array
    move  $s2    $v0            # save array length in $s2
    
                                # print input header
                                 
    lab5_print_string("\n----------------------------------------")
    lab5_print_string("\nInput string array\n")
                       
    # Register Usage
    # $s0 - Ptr to int array
    # $s1 - Double ptr to str array
    # $s2 - Array length
                       
                                # load subroutine arguments
    move  $a0 $s2               # load array length
    move  $a1 $s1               # load double pointer to str array
    jal   print_str_array       # print array of ASCII strings
    
                                # load subroutine arguments
    move  $a0 $s2               # load array size
    move  $a1 $s1               # load double pointer string array
    move  $a2 $s0        # using hard coded data address
    jal   str_to_int_array      # convert string array to int array
                                
                                # load subroutine arguments
    move  $a0 $s2               # load array size
    move  $a1 $s0               # load integer array. Make sure array is loaded from arg $a2 of str_to_int_array
    jal   sort_array            # sort int array
    lab5_push_a0_v0

                                # print output header    
    lab5_print_new_line
    lab5_print_string("\n----------------------------------------")
    lab5_print_string("\nSorted integer array\n")
    
    ########################### # add code (delete this comment)
                                # load subroutine arguments
    move  $a0 $s2               # load array size
    move  $a1 $s0               # load integer array. Make sure array is loaded from arg $a2 of str_to_int_array
    jal   print_decimal_array   # print integer array as decimal
                                # save output values
    
    lab5_print_new_line
    
    ########################### # add code (delete this comment)
                                # move min and max values from array
                                # to output registers
                                
    lab5_pop_a0_v0        
    lw    $ra 16($sp)           # pop return address from stack
    lw    $s0 12($sp)           # pop save registers from stack
    lw    $s1  8($sp)
    lw    $s2  4($sp)
    lw    $s3  0($sp)
    addi  $sp    $sp   20       # increment stack pointer
    
    jr    $ra                   # return from subroutine

#-----------------------------------------------------------------------
# print_str_array	
#
# Prints array of ASCII inputs to screen.
#
# arguments:  $a0 - array length (optional)
# 
#             $a1 - double pointer to string array (pointer to array of
#                   addresses that point to the first characters of each
#                   string in array)
#
# returns:    n/a
#-----------------------------------------------------------------------
# REGISTER USE
# $t0 - Copy of address
# $t1 - Double pointer index
# $t2 - Array length
#-----------------------------------------------------------------------

.text
print_str_array: NOP 
    # Initialize registers listed above
    move $t0, $a1
    li $t1, 0
    # li $t2, 3
    move $t2, $a0
    printLoop: NOP
    # If looped enough times, break
    bge $t1, $t2, finishPrintLoop
    # Print the string
    lw $a0, 0($t0)
    li $v0, 4
    syscall
    # Space
    li $a0, 0x20
    li $v0, 11
    syscall
    # Increment index and address
    addi $t0, $t0, 4
    addi $t1, $t1, 1
    j printLoop
    finishPrintLoop: NOP
    jr  $ra
    
#-----------------------------------------------------------------------
# str_to_int_array
#
# Converts array of ASCII strings to array of integers in same order as
# input array. Strings will be in the following format: '0xABCDEF00'
# 
# i.e zero, lowercase x, followed by 8 hexadecimal digits, with A - F
# capitalized
# 
# arguments:  $a0 - array length (optional)
#
#             $a1 - double pointer to string array (pointer to array of
#                   addresses that point to the first characters of each
#                   string in array)
#
#             $a2 - pointer to integer array
#
# returns:    n/a
#-----------------------------------------------------------------------
# REGISTER USE
# $t0 - Copy of array length
# $t1 - Copy of double pointer to string array
# $t2 - Copy of pointer to integer array
# $t3 - Index of number of strings examined
#-----------------------------------------------------------------------

.text
str_to_int_array: nop
    move $t0 $a0
    move $t1 $a1
    move $t2 $a2
    move $t3 $zero
    str_to_int_array_loop: nop
    lw $a0 0($t1)
    addiu $t1 $t1 4
    subi  $sp    $sp   20       # decrement stack pointer
    sw    $ra 16($sp)           # push return address to stack
    sw    $t0 12($sp)           # push save registers to stack
    sw    $t1  8($sp)
    sw    $t2  4($sp)
    sw    $t3  0($sp)
    jal str_to_int
    lw    $ra 16($sp)           # pop return address from stack
    lw    $t0 12($sp)           # pop save registers from stack
    lw    $t1  8($sp)
    lw    $t2  4($sp)
    lw    $t3  0($sp)
    addi  $sp    $sp   20       # increment stack pointer
    sw $v0 0($t2)               # store result in address $t2
    addiu $t2 $t2 4
    addiu $t3 $t3 1
    blt $t3 $t0 str_to_int_array_loop
    jr   $ra

#-----------------------------------------------------------------------
# str_to_int	
#
# Converts ASCII string to integer. Strings will be in the following
# format: '0xABCDEF00'
# 
# i.e zero, lowercase x, followed by 8 hexadecimal digits, capitalizing
# A - F.
# 
# argument:   $a0 - pointer to first character of ASCII string
#
# returns:    $v0 - integer conversion of input string
#-----------------------------------------------------------------------
# REGISTER USE
# $t0 - Buffer for resulting character
# $t1 - Buffer for resulting number
# $t2 - Index of how many characters examined
# $t4 - String Address Buffer
#-----------------------------------------------------------------------

.text
str_to_int: nop
    # Beginning of outer loop
    startLoop: NOP
    # Store address of ASCII string in $t4
    la $t4, 0($a0)
    # Chop off 0x
    addiu $t4, $t4, 2
    # Store character index in $t2
    li $t2, 0
    loop: NOP
    # Then use hex ASCII of 'A' 0x41 for comparison (Less than means integer, greater than means character)
    lbu $t0, 0($t4)
    # If less than "A" subtract 48, else subtract 55
    blt $t0, 0x41, less
    sub $t0, $t0, 55
    b storeLoop
    less: NOP
    sub $t0, $t0, 48
    # Then store the resulting byte
    storeLoop: NOP
    sll $t1, $t1, 4
    addu $t1, $t1, $t0
    # Check loop invariant, add one to loop counter then if lower than 8, continue looping
    addiu $t4, $t4, 1
    addiu $t2, $t2, 1
    blt $t2, 8, loop
    # Finally, move the result from $t1 to the desired register
    move $v0, $t1
    # And return
    jr   $ra
    
#-----------------------------------------------------------------------
# sort_array
#
# Sorts an array of integers in ascending numerical order, with the
# minimum value at the lowest memory address. Assume integers are in
# 32-bit two's complement notation.
#
# arguments:  $a0 - array length (optional)
#             $a1 - pointer to first element of array
#
# returns:    $v0 - minimum element in array
#             $v1 - maximum element in array
#-----------------------------------------------------------------------
# REGISTER USE
# $t0 - First element
# $t1 - Second element
# $t2 - Third element
# $t4 - Buffer
#-----------------------------------------------------------------------

.text
sort_array: nop
# Sort values using $t4 as buffer
lw $t0 0($a1)
lw $t1 4($a1)
lw $t2 8($a1)
blt $t0, $t1, noSort1
move $t4, $t0
move $t0, $t1
move $t1, $t4
noSort1: NOP
blt $t1, $t2 noSort2
move $t4, $t1
move $t1, $t2
move $t2, $t4
noSort2: NOP
blt $t0, $t2 noSort3
move $t4, $t0
move $t0, $t2
move $t2, $t4
noSort3: NOP
blt $t0, $t1 doneSorting
move $t4, $t0
move $t0, $t1
move $t1, $t4
doneSorting: NOP
move $v0 $t0
move $v1 $t2
sw $t0 0($a1)
sw $t1 4($a1)
sw $t2 8($a1)
    jr   $ra


#-----------------------------------------------------------------------
# print_decimal_array
#
# Prints integer input array in decimal, with spaces in between each
# element.
#
# arguments:  $a0 - array length (optional)
#             $a1 - pointer to first element of array
#
# returns:    n/a
#-----------------------------------------------------------------------
# REGISTER USE
# $s0 - Copy of array length
# $s1 - Copy of pointer to first element of array
# $s2 - Counter of number of elements printed
#-----------------------------------------------------------------------

.text
print_decimal_array: nop
    # Save $s0-$s2 registers to $sp
    subi  $sp    $sp   16        # decrement stack pointer
    sw    $ra  0($sp)            # push return address to stack
    sw    $s0  4($sp)            # push save registers to stack
    sw    $s1  8($sp)
    sw    $s2 12($sp)
    # Initialize $s0-$s2 registers to their values defined above
    move $s0 $a0
    move $s1 $a1
    move $s2 $zero
    print_decimal_array_loop: nop
        lw $a0 0($s1)
        addiu $s1 $s1 4
    	jal print_decimal
    	# Print space
    	li $a0 0x20
    	li $v0 11
    	syscall
    	addiu $s2 $s2 1
    	blt $s2 $s0 print_decimal_array_loop
    finished_decimal_array_loop: nop
    lw    $ra  0($sp)           # pop return address from stack
    lw    $s0  4($sp)           # pop save registers from stack
    lw    $s1  8($sp)
    lw    $s2 12($sp)
    addi  $sp    $sp   16       # increment stack pointer
    jr    $ra                   # jump to return address
    
#-----------------------------------------------------------------------
# print_decimal
#
# Prints integer in decimal representation using only syscalls 4 and 11.
#
# arguments:  $a0 - integer to print
#
# returns:    n/a
#-----------------------------------------------------------------------
# REGISTER USE
# $t0 - Copy of integer to print
# $t1 - 10 for printing and -1 for sign conversion
# $t2 - Resulting string (backwards)
# $t3 - Remainder storing
#-----------------------------------------------------------------------

.text
print_decimal: nop
    move $t0, $a0
    subiu $sp, $sp 4
    sw $a0, 0($sp)
    beqz $t0, print_zero
    bltz $t0, print_negative
    decimal_to_str: nop
    li $t1, 10
    move $t2, $zero
    decimal_to_str_recur: nop
    div $t0, $t1                  # Divide by 10
    mflo $t0                      # Store quotient in $t0
    mfhi $t3                      # Store remainder in $t3
    sll $t2, $t2, 8               # Shift resulting register
    addiu $t3, $t3, 48            # Cast to character
    addu $t2, $t2, $t3            # Store remainder into result
    bgtz $t0, decimal_to_str_recur# Recur if needed
    print_decimal_loop: nop
    move $a0, $t2
    srl $t2, $t2, 8
    li $v0, 11
    syscall
    bgtz $t2, print_decimal_loop
    finish_print_decimal: nop
    # Reset stack
    lw $a0, 0($sp)
    addiu $sp, $sp 4
    jr   $ra
    
print_zero: nop
li $a0 '0'
li $v0 11
syscall
j finish_print_decimal

print_negative: nop
li $a0 '-'
li $v0 11
syscall
li $t1 -1
div $t0 $t1
mflo $t0
j decimal_to_str

#-----------------------------------------------------------------------
# exit_program (given)
#
# Exits program.
#
# arguments:  n/a
#
# returns:    n/a
#-----------------------------------------------------------------------
# REGISTER USE
# $v0: syscall
#-----------------------------------------------------------------------

.text
exit_program: nop
    
    addiu   $v0  $zero  10      # exit program cleanly
    syscall
    
#-----------------------------------------------------------------------
# OPTIONAL SUBROUTINES
#-----------------------------------------------------------------------
# You are permitted to delete these comments.

#-----------------------------------------------------------------------
# get_array_length (optional)
# 
# Determines number of elements in array.
#
# argument:   $a0 - double pointer to string array (pointer to array of
#                   addresses that point to the first characters of each
#                   string in array)
#
# returns:    $v0 - array length
#-----------------------------------------------------------------------
# REGISTER USE
# $t0 - Copy of double pointer
#-----------------------------------------------------------------------

.text
get_array_length: nop
    # Set counter of length to zero
    li      $v0    -1
    move    $t0  $a0
    get_array_length_loop: nop
    lw      $t1  0($t0)
    addi   $v0  $v0  1
    addiu   $t0  $t0  4
    bgtz    $t1  get_array_length_loop
    # addiu   $v0  $zero  3       # replace with /code to
                                # determine array length
    jr      $ra
    
#-----------------------------------------------------------------------
# save_to_int_array (optional)
# 
# Saves a 32-bit value to a specific index in an integer array
#
# argument:   $a0 - value to save
#             $a1 - address of int array
#             $a2 - index to save to
#
# returns:    n/a
#-----------------------------------------------------------------------
# REGISTER USE
# 
#-----------------------------------------------------------------------
