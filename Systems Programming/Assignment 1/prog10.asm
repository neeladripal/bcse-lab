TITLE	PROG10 {EXE}		Display A-Z
;--------------------------------------------
	.MODEL SMALL
	.STACK
	.DATA
;--------------------------------------------
	.CODE
MAIN	PROC	FAR
	MOV	AX,@data	; Initialize segment registers
	MOV	DS,AX
	
	MOV 	CL,26		; Initialize counter
	MOV 	BL,'A'		; First character is 'A'
	MOV	AH,02H

DLOOP:
	MOV	DL,BL		; Print character
	INT 	21H
	INC	BL		; Increment to next character
	MOV	DL,' '		; Print space
	INT	21H
	LOOP 	DLOOP		; Loop until all characters are printed

TATA:
	MOV	AH,4CH		; Terminate
	INT 	21H
MAIN	ENDP

END 	MAIN