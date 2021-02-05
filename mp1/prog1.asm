;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	                        ; fill the histogram with zeroes 
	AND R6,R6,#0		    ; put a zero into R6
	LD R1,NUM_BINS		    ; initialize loop count to 27
	ADD R2,R0,#0		    ; copy start of histogram into R2

	                        ; loop to fill histogram starts here
HFLOOP	
    STR R6,R2,#0		    ; write a zero into histogram
	ADD R2,R2,#1		    ; point to next histogram entry
	ADD R1,R1,#-1		    ; decrement loop count
	BRp HFLOOP		        ; continue until loop count reaches zero

	                        ; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		    ; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		    ; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		    ; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		    ; point R1 to start of string

	                        ; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		    ; read the next character from the string
	BRz PRINT_HIST		    ; found the end of the string

	ADD R2,R2,R3		    ; subtract '@' from the character
	BRp AT_LEAST_A		    ; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		    ; load the non-alpha count
	ADD R6,R6,#1		    ; add one to it
	STR R6,R0,#0		    ; store the new non-alpha count
	BRnzp GET_NEXT		    ; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		    ; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

                            ; note that we no longer need the current character
                            ; so we can reuse R2 for the pointer to the correct
                            ; histogram entry for incrementing
ALPHA	
    ADD R2,R2,R0		    ; point to correct histogram entry
	LDR R6,R2,#0		    ; load the count
	ADD R6,R6,#1		    ; add one to it
	STR R6,R2,#0		    ; store the new count
	BRnzp GET_NEXT		    ; branch to end of conditional structure

                            ; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		    ; subtract '`' - '@' from the character
	BRnz NON_ALPHA		    ; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		    ; compare with 'z'
	BRnz ALPHA		        ; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		    ; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		    ; point to next character in string
	BRnzp COUNTLOOP		    ; go to start of counting loop



PRINT_HIST

; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments

; This particular part of the code prints out all of the histogram bins
; calculated by the beginning part of the program. For each histogram bin, one register keeps
; track of the character that needs to be printed. The other register keeps track of the 
; address of the numerical value that is inside the bin. Both registers are incremented 
; when proceeding onto the next bin. There is an outerloop which keeps track of the number of 
; bins to print. Two loops are used to print digits. The first loop is used to count the number of digits that are printed
; and the second loop is used to keep track of the number of bits to be extracted from numerical value of a current bin 
; and essentially replace a digit. Then in order to print the numerical value stored at the current bin, four bits need to be extracted
; and be put into another register. The register store values that are converted into ASCII value representing the digits which is converted into 
; ASCII value representing the digit to be printed onto the monitor. 

; Partners: shreyav3, ajayka2

; Register Table:
; R0 serves as a loop counter which keeps track of the right number of bits to be extracted from the 
;    current value stored at bin being printed
; R1 is used to keep track of the character linked with the current bin to be printed
; R2 is used to keep track of the address of the current bin to be printed
; R3 serves as a loop counter that keeps track of the number of bins that have been printed so far
; R4 is used to hold the numerical value of the current bin being printed
; R5 is used to hold the numerical value of the first digit stored at R4
; R6 is used as another loop counter which keeps track of the number of digits that would be printed to the screen
;    for the current bin

	LD R2, HIST_ADDR     ; load HIST_ADDR (histogram bin) into R2 register
	LD R1, NEG_AT        ; load the negative @ into R1 register
	ADD R1, R1, #-1      ; add the current stored value at R1 with -1 in order to invert -@ to +@
	NOT R1, R1           ; current value stored at R1 is negated, and positive @ is stored in R1
	LD R3, NUM_BINS	     ; NUM_BINS contains 27 (number of bins printed for outerloop) which is loaded into R3

CHAR_PRINT            
	ADD R0, R1, #0       ; the current value stored in R1 is added with 0 and stored into R0
	OUT                  ; character is printed 
	LD R0, SPACE         ; loads SPACE (ascii space character value) into R0, updating the value at R0
	OUT                  ; character is printed 

SHIFT_LOOP
	LDR R4, R2, #0       ; R4 is loaded with the current value stored at R2
	AND R6, R6, #0       ; R6 is initialized
	ADD R6, R6, #4       ; current value at R6 is added with 4, which updates R6 containing 4 
                         ; (4 digits that must be printed for each bin)

START_SHIFT
	AND R5, R5, #0       ; R5 is initialized 
	AND R0, R0, #0       ; R0 is re initialized 
	ADD R0, R0, #4       ; current value at R0 is added with 4, updating R0 to 4 (number of times R4 is shifted into R5)

EXTRACT_LOOP
	ADD R5, R5, R5       ; R5 is shifted left to make space for the next bit from R4
	ADD R4, R4, #0       ; checks the most significant bit for R4
	BRzp SHIFT           ; if most significant bit is 0, 1 is not added to R5 and goes to the SHIFT label
	ADD R5, R5, #1       ; else, current value stored at R5 is added with 1, updating R5 to the current value

SHIFT
	ADD R4, R4, R4       ; R4 is shifted left
	ADD R0, R0, #-1      ; R0 bit counter is decremented by 1
	BRp EXTRACT_LOOP     ; keeps shifting until R0 hits 0

DIGIT_PRINT_LOOP
	ADD R0, R5, #-9      ; current value of R5 is added with -9, updating R0
	BRnz PRINT_NUMERICAL ; if digit is 0-9, goes to PRINT_NUMERICAL label
	LD R0, A             ; else, if digit is A-F, R0 is loaded with the ASCII value of 'A'
	ADD R0, R0, R5       ; current value of R0 is added with current value at R5, updating a new value into R0
	ADD R0, R0, #-10     ; current value of R0 is added with -10, updating current value at R0
	BRnzp DIG_LOOP_DONE  ; heads to the DIG_LOOP_DONE label, prints through OUT

PRINT_NUMERICAL
	LD R0, ZERO          ; loads ASCII value of '0' into R0
	ADD R0, R0, R5       ; current value at R0 is added with current value at R5, updating R0 in general

DIG_LOOP_DONE
	OUT                  ; digit/value is printed 

	ADD R6, R6, #-1      ; current value at R6 is added with -1, updating R6 as a whole (R6 decrements)
	BRp START_SHIFT      ; if the value is positive, head to START_SHIFT label
	LD R0, NEWLINE       ; ASCII value at NEWLINE is loaded into R0
	OUT                  ; character is printed 
	ADD R3, R3, #-1      ; current value at R3 is added with -1, updating R3 as a whole (R3 decrements)
	BRz DONE             ; heads to DONE label to print all the bins

	ADD R1, R1, #1       ; current value at R1 is added with 1, updating R1 in general to become the next ASCII character to be printed
	ADD R2, R2, #1       ; current value at R2 is added with 1, updating R2 in general to become the address of the next bin
	BRnzp CHAR_PRINT     ; heads to the CHAR_PRINT label

DONE	
    HALT		         ; done


; the data needed by the program
NUM_BINS	.FILL #27	  ; 27 loop iterations
NEG_AT		.FILL xFFC0	  ; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	  ; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	  ; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00   ; histogram starting address
STR_START	.FILL x4000	  ; string starting address

; the data needed by the printing part of the program
SPACE       .FILL x0020   ; contains value at ASCII space character 
ZERO        .FILL #48     ; contains value at ASCII zero character
A           .FILL #65     ; contains value at ASCII letter A character
NEWLINE     .FILL x000A   ; contains value at ASCII newline character

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING    .STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
