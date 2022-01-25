.data
top: .asciiz " /\ "
doubleSpace: .asciiz "  "
quadSpace: .asciiz "    "
endl: .asciiz "\n"
numTree: .asciiz "Enter the number of trees to print (must be greater than 0): "
sizeTree: .asciiz "Enter the size of one tree (must be greater than 1): "
invalid: .asciiz "Invalid entry!\n"

.text
promptTrees: NOP
# Print number of trees prompt
la $a0, numTree
li $v0, 4
syscall
# Take in integer input for number of trees
li $v0, 5
syscall
# Store number of trees in $s0
move $s0, $v0
# If greater than 0, continue
bgtz $s0, promptSize
# Else, print error with new line and loop
la $a0, invalid
li $v0, 4
syscall
b promptTrees

promptSize: NOP
# Print size of trees prompt
la $a0, sizeTree
li $v0, 4
syscall
# Take in integer input for size of trees
li $v0, 5
syscall
# Store size of trees in $s1
move $s1, $v0
# If greater than 1, continue
bgt $s1, 1, continue
# Else, print error with new line and loop
la $a0, invalid
li $v0, 4
syscall
b promptSize

# Everything is good to go, number of trees is stored in $s0 and size in $s1
continue: NOP
# Store number of trees $s0 - 1 in $s2 as buffer for loops
move $s2, $s0
addi $s2, $s2, -1
# Store size $s1 - 1 in $s3 as buffer for loops
move $s3, $s1
addi $s3, $s3, -1
# Print tops of trees
# First top of tree
# Space
li $a0, 0x20
li $v0, 11
syscall
# Back slash
li $a0, 0x2F
li $v0, 11
syscall
# Forward slash
li $a0, 0x5C
li $v0, 11
syscall
# Rest of tops if needed
bgtz $s2, loopTop
b loopLeaves

loopTop: NOP
# Print spacing
la $a0, quadSpace
li $v0, 4
syscall
# Print top of tree
# Back slash
li $a0, 0x2F
li $v0, 11
syscall
# Forward slash
li $a0, 0x5C
li $v0, 11
syscall
# Loop invariant
addi $s2, $s2, -1
bgtz $s2, loopTop

loopLeaves: NOP
# Reset number of trees buffer for inner loop
move $s2, $s0
addi $s2, $s2, -1
# New line
la $a0, endl
li $v0, 4
syscall
# Back slash
li $a0, 0x2F
li $v0, 11
syscall
# Double space
la $a0, doubleSpace
li $v0, 4
syscall
# Forward slash
li $a0, 0x5C
li $v0, 11
syscall
# Inner loop for leaves of extra trees if needed
bgtz $s2, loopExtraLeaves
b loopLeavesInvariant
loopExtraLeaves: NOP
# Double space
la $a0, doubleSpace
li $v0, 4
syscall
# Back slash
li $a0, 0x2F
li $v0, 11
syscall
# Double space
la $a0, doubleSpace
li $v0, 4
syscall
# Forward slash
li $a0, 0x5C
li $v0, 11
syscall
# Inner loop invariant using number of trees buffer
addi $s2, $s2, -1
bgtz $s2, loopExtraLeaves
loopLeavesInvariant: NOP
# Outer loop invariant using size buffer
addi $s3, $s3, -1
bgtz $s3, loopLeaves

width: NOP
# New line
la $a0, endl
li $v0, 4
syscall
# Reset number of trees buffer for loop
move $s2, $s0
addi $s2, $s2, -1
# Dash
li $a0, 0x2D
li $v0, 11
syscall
# Dash
li $a0, 0x2D
li $v0, 11
syscall
# Dash
li $a0, 0x2D
li $v0, 11
syscall
# Dash
li $a0, 0x2D
li $v0, 11
syscall
# Loop for widths of trees if necessary
bgtz $s2, loopWidth
b trunk
loopWidth: NOP
# Double space
la $a0, doubleSpace
li $v0, 4
syscall
# Dash
li $a0, 0x2D
li $v0, 11
syscall
# Dash
li $a0, 0x2D
li $v0, 11
syscall
# Dash
li $a0, 0x2D
li $v0, 11
syscall
# Dash
li $a0, 0x2D
li $v0, 11
syscall
# Inner loop invariant using number of trees buffer
addi $s2, $s2, -1
bgtz $s2, loopWidth

# Reset size buffer for outer loop
divu $s3, $s1, 2
trunk: NOP
# Reset number of trees buffer for inner loop
move $s2, $s0
addi $s2, $s2, -1
# New line
la $a0, endl
li $v0, 4
syscall
# Space
li $a0, 0x20
li $v0, 11
syscall
# Vertical character
li $a0, 0x7C
li $v0, 11
syscall
# Vertical character
li $a0, 0x7C
li $v0, 11
syscall
# Inner loop for trunks of extra trees if needed
bgtz $s2, loopExtraTrunks
b loopTrunksInvariant
loopExtraTrunks: NOP
# Print spacing
la $a0, quadSpace
li $v0, 4
syscall
# Vertical character
li $a0, 0x7C
li $v0, 11
syscall
# Vertical character
li $a0, 0x7C
li $v0, 11
syscall
# Inner loop invariant using number of trees buffer
addi $s2, $s2, -1
bgtz $s2, loopExtraTrunks
loopTrunksInvariant: NOP
# Outer loop invariant using size buffer
addi $s3, $s3, -1
bgtz $s3, trunk

exit: NOP
# Exit program cleanly
li $v0, 10
syscall
