#Author: coleman7245
#Project: Find the maximum value in the array.
#Date: 3/1/19

.data #Data section

strA: .asciiz "Original Array:\n" #Title for the original array.
strB: .asciiz "Second Array:\n" #Title for the max value array.
newline: .asciiz "\n" #Newline for creating new lines.
space: .asciiz " " #Space for creating spaces.

MatBegin: .word 100, 170, 350, 100 #Array of integers.
		  .word 305, 330, 105, 235
		  .word 197, 195, 90, 205
		  .word 80, 209, 110, 215
		  
MaxVals: .space 16 #Space directive for allocating space for the max value array.
		 .align 2 #Alignment directive for aligning memory.
.text #Text section
.globl main #Main thread.

main:
	la $t0, MatBegin #Load the address of the original array
	la $t1, MaxVals #Load the address of the max value array.
	addi $t2, $t0, 52 #Upper limit for LOOP2
	addi $t3, $t0, 16 #Upper limit for LOOP1
	LOOP1: #Outer loop for column selection.
	move $v0, $zero #Initialize max value to zero.
	move $t4, $t0 #Initialize $t4 to the address of the original array.
		LOOP2: #Inner loop for row selection.
			move $a0, $v0 #Move the max value to $a0.
			lw $a1, 0($t4) #Load a value of the original array into $a1.
			jal findMaxValue #Call findMaxValue procedure.
			addi $t4, $t4, 16 #Select the next row of the array.
		blt $t4, $t2, LOOP2 #If the address in $t4 is less than that of $t2, then loop again.
	sw $v0, 0($t1) #
	addi $t1, $t1, 4
	addi $t2, $t2, 4
	addi $t0, $t0, 4
	blt $t0, $t3, LOOP1
	la $a1, strB
	la $a2, newline
	la $a3, space
	jal printArray
	li $v0, 10
	syscall

findMaxValue:
	addi $sp, $sp, -4
	sw $s0, 0($sp)
	blt $a0, $a1, ifElse1
	move $v0, $a0
	j exit
	ifElse1: 
		move $v0, $a1
	exit:	
		lw $s0, 0($sp)
		addi $sp, $sp, 4	
		jr $ra
		
printArray:
	addi $sp, $sp, -4
	sw $s0, 0($sp)
	la $t0, MatBegin
	addi $t1, $t0, 64
	addi $t4, $t0, 12
	la $t2, MaxVals
	addi $t3, $t2, 16
	li $v0, 4
	la $a0, strA
	syscall
	LOOP3:
		li $v0, 1
		lw $a0, 0($t0)
		syscall
		li $v0, 4
		blt $t0, $t4, ifElse2
		la $a0, newline
		addi $t4, $t4, 16
		j CONTINUE
		ifElse2:
			la $a0, space
		CONTINUE:		
			syscall
			addi $t0, $t0, 4
			blt $t0, $t1, LOOP3
	li $v0, 4
	la $a0, strB
	syscall
	LOOP4:
		li $v0, 1
		lw $a0, 0($t2)
		syscall
		li $v0, 4
		la $a0, space
		syscall
		addi $t2, $t2, 4
		blt $t2, $t3, LOOP4
	lw $s0, 0($sp)
	addi $sp, $sp, 4
	jr $ra
	
