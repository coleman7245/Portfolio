# Name: coleman7245
# Project: Integer/Floating-point Division
# Last Update: 2/25/19

.text
.globl main

#Main thread of execution.
main:
	jal readInput #Call the read input method, and store the return address in ra.
	move $a0, $v0 #Move the first integer read into the first arguement register.
	move $a1, $v1 #Move the second integer read into the second arguement register. 
	jal divideFloatingPoint #Call the divide floating point number method, and store the return address in ra.
	jal divideInteger #Call the divide integer number method, and store the return address in ra.
	move $t0, $v0 #Move the remainder to the first temporary register. 
	move $t1, $v1 #Move the quotient to the second temporary register. 
	jal displayFloatQuotient #Call the display floating-point quotient method, and store the return address in ra.
	jal displayIntQuotient #Call the display integer quotient method, and store the return address in ra. 
	li $v0, 10 #Load the value for the exit system call.
	syscall #Exit the program.
	
readInput:
	li $v0, 4 #Load the value for print string system call.
	la $a0, in_message_1 #Load the address for the first input message.
	syscall #Print the string.
	li $v0, 5 #Load the value for the read integer system call.
	syscall #Read the integer from the user.
	move $t0, $v0 #Move the read value from its origin to a temporary register.
	li $v0, 4 #Load the value for print string system call.
	la $a0, in_message_2 #Load the address for the second input message.
	syscall #Print the string.
	li $v0, 5 #Load the value for the read integer system call.
	syscall #Read the integer from the user.
	move $v1, $v0 #Move the read value from its origin to the return value register.
	move $v0, $t0 #Move the read value from the temporary register to the return value register.
	jr $ra #Jump back to the main thread.
	
divideInteger:
	div $a0, $a1 #Divide the two arguements, and store the quotient and remainder in the lo and hi registers respectively. 
	mfhi $v1 #Move the remainder from the hi register.
	mflo $v0 #Move the quotient from the lo register.
	jr $ra #Jump back to the main thread.

divideFloatingPoint:
	mtc1 $a0, $f0 #Move the dividend to the floating-point register.
	mtc1 $a1, $f1 #Move the divisor to the floating-point register.
	cvt.s.w $f0, $f0 #Convert the dividend from integer to floating-point.
	cvt.s.w $f1, $f1 #Convert the divisor from integer to floating-point.
	div.s $f2, $f0, $f1 #Divide the numbers, and store them in another register.
	jr $ra #Jump back to the main thread.

displayIntQuotient:
	li $v0, 4 #Load the value for print string system call.
	la $a0, out_message_int1 #Load the integer quotient message.
	syscall #Print the string.
	li $v0, 1 #Load the value for the print integer system call.
	move $a0, $t0 #Move the quotient from the temporary register to the first arguement register.
	syscall #Print the integer.
	li $v0, 4 #Load the value for print string system call.
	la $a0, out_message_int2 #Load the address for the integer remainder message.
	syscall #Print the string.
	li $v0, 1 #Load the value for the print integer system call.
	move $a0, $t1 #Move the remainder from the temporary register to the first arguement register. 
	syscall #Print the integer.
	jr $ra #Jump back to the main thread.

displayFloatQuotient:
	li $v0, 4 #Load the value for print string system call.
	la $a0, out_message_fp #Load the address for the floating-point quotient message. 
	syscall #Print the string.
	li $v0, 2 #Load the value for the print floating-point number system call.
	mov.s $f12, $f2 #Move the floating-point quotient to the appropriate floating-point register. 
	syscall #Print the floating-point number.
	jr $ra #Jump back to the main thread.

#Data section.
.data

in_message_1: .asciiz "Input integer 1: "
in_message_2: .asciiz "\nInput integer 2: "
out_message_fp: .asciiz "\nFloating point result = " 
out_message_int1: .asciiz "\n\nInteger division quotient = "
out_message_int2: .asciiz " Remainder = "
