TITLE	PROG8 {EXE}	Find maximum and minimum from an array of numbers
;------------------------------------
	.MODEL	SMALL
	.STACK
;------------------------------------
	.DATA
INPTMSG	DB	"Array of elements? ", "$"
OUTMX	DB	"Max -> ", "$"
OUTMN	DB	09H, "Min -> ", "$"

MAX	DW	0FFFFH
MIN	DW	7FFFH
;------------------------------------
	.CODE
MAIN	PROC	FAR
	MOV	AX,@data		; Initialize segment registers
	MOV	DS,AX

	MOV	AH,09H
	LEA 	DX,INPTMSG		; Display input prompt
	INT 	21H
INPTLOOP:
	CALL	INPT			; Request input
	
	CMP 	DX,MAX			; Check if number > max
	JLE	CONT1
	MOV	MAX,DX			; Update max

CONT1:	
	CMP	DX,MIN			; Check if number < min
	JGE	CONT2
	MOV	MIN,DX			; Update min

CONT2:
	CMP	AL,0DH			; Check if Enter
	JE	DISP
	CMP	AL,0AH			; Check if Linefeed
	JNE	INPTLOOP

DISP:
	LEA	DX,OUTMX
	MOV	AH,09H			; Display output message
	INT 	21H
	MOV	BX,MAX	
	CALL	OUTPT			; Display max number
	LEA	DX,OUTMN
	MOV	AH,09H			; Display output message
	INT 	21H
	MOV	BX,MIN
	CALL	OUTPT			; Display min number
		
TATA:
	MOV	AH,4CH			; Terminate
	INT 	21H

MAIN	ENDP

;	Accept input of number
;	----------------------
INPT	PROC	NEAR
	MOV 	DX,0000H
	MOV	CL,4
GETCH:
	MOV 	AH,01H			; Request character input
    	INT 	21H
	CMP 	AL,' '			; Check if Space
	JE 	DONE
	CMP	AL,0DH			; Check if Linefeed
	JE	DONE
	CMP	AL,0AH			; Check if Enter
	JE	DONE

	SHL 	DX,CL 			; Left shift 4 bits
	SUB 	AL,48 			; Find the numerical value from character
	CMP 	AL,9
	JLE 	ISNUM   		; Check if 0-9 or A-F
	SUB 	AL,7  			; for A-F

ISNUM:
	OR 	DL,AL			; Store the character
	JMP 	GETCH			; Loop to take next character
DONE:
	RET

INPT 	ENDP

;	Display Number
;	-----------
OUTPT 	PROC	NEAR
	MOV 	CL,4

    	MOV	DX,BX
    	MOV 	DL,DH 			; Take first 4 bits
    	SHR 	DL,CL
    	CALL	DISPCH

    	MOV 	DX,BX
    	MOV 	DL,DH 			; The next 4 bits
    	CALL	DISPCH

    	MOV 	DX,BX
    	SHR 	DL,CL 			; The next 4 bits
    	CALL	DISPCH

    	MOV 	DX,BX			; The last 4 bits
    	CALL	DISPCH
    	RET
OUTPT 	ENDP

;	Display hex-equivalent of decimal character
;	-------------------------------------------
DISPCH 	PROC 	NEAR
	AND 	DL,0FH
    	CMP 	DL,0AH
    	JL 	ISNUM2
    	ADD 	DL,7
ISNUM2:
        ADD 	DL,48
    	MOV 	AH,02H
    	INT 	21H
	RET
DISPCH 	ENDP

END 	MAIN