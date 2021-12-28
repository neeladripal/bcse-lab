TITLE	PROG7 {EXE}	Validate second number is less than the first
;------------------------------------
	.MODEL	SMALL
	.STACK
;------------------------------------
	.DATA
INPMSG1	DB	"First Number? ", "$"
INPMSG2 DB	"Second Number? ", "$"
EQMSG	DB	"Both numbers are equal", "$"
GMSG	DB	"First number is greater than the second number", "$"
LMSG	DB	"First number is less than the second number", "$"

NUM1	DW	?
NUM2	DW	?
;------------------------------------
	.CODE
MAIN	PROC	FAR
	MOV	AX,@data		; Initialize segment registers
	MOV	DS,AX

	; Input first number
	LEA  	DX,INPMSG1
	CALL	DISP			; Display prompt
	CALL	INPT			; Request input of first number
	MOV	NUM1,AX
	
	; Input second number
	LEA  	DX,INPMSG2
	CALL	DISP			; Display prompt
	CALL	INPT			; Request input of second number
	MOV	NUM2,AX

	; Comparison
	MOV	AX,NUM1
	MOV	BX,NUM2
	CMP	AX,BX			; Compare the two numbers
	JNE	NOTEQUAL
EQUAL:	
	LEA	DX,EQMSG		; If the numbers are equal
	JMP	TATA

NOTEQUAL:	
	JL	LESS
	LEA	DX,GMSG			; If the first number is greater
	JMP	TATA
LESS:	
	LEA	DX,LMSG			; If the first number is less
TATA:
	CALL	DISP			; Display the result
	MOV	AH,4CH			; Terminate
	INT 	21H

MAIN	ENDP

;	Display message
;	--------------------
DISP	PROC	NEAR
	MOV	AH,09H
	INT 	21H
	RET
DISP	ENDP

;	Accept input of number
;	----------------------
INPT	PROC	NEAR
	PUSH 	DX

	MOV 	DX,0000H
	MOV	CL,4
GETCH:
	MOV 	AH,01H			; Request character input
    	INT 	21H
	CMP 	AL,0DH			; Check if Enter
	JE 	DONE
	CMP 	AL,0AH 			; Check if LineFeed
	JE 	DONE

	SHL 	DX,CL 			; Left shift 4 bits
	SUB 	AL,48 			; Find the numerical value from character
	CMP 	AL,9
	JLE 	ISNUM   		; Check if 0-9 or A-F
	SUB 	AL,7  			; for A-F

ISNUM:
	OR 	DL,AL			; Store the character
	JMP 	GETCH			; Loop to take next character
DONE:
	MOV 	AX,DX			; Store the number
	POP 	DX
	RET

INPT 	ENDP

END 	MAIN