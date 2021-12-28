TITLE	PROG9 {EXE}	Loop until the user decides to quit
;--------------------------------------------
	.MODEL	SMALL
	.STACK
;--------------------------------------------
	.DATA
INPMSG	DB	"Enter q to quit: ", "$"
OUTMSG	DB	0DH, 0AH, "Your character -> ", "$"
EXITMSG	DB	0DH, 0AH, "Quitting...", "$"
;--------------------------------------------
	.CODE
MAIN	PROC	FAR
	MOV	AX,@data	; Initialize segment registers
	MOV	DS,AX
TLOOP:
	LEA	DX,INPMSG	; Display input prompt
	MOV	AH,09H
	INT 	21H
	CALL	CHINPT		; Request input character
	LEA	DX,OUTMSG	; Display output message
	MOV	AH,09H
	INT 	21H
	CALL	DISPCH 		; Request character display
	CMP	BL,'q'		; Check if entered character is 'q'
	JNE	TLOOP		; else loop
TATA:
	LEA	DX, EXITMSG
	MOV	AH,09H
	INT 	21H		; Show terminating message
	MOV	AH,4CH		; Terminate
	INT 	21H

MAIN	ENDP

;	Character Input
;	---------------
CHINPT	PROC	NEAR
	MOV	AH,01H
	INT 	21H
	MOV	BL,AL
	RET
CHINPT 	ENDP

;	Character display
;	-----------------
DISPCH 	PROC	NEAR
	MOV	AH,02H
	MOV	DL,BL		; Display character
	INT 	21H
	MOV	DL,' '
	INT	21H
	RET
DISPCH 	ENDP

END	MAIN