TITLE	PROG6 {EXE}	Take a character from keyboard and print it
;--------------------------------------------
	.MODEL	SMALL
	.STACK
;--------------------------------------------
	.DATA
INPMSG	DB	"Enter character: ", "$"
OUTMSG	DB	0DH, 0AH, "Your character -> ", "$"
;--------------------------------------------
	.CODE
MAIN	PROC	FAR
	MOV	AX,@data	; Initialize segment registers
	MOV	DS,AX
TLOOP:
	CALL	PROMPT		; Display prompt
	CALL	CHINPT		; Request input
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
	MOV	DL,AL		; Display character
	INT 	21H
	RET
DISP 	ENDP

END	MAIN