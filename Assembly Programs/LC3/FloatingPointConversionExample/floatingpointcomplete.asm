; Floating Point Conversion Complete
; Author: Derek Coleman
; Last Update: 3/5/19
;
; Description: Implements the manipulation of half precision (16-bit) floating point numbers

;------------------------------------------------------------------------------
; Begin reserved section: do not change ANYTHING in reserved section!

                .ORIG x3000
                BR Main

; A jump table defined as an array of addresses
Functions       .FILL flt16_add      ; (option 0)
                .FILL flt16_sub      ; (option 1)
                .FILL flt16_get_sign ; (option 2)
                .FILL flt16_get_exp  ; (option 3)
                .FILL flt16_get_val  ; (option 4)
                .FILL flt16_abs      ; (option 5)
                .FILL flt16_neg      ; (option 6)
                .FILL left_most1     ; (option 7)
                .FILL left_shift     ; (option 8)
                .FILL right_shift    ; (option 9)
                .FILL binary_or      ; (option 10)

Main            LEA R0,Functions     ; get base of jump table
                LD  R1,Option        ; get option to use, no error checking
                ADD R0,R0,R1         ; add index of array
                LDR R0,R0,#0         ; get address of function
                JSRR R0              ; call selected function
                HALT

; Parameters and return values for all functions
Option          .BLKW 1              ; which function to call
Param1          .BLKW 1              ; space to specify first parameter
Param2          .BLKW 1              ; space to specify second parameter
Result          .BLKW 1              ; space to store result
TempParam1      .BLKW 1              ; Temporary space for Param1
TempParam2      .BLKW 1              ;Temporary space for Param2

; You may add variables and functions after here as you see fit. You may use JSR
; within the code of flt16_add or other functions. However, this requires that
; you save and restore return addresses, otherwise a function will not be able
; to use JSR to call another subroutine. See flt16_add for an example of how to
; save and restore a return address. When will this scheme NOT work?

; Here are some useful constants:

SIGN_MASK       .FILL x8000          ; 1 in left most bit 
EXP_MASK        .FILL x001F          ; exactly 5 bits     
VAL_MASK        .FILL x03FF          ; exactly 10 bits    
IMPL1_MASK      .FILL x0400          ; 1 in the 11 bit    
ONE             .FILL #1             ; the number 1       
TEN             .FILL #10            ; the number 10      
SIXTEEN         .FILL #16            ; the value 16

; End reserved section: do not change ANYTHING in reserved section!
;------------------------------------------------------------------------------

; Local variables, this is how you will be tested for PA6
; Do not change the names!
X               .BLKW 1		     ; x value
Y               .BLKW 1              ; y value
signX           .BLKW 1              ; sign of X
expX            .BLKW 1              ; exponent of X
valX            .BLKW 1              ; mantissa of X
signY           .BLKW 1              ; sign of Y
expY            .BLKW 1              ; exponent of Y
valY            .BLKW 1              ; mantissa of Y
signSum         .BLKW 1              ; sign of sum
expSum          .BLKW 1              ; exponent of sum
valSum          .BLKW 1              ; mantissa of sum
expDiff         .BLKW 1              ; save difference
left1           .BLKW 1              ; location of left most 1

flt16_add_RA    .BLKW 1              ; return addess storagehttp://www.cs.colostate.edu/~cs270/.Spring14/assignments/PA5/PA5.html
flt16_get_exp_RA .BLKW 1
flt16_sub_RA     .BLKW 1             ;

flt16_add       ST R7,flt16_add_ra   ; save return address

                LD R0,Param1         ; read X parameter
                ST R0,X              ; store X parameter
                LD R0,Param2         ; read Y parameter
                ST R0,Y              ; store Y parameter

                ; STEP ONE) Extract fields from operands
                JSR flt16_get_sign   ; extract x sign
                LD R0,Result         ; load x sign
                ST R0,signX          ; store x sign
                JSR flt16_get_exp    ; extract x exponent
                LD R0,Result         ; load x exponent
                ST R0,expX           ; store x exponent
                JSR flt16_get_val    ; extract x mantissa
                LD R0,Result         ; load x mantissa
                ST R0,valX           ; store x mantissa

                LD R0,Y              ; load y operand
                ST R0,Param1         ; prepare for call
                JSR flt16_get_sign   ; extract y sign
                LD R0,Result         ; load y sign
                ST R0,signY          ; store y sign
                JSR flt16_get_exp    ; extract y exponent
                LD R0,Result         ; load y exponent
                ST R0,expY           ; store y exponent
                JSR flt16_get_val    ; extract y mantissa
                LD R0,Result         ; load y mantissa
                ST R0,valY           ; store mantissa

		LD R0, expX
		ST R0, expSum
		LD R0, valX
		LD R1, signX
		BRz X_POSITIVE
		NOT R0, R0
		ADD R0, R0, #1
X_POSITIVE	ST R0, valX
		LD R0, valY
		LD R1, signY
		BRz Y_POSITIVE
		NOT R0, R0
		ADD R0, R0, #1
Y_POSITIVE	ST R0, valY
		LD R0, valX
		LD R1, valY
		ADD R2, R1, R0
		ST R2, valSum
		LD R0, valSum
		ST R0, Param1
		JSR left_most1
		LD R0, Result
		ADD R0, R0, #-10
		BRz sum_positive
		BRp sum_right_shift
		LD R1, expSum
		ADD R1, R0, R1
		ST R1, expSum
		NOT R0, R0
		ADD R0, R0, #1
		ST R0, Param2
		JSR left_shift
		LD R0, Result
		ST R0, valSum
		BRnzp sum_complete
sum_right_shift ST R0, Param2
		LD R1, expSum
		ADD R0, R0, R1
		ST R0, expSum
		JSR right_shift
		LD R0, Result
		ST R0, valSum
		BRnzp sum_complete
sum_positive	ST R0, valSum
		AND R0, R0, #0
		ST R0, signSum
sum_complete	LD R1,expSum         ; load sum exponent
                ST R1,Param1         ; setup left shift
                LD R2,TEN            ; load constant 10
                ST R2,Param2         ; setup left shift
                JSR left_shift       ; call left shift
                LD R1,Result         ; load result
                LD R0,signSum        ; load sum sign
                LD R2,valSum         ; load sum mantissa
                LD R3,VAL_MASK       ; load mantissa mask
                AND R2,R2,R3         ; remove implicit bit
                ADD R0,R0,R1         ; add sum exponent
                ADD R0,R0,R2         ; add sum mantissa
                ST R0,Result         ; store result
                LD R7,flt16_add_RA   ; restore return address
                RET
;------------------------------------------------------------------------------
flt16_sub       ST R7, flt16_sub_RA  ; Result is Param1 minus Param2
		LD R0, Param1
		ST R0, TempParam1
		LD R0, Param2
		ST R0, Param1
		JSR flt16_neg 
		LD R0, Result
		ST R0, Param2
		LD R0, TempParam1
		ST R0, Param1
		JSR flt16_add
		LD R0, Result
                LD R7, flt16_sub_RA  ; your code goes here
                RET
;------------------------------------------------------------------------------
flt16_get_sign                       ; Result is 0 if Param1 is positive, 1 otherwise
                AND R0, R0, #0       ; Initialize result
                LD R1, Param1        ; Get first parameter
                BRzp return_sign     ; Sign is 0 (zero or positive)
                ADD  R0, R0, #1      ; Sign is 1 (negative)
return_sign     ST R0, Result        ; Save the result
                RET
;------------------------------------------------------------------------------
flt16_get_exp                        ; Result is biased exponent from Param1
                ST R7, flt16_get_exp_RA
		        LD R0, Param1
		        AND R1, R1, #0
		        ADD R1, R1, #10
		        ST R1, Param2
		        JSR right_shift
		        LD R0, Result
		        LD R1, EXP_MASK
		        AND R0, R0, R1
		        ST R0, Result
		        LD R7, flt16_get_exp_RA
                RET
;------------------------------------------------------------------------------
flt16_get_val                        ; Result is mantissa from Param1 plus implicit 1
                LD R0, Param1
		BRz END              ; your code goes here
		LD R1, VAL_MASK
		AND R0, R1, R0
		LD R2, IMPL1_MASK
                ADD R0, R0, R2
END		ST R0, Result
                RET
;------------------------------------------------------------------------------
flt16_abs                            ; Result is absolute value of Param1
                LD R0, Param1        ; your code goes here
                BRp RETURN_VALUE
		LD R1, SIGN_MASK
		NOT R1, R1
		AND R0, R0, R1
RETURN_VALUE    ST R0, Result
                RET
;------------------------------------------------------------------------------
flt16_neg                            ; Result is negative value of Param1
                LD R0, Param1        ; your code goes here
		BRz IF_ZERO
                LD R1, SIGN_MASK
                BRp IF_POSITIVE
                NOT R1, R1
IF_POSITIVE     ADD R0, R0, R1
		ADD R0, R0, #1
IF_ZERO         ST R0, Result                
                RET
;------------------------------------------------------------------------------
left_most1                           ; Result is bit position of leftmost 1 in Param1
                AND R0, R0, #0       ; your code goes here
		ADD R0, R0, #-1
		AND R1, R1, #0
		LD R2, ONE
		LD R3, Param1
		BRz END0
LOOP1		AND R4, R2, R3
		BRz LOOP2
		ADD R0, R1, #0
LOOP2		ADD R1, R1, #1
		ADD R2, R2, R2
		BRz END0
		BR LOOP1
END0		ST R0, Result   
                RET
;------------------------------------------------------------------------------
left_shift                           ; Result is Param1 shifted left by Param2 bits
                LD R0, Param1        ; your code goes here
                LD R1, Param2
		BRnz EXIT
AGAIN           ADD R0, R0, R0
                ADD R1, R1, #-1
                BRp AGAIN
EXIT            ST R0, Result
                RET
;------------------------------------------------------------------------------
right_shift                          ; Result is Param1 shifted right by Param2 bits
                LD R0, Param1        ; your code goes here
		AND R2, R2, #0
		ADD R2, R2, #1
		AND R3, R3, #0
		ADD R3, R3, #1
		AND R4, R4, #0
		AND R5, R5, #0
		LD R1, Param2
		BRnz EXIT1
LOOP3		ADD R2, R2, R2
		ADD R1, R1, #-1
		BRp LOOP3
LOOP4		AND R4, R0, R2
		BRz IF0
		ADD R5, R5, R3
IF0		ADD R3, R3, R3
		ADD R2, R2, R2
		BRnp LOOP4
EXIT1		ST R5, Result
                RET
;------------------------------------------------------------------------------
binary_or                            ; Result is a bitwise OR of Param1 and Param2
                AND R3, R3, #0       ; your code goes here
                LD R0, Param1
                LD R1, Param2
                NOT R0, R0
                NOT R1, R1
                AND R3, R0, R1
                NOT R3, R3
                ST R3, Result
                RET
;------------------------------------------------------------------------------
                .END


