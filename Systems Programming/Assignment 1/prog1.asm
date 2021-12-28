TITLE 	PROG1 {EXE} 	Display name and title of program title on the output screen
;------------------------------------------------------------
        .MODEL  SMALL
        .STACK
;------------------------------------------------------------
        .DATA
PARLIST LABEL   BYTE            ;Name parameter list
MAXNLEN DB      20              ; maximum length of name
ACTULEN DB      ?               ; no. of characters entered
KBNAME  DB      20 DUP (' ')    ; entered name
PROMPT  DB      'Name? ', '$'
PROMPT2 DB	0AH, 'Name -> ', '$'
PROGTTL DB	'Title -> Assignment1-Program1', 0DH, 0AH, '$'
;------------------------------------------------------------
        .CODE
MAIN    PROC  	FAR  
        MOV     AX,@data        ;Initialize segment registers
        MOV     DS,AX           
             
        CALL	DISPTTL		;Display title
	CALL    DISPRMT         ;Display prompt
        CALL    INPNM           ;Provide for input of name
        CMP     ACTULEN,00      ;Name entered
        JE      TATA
        
        CALL    DISPNM          ;Display entered name
TATA:
        MOV     AH,4CH          ;End processing
        INT     21H

MAIN    ENDP
;               Display title:
;               --------------
DISPTTL 	PROC    NEAR
        MOV     AH,09H          ;Request display
        LEA     DX,PROGTTL
        INT     21H
        RET
DISPTTL ENDP
;               Display prompt:
;               --------------
DISPRMT PROC	NEAR    
        MOV     AH,09H          ;Request display
        LEA     DX,PROMPT
        INT     21H
        RET
DISPRMT ENDP
;               Accept input of name:
;               --------------------
INPNM   PROC	NEAR    
        MOV     AH,0AH          ;Request keyboard
        LEA     DX,PARLIST      ;Input
        INT     21H
	MOV	BL,ACTULEN
	MOV	KBNAME[BX],'$'	;Replace Enter with $
        RET
INPNM   ENDP
;               Display Name:
;               ------------
DISPNM  PROC	NEAR
	MOV     AH,09H          ;Request display
        LEA     DX,PROMPT2
        INT     21H
        LEA     DX,KBNAME
        INT     21H
        RET
DISPNM  ENDP
        END     MAIN