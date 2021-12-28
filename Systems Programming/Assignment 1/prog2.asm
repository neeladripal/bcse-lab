TITLE	PROG2 {EXE}	Convert a letter from uppercase to lowercase
;--------------------------------------------
	.MODEL	SMALL
	.STACK
;--------------------------------------------
	.DATA
INPMSG	DB	"Enter character: ", "$"
OUTMSG	DB	0DH, 0AH, "Your character in lowercase -> ", "$"
ERRMSG	DB	0DH, 0AH, "Character must be between A and Z", "$"
;--------------------------------------------
	.CODE
MAIN	PROC	FAR
	MOV	AX,@data	; Initialize segment registers
	MOV	DS,AX
TLOOP:
	CALL	PROMPT		; Display prompt
	CALL	CHINPT		; Request input
	
	MOV	AH,09H
	LEA 	DX,ERRMSG	; Load the error message
	
	CMP	AL,'A'		; Check if entered character >= 'A'
	JGE	OK
	INT	21H
	JMP	TATA	
OK:	
	CMP	AL,'Z'		; Check if entered character <= 'Z'
	JLE	CNVT
	INT	21H
	JMP	TATA
	
CNVT:
	ADD	AL,20H		; Convert to lowercase	
	CALL	DISP 		; Request display
TATA:
	MOV	AH,4CH		; Terminate
	INT 	21H

MAIN	ENDP

;	Display Prompt
;	--------------
PROMPT	PROC	NEAR
	MOV	AH,09H
	LEA 	DX,INPMSG
	INT 	21H
	RET
PROMPT	ENDP

;	Character Input
;	---------------
CHINPT	PROC	NEAR
	MOV	AH,01H
	INT 	21H
	RET
CHINPT 	ENDP

;	Character display
;	-----------------
DISP 	PROC	NEAR
	MOV	AH,09H
	LEA	DX,OUTMSG	; Display output message
	INT 	21H
	MOV	AH,02H
	MOV	DL,AL		; Display lowercase character
	INT 	21H
	RET
DISP 	ENDP

END	MAIN