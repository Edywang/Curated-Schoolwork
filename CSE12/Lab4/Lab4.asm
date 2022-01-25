##########################################################################
# Created by:  Wang, Edwin
#              Ekwang
#              22 November 2019
#
# Assignment:  Lab 4: Sorting Floats
#              CMPE 012, Computer Systems and Assembly Language
#              UC Santa Cruz, Fall 2019
# 
# Description: This program takes in three IEEE 754 single precision FP args.
#              It then prints those args back, sorts them, prints them sorted
#              Converts them to decimal, and prints them again
# 
# Notes:       This program is intended to be run from the MARS IDE.
##########################################################################
# Pseudocode:
# 1. Store arguments in $s0 to $s2
# 2. Print back those arguments in $s0 to $s2
# 3. Compare each byte (In a temp register) against ASCII 'A"
# 4. If greater, subtract 55
# 5. else, subtract 48
# 6. Shift the storage register and add the registers
# 7. Bubble sort using built in FP instructions
# 8. Print using built in FP instructions
# 9. Print using built in decimal instructions

.data
progArgs: .asciiz "Program arguments:\n"
sortIEEE: .asciiz "Sorted values (IEEE 754 single precision floating point format):\n"
sortDec: .asciiz "Sorted values (Decimal):\n"
endl: .asciiz "\n"

.text
start: NOP
# First store arguments in $s0 to $s2
lw $s0, 0($a1)
lw $s1, 4($a1)
lw $s2, 8($a1)

printBack: NOP
la $a0, progArgs
li $v0, 4
syscall
# Print first arg back
la $a0, ($s0)
li $v0, 4
syscall
# Space
li $a0, 0x20
li $v0, 11
syscall
# Print second arg back
la $a0, ($s1)
li $v0, 4
syscall
# Space
li $a0, 0x20
li $v0, 11
syscall
# Print third arg back
la $a0, ($s2)
li $v0, 4
syscall
# Print new line
la $a0, endl
li $v0, 4
syscall
# Print new line
la $a0, endl
li $v0, 4
syscall

# Chop off "0x"
chop: NOP
la $s0, 2($s0)
la $s1, 2($s1)
la $s2, 2($s2)

# Then use hex ASCII of 'A' 0x41 for comparison (Less than means integer, greater than means character)
# To grab each byte to compare and cast to integer, ex. 0($a1), 1($a1), 2($a1), etc.
# Also store counter in $s6 of how many times we have looped
li $s6, 3

# Loop to cast each byte in $s0 to $s2 and "A" ASCII 0x41
# Reset index in $s7
startLoop: NOP
li $s7, 0
loop: NOP
lbu $t0, ($s0)
# If less than "A" subtract 48, else subtract 55
blt $t0, 0x41, less
addi $t0, $t0, -55
b storeLoop
less: NOP
addi $t0, $t0, -48
# Store in correct location depending on current argument being examined
storeLoop: NOP
beq $s6, 3, firstLoop
beq $s6, 2, secondLoop
beq $s6, 1, thirdLoop
# Chech loop invariant, add one to loop counter then if lower than 8, continue looping
finishLoop: NOP
addi $s0, $s0, 1
addi $s7, $s7, 1
blt $s7, 8, loop
afterLoop: NOP
addi $s6, $s6, -1
beq $s6, 2, afterFirst
beq $s6, 1, afterSecond
beq $s6, 0, afterThird

# Storing the byte in the oorrect spot, first number in $t1, second in $t2, third in $t3
firstLoop: NOP
sll $t1, $t1, 4
add $t1, $t1, $t0
b finishLoop
secondLoop: NOP
sll $t2, $t2, 4
add $t2, $t2, $t0
b finishLoop
thirdLoop: NOP
sll $t3, $t3, 4
add $t3, $t3, $t0
b finishLoop

# After a respective loop
afterFirst: NOP
la $s0, ($s1)
b startLoop
afterSecond: NOP
la $s0, ($s2)
b startLoop
# Finished loop, arguments not sorted stored in $t1, $t2, and $t3
afterThird: NOP

# Move FP values from registers $t1 to $t3 into $f0 to $f2 unsorted
mtc1 $t1, $f0
mtc1 $t2, $f1
mtc1 $t3, $f2

# Sort values using $f3 as buffer
c.le.s $f0, $f1
bc1t noSort1
movf.s $f3, $f0
movf.s $f0, $f1
movf.s $f1, $f3
noSort1: NOP
c.le.s $f1, $f2
bc1t noSort2
movf.s $f3, $f1
movf.s $f1, $f2
movf.s $f2, $f3
noSort2: NOP
c.le.s $f0, $f2
bc1t noSort3
movf.s $f3, $f0
movf.s $f0, $f2
movf.s $f2, $f3
noSort3: NOP
c.le.s $f0, $f1
bc1t doneSorting
movf.s $f3, $f0
movf.s $f0, $f1
movf.s $f1, $f3
doneSorting: NOP

# Print sorted values stored in $f0, $f1, and $f2 in IEEE
la $a0, sortIEEE
li $v0, 4
syscall
# Print first of sorted values
mfc1 $a0, $f0
li $v0, 34
syscall
# Space
li $a0, 0x20
li $v0, 11
syscall
# Print second of sorted values
mfc1 $a0, $f1
li $v0, 34
syscall
# Space
li $a0, 0x20
li $v0, 11
syscall
# Print third of sorted values
mfc1 $a0, $f2
li $v0, 34
syscall
# Print new line
la $a0, endl
li $v0, 4
syscall
# Print new line
la $a0, endl
li $v0, 4
syscall

# Print sorted values stored in $f0, $f1, and $f2 in decimal
la $a0, sortDec
li $v0, 4
syscall
# Print first of sorted values
mov.s $f12, $f0
li $v0, 2
syscall
# Space
li $a0, 0x20
li $v0, 11
syscall
# Print second of sorted values
mov.s $f12, $f1
li $v0, 2
syscall
# Space
li $a0, 0x20
li $v0, 11
syscall
# Print third of sorted values
mov.s $f12, $f2
li $v0, 2
syscall
# Print new line
la $a0, endl
li $v0, 4
syscall

exit: NOP
# Exit program cleanly
li $v0, 10
syscall
