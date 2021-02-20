; This program's main goal was to process the inputs from the user/keyboard
; adding them to a stack storing the numbers as well as the operations conducted.
; The operations consisted of +, -, *, /, and ^. By checking the stack underflow,
; we notice how pushing and popping the values of the inputs can be conducted/determined. 
; The program was worked out to recognize the operations placed by the user, conducting the operation
; pushing the result back into the stack. By the user entering the expression and ending with =, the stack then knows to pop/print 
; the output which is stored in R5. Finally, within this program, if the user enters an unknown character/value which is a nonnumber or operator
; then the program prints "Wrong equation used".

; Partners: shreyav3, ajayka2

.ORIG x3000
	
;your code goes here
;Results:
;Register R5 holds the output

START
	JSR EVALUATE    ; jumps to EVALUATE label
	ADD R0, R0, #0  ; ADD 0 to R0, updating R0 register
	BRnp FINISH     ; heads to FINISH label
	JSR PRINT_HEX   ; jumps to PRINT_HEX label

FINISH
	HALT            ; done

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Utlized MP1 into the first part

;Throughout the whole program
;Register Table:
;R3- value to print in hexadecimal
;R0- is used for IO
;R1- temporary register
;R2- register that determines the character entered
;R4- keeps the value that is popped from the stack
;R5- is the output that stores the result of push/pop displaying as output
;R6- helps load in ASCII and R0 values
;R7- helps store the subroutine PC values

PRINT_HEX
	ST R7, SAVE_R7_PRINT  ; stores the label value into R7
	AND R6, R6, #0        ; R6 is initialized by adding 0, updating the register
	ADD R6, R5, #0        ; 0 is added to the current value of R5 into R6

SHIFT_LOOP              
	AND R1, R1, #0        ; R1 is initalized by adding 0, updating the register
    ADD R1, R1, #4        ; R1 is then added with 4 which updates R1

START_SHIFT
    AND R2, R2, #0        ; R2 is initialized
    AND R0, R0, #0        ; R0 is initialized
    ADD R0, R0, #4        ; R0 is then added with 4, updating the current value at R0

EXTRACT_LOOP
	ADD R2, R2, R2        ; R2 is shifted left
    ADD R6, R6, #0        ; R6 is added with 0, updating the current value at R6
    BRzp SHIFT            ; heads towards the SHIFT label
    ADD R2, R2, #1        ; R2 is incremented by 1, updating the current value at R2

SHIFT
   ADD R6, R6, R6         ; R6 is shifted left
   ADD R0, R0, #-1        ; R0 is decremented by 1, updating the current value at R0
   BRp EXTRACT_LOOP       ; heads towards the EXTRACT_LOOP label

DIGIT_PRINT_LOOP
	ADD R0, R2, #-9       ; R2 is added with -9 and stored into R0
	BRnz PRINT_NUMERICAL  ; heads towards the PRINT_NUMERICAL label
	LD R0, A              ; R0 is loaded with the ASCII value of 'A'
    ADD R0, R0, R2        ; R0 is then added with R2, updating R0 register
	ADD R0, R0, #-10      ; current value of R0 is added with -10, updating the current value at R0
	BRnzp DIG_LOOP_DONE   ; heads towards the DIG_LOOP_DONE label

PRINT_NUMERICAL
	LD R0, ZERO           ; R0 is loaded with the ASCII value of zero
	ADD R0, R0, R2        ; current value of R0 is then added with the current value of R2, updating the value at R0

DIG_LOOP_DONE
	OUT                   ; digit/value is printed
	ADD R1, R1, #-1       ; R1 is decremented, updating the current value at R1
	BRp START_SHIFT       ; heads towards START_SHIFT LABEL
	BRnzp RESULT          ; else heads towards the RESULT label

RESULT
	LD R7, SAVE_R7_PRINT  ; loads the value of the label SAVE_R7_PRINT into R7
	RET                   ; return


;.FILLS needed
SAVE_R7_PRINT .BLKW #1
ZERO .FILL x30
A .FILL #65
ASCII .FILL x37
SAVE_R7_EVALUATE .BLKW #1
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;R1- temporary register
;R2- register that determines the character entered
;R4- keeps the value that is popped from the stack
;R5- is the output that stores the result of push/pop displaying as output
;R3- value to print in hexadecimal

EVALUATE
;your code goes here
	ST R7, SAVE_R7_EVALUATE

KEYIN
	GETC              ; asks user for input
	OUT               ; digit/value is printed
	LD R2, CHAREQUALS ; the character is an equals sign, load the value into R2
	ADD R2, R2, R0    ; use the temporary register R2 to store what it originally had plus the input from user
	BRz PRODUCT       ; head to PRODUCT label

	LD R2, CHARSPACE  ; the character is a space, load the value into R2
	ADD R2, R0, R2    ; use the temporary register R2 to store what it originally had plus the input from user
	BRz KEYIN         ; head to the KEYIN label

	LD R2, LESS9      ; the character is less than or equal to 9, load the value into R2
	ADD R2, R0, R2    ; use the temporary register R2 to store what it originally had plus the input from user
	BRp CHECKEXP      ; head to the CHECKEXP label
    BRnzp SKIP        ; else head to the SKIP label

CHECKEXP
	LD R1, CHAREXP    ; load the value at the label CHAREXP into R1
	ADD R1, R1, R0    ; add the current value at R0 with the value at R1, updating R1 as a whole
	BRnp WRONGRES     ; head to the WRONGRES label

SKIP
	LD R2, GREATER    ; the character is greater than or equal to 0, load the value into R2
	ADD R2, R0, R2    ; use the temporary register R2 to store what it originally had plus the input from user
	BRzp OPERATIONS   ; head to the OPERATIONS label

	ADD R6, R0, #0    ; add the current value at R0 with 0 storing into R6
	JSR POP           ; POP

	ADD R5, R5, #0    ; add the current value at R5 into R5 incase for underflow
	BRp WRONGRES      ; head to WRONGRES label

	ADD R4, R0, #0    ; add the current value at R0 with 0 into R4, updating the register
	JSR POP           ; POP

	ADD R5, R5, #0    ; add 0 with the current value at R5, updating the R5 register
	BRp WRONGRES      ; head to the WRONGRES label

	ADD R3, R0, #0    ; add the current value at R0 with 0 into R3, updating the register
	LD R2, CHARADD    ; load R2 with the value found at the label CHARADD
	ADD R2, R6, R2    ; add the current value at R2 with the value stored at R6, updating the R2 register as a whole
	BRnp SUBTRACT     ; head to the SUBTRACT label

	JSR PLUS          ; jump to PLUS label
	JSR PUSH          ; jump to PUSH label
	BRnzp KEYIN       ; head to KEYIN label to loop through

OPERATIONS
	LD R2, GREATER    ; load the value at the label GREATER into R2
	ADD R0, R0, R2    ; add current value at R2 with R0, updating the value at R0
	JSR PUSH          ; PUSH
	ADD R5, R5, #0    ; add the current value at R5 with 0, updating the R5 register
	BRp WRONGRES      ; head to the WRONGRES label
	BRnzp KEYIN       ; head to the KEYIN label 

SUBTRACT
	LD R2, CHARMINUS  ; load the value at the label CHARMINUS into R2
	ADD R2, R6, R2    ; add the current value of R2 with the value at R6 into R2, updating the register
	BRnp MULTIPLY     ; head to the MULTIPLY label
	JSR MIN           ; jump to MIN label
	JSR PUSH          ; jump to PUSH label
	BRnzp KEYIN       ; head to KEYIN label

MULTIPLY
	LD R2, CHARMULT  ; load the value at the label CHARMULT into R2
	ADD R2, R6, R2   ; add the current value at R2 with R6, updating the R2 register
	BRnp POWER       ; head to POWER label
	JSR MUL          ; jump to MUL label
	JSR PUSH         ; jump to PUSH label
	BRnzp KEYIN      ; head to KEYIN label

POWER
	LD R6, CHAREXP   ; load the value at the label CHAREXP into R6
	NOT R6, R6       ; negate the current value stored at R6
	ADD R6, R6, #1   ; add 1 with the current value at R6, updating the R6 regitster 
	ADD R6, R0, R6   ; add R6 with R0 into R6, updating the R6 register as a whole
	BRnp DIVIDE      ; head to the DIVIDE label
	JSR EXP          ; jump to the EXP label
	JSR PUSH                    ; jump to the PUSH label
	LD R7, SAVE_R7_EVALUATE     ; load the SAVE_R7_EVALUATE label value into R7
	RET                         ; return

DIVIDE 
	LD R2, CHARDIV   ; load the value at the label CHARDIV into R2
	ADD R2, R6, R2   ; add the current value at R2 with R6 into R2, updating the register as a whole
	ADD R4, R4, #0   ; add 0 with R4, updating the current value at R4
	BRz WRONGRES     ; else head to the WRONGRES label
	JSR DIV          ; jump to the DIV label
	JSR PUSH         ; jump to the PUSH label
	BRnzp KEYIN      ; head to the KEYIN label

PRODUCT
	LD R2, STACK_TOP     ; load the STACK_TOP label's value into R2
	LD R1, STACK_START   ; load the STACK_START label's value into R1
	ADD R2, R2, #1       ; add 1 to the current value at R2, updating the value at R2 
	NOT R1, R1           ; negate the value stored at R1, updating the value at R1
	ADD R1, R1, #1       ; add 1 with R1 to R1, updating the R1 register as a whole
	ADD R2, R2, R1       ; add R1 with R2 into R2, updating the current value at R2
	BRz CORRECTRES       ; head to the CORRECTRES label
	BRnzp WRONGRES       ; head to the WRONGRES label

CORRECTRES
	JSR POP              ; head to POP label
	ADD R5, R0, #0       ; add the current value at R0 with 0 into R5, updating the current value at R5
	AND R0, R0, #0       ; reinitialize R0
	BRnzp EVALRET        ; head to the EVALRET label

WRONGRES
	LEA R0, WRONG           ; place the value at WRONG label into R0
	PUTS                    ; PUTS
	BRnzp EVALRET           ; head to the EVALRET label

EVALRET
	LD R7, SAVE_R7_EVALUATE ; load the value at SAVE_R7_EVALUATE label into R7
	RET                     ; return

;.FILLS added here
CHAREQUALS .FILL xFFC3
CHARSPACE  .FILL xFFE0
GREATER    .FILL xFFD0
LESS9      .FILL xFFC7
CHARADD    .FILL xFFD5
CHARMINUS  .FILL xFFD3
CHARMULT   .FILL xFFD6
CHARDIV    .FILL xFFD1
CHAREXP    .FILL xFFA2
WRONG      .STRINGZ "Wrong equation used"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	
;your code goes here
	ADD R0, R3, R4    ; add the current value at R4 with R3 into R0
	RET               ; return
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	
;your code goes here
	ADD R0, R4, #0    ; add the current value at R4 with 0 into R0
	NOT R0, R0        ; negate the value stored at R0
	ADD R0, R0, #1    ; add 1 with R0, into R0, updating the current value
	ADD R0, R3, R0    ; add R0 with the value stored in R3 into R0, updating the current value at R0
	RET               ; return
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	
;your code goes here
	ST R7, VALR7      ; store the value at label VALR7 into R7
	JSR MAGNITUDE     ; jump to MAGNITUDE label

LOOP
	ADD R3, R3, #0    ; add current value at R3 with 0, updating the current value at R3
	BRz FINLOOP       ; head to FINLOOP label
	ADD R0, R4, R0    ; add the current value at R0 with R4, into R0, updating the register
	ADD R3, R3, #-1   ; decrement the current value at R3 by 1 back into R3
	BRnzp LOOP        ; head to LOOP label

FINLOOP
	ADD R2, R2, #-1   ; decrement the current value at R2 by 1, storing it into R2
	BRnp MULRET       ; head to the MULRET label
	NOT R0, R0        ; negate the current value at R0
    ADD R0, R0, #1    ; increment the current value at R0 by 1, updating the R0 register

MULRET
	LD R2, VALR2      ; load VALR2 label's value into R2
	LD R7, VALR7      ; load VALR7 label's value into R7
	RET               ; return

;.BLKW's here
VALR2 .BLKW #1       
VALR7 .BLKW #1

MAGNITUDE
	ST R2, VALR2      ; store the value at the VALR2 label into R2
	AND R2, R2, #0    ; re-initialize R2
	ADD R3, R3, #0    ; add the current value at R3 with 0 into R3
	BRzp LOOP1        ; head to LOOP1 label

	ADD R2, R2, #1    ; increment R2 by 1, updating the register
	NOT R3, R3        ; negate the current value at R3
	ADD R3, R3, #1    ; add the current value at R3 with 1, updating the R3 register 

LOOP1
	ADD R4, R4, #0   ; add current value at R4 with 0, into R4
	BRzp LOOP2       ; head to LOOP2 label

	ADD R2, R2, #1   ; increment R2 by 1, updating the register as a whole
	NOT R4, R4       ; negate current value at R4
	ADD R4, R4, #1   ; add the current value at R4 with 1, updating the R4 register 

LOOP2
	AND R0, R0, #0   ; re-initalize R0
	RET              ; return
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	
;your code goes here
	ADD R4, R4, #0  ; add the current value at R4 with 0 into R4
	BRz WRONGRES    ; head to WRONGRES label 

	ST R7, VALR7    ; store the value at VALR7 label into R7
	JSR MAGNITUDE   ; jump to MAGNITUDE label
	NOT R4, R4      ; negate current value R4
	ADD R4, R4, #1  ; increment current value at R4 by 1

REPEAT
	ADD R3, R3, #0  ; add 0 to the current value at R3 into R3
	BRn FINISHLOOP  ; head to the FINISHLOOP label

	ADD R3, R3, R4  ; add the current value at R4 with R3, into R3, updating the R3 register
	ADD R0, R0, #1  ; increment the current value at R0 by 1
	BRnzp REPEAT    ; head to REPEAT label

FINISHLOOP
	ADD R0, R0, #-1  ; decrement the current value at R0 by 1
	ADD R2, R2, #-1  ; decrement the current value at R2 by 1
	BRnp DIVRET      ; head to the DIVRET label

	NOT R0, R0       ; negate the current value at R0
	ADD R0, R0, #1   ; increment the current value at R0 by 1

DIVRET
	LD R2, VALR2     ; load the value at label VALR2 into R2
	LD R7, VALR7     ; load the value at label VALR7 into R7
	RET              ; return
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
;your code goes here
	ST R5, EXP_SAVE_R5  ; store the current value at EXP_SAVE_R5 label into R5
	ST R6, EXP_SAVE_R6  ; store the current value at EXP_SAVE_R6 label into R6

	ADD R6, R3, #0      ; add the current value at R3 with 0 into R6, updating the register
	ADD R0, R3, R4      ; add R3 with R4 into R0, updating the R0 register
	ADD R4, R4, #0      ; add R4 with 0, updating the current value at R4
	BRp OUTEREXPLOOP    ; head to OUTEREXPLOOP label

	AND R0, R0, #0      ; re-initialize R0 
	ADD R0, R0, #1      ; increment R0 by 1
	LD R6, EXP_SAVE_R6  ; load EXP_SAVE_R6 label's value into R6
	RET                 ; return

OUTEREXPLOOP
	ADD R4, R4, #-1     ; decrement the current value at R4 by 1
	BRz EXPDONE         ; head to the EXPDONE label

	ADD R0, R6, #0      ; add the current value of R6 with 0 into R0
	ADD R5, R3, #0      ; add the current value at R3 with 0 into R5
	
EXPLOOP
	ADD R0, R0, #-1     ; decrement R0 by 1
	BRz OUTEREXPLOOP    ; head to the OUTEREXPLOOP label

	ADD R3, R5, R3      ; add the current value at R3 with R5 into R3
	BRnzp EXPLOOP       ; head to the EXPLOOP label

EXPDONE
	ADD R0, R3, #0      ; add the current value at R3 with 0 into R0
	LD R5, EXP_SAVE_R5  ; load the label's value into R5 
	LD R6, EXP_SAVE_R6  ; load the label's value into R6
	RET                 ; return

;.BLKW's here
EXP_SAVE_R5  .BLKW #1
EXP_SAVE_R6  .BLKW #1
	
;GIVEN
	
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACK_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;


.END
