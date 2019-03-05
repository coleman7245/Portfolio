; Floating Point Conversion Partial
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

flt16_add_RA    .BLKW 1              ; return addess storage

flt16_add       ST R7,flt16_add_RA   ; save return address
                                     ; your code goes here
                LD R7,flt16_add_RA   ; restore return address
                RET
;------------------------------------------------------------------------------
flt16_sub                            ; Result is Param1 minus Param2
                                     ; your code goes here
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
                                     ; your code goes here 
                RET
;------------------------------------------------------------------------------
flt16_get_val                        ; Result is mantissa from Param1 plus implicit 1
                LD R0, Param1        ; your code goes here
		BRz END
                LD R1, VAL_MASK
		LD R2, IMPL1_MASK
                AND R0, R1, R0
                ADD R0, R0, R2
END             ST R0, Result
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
                                     ; your code goes here
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


