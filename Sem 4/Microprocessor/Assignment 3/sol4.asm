	   LXI H,201EH		; place the address conatining N in HL pair
	   MOV C,M 			; transfer the value of N in register C
	   LXI H,2500H 		; set up HL to point to the first byte address
	   LXI D,2500H 		; set up DL to point to the first byte address

LOOP1: INX H 			; increment HL to point to the next address
	   INX D 			; increment DE to point to the next address
	   DCR C 			; decrement value of N
	   JNZ LOOP1 		; continue the loop N times
	   DCX H 			; set up HL to point to Nth address
	   DCX D 			; set up DE to point to Nth address
	   LDA 201FH 		; place the address containing M in accumulator
	   MOV C,A 			; transfer the value of M in register C

LOOP2: INX D 			; increment DE to point to the next address
	   DCR C 			; decrement value of M
	   JNZ LOOP2 		; continue the loop M times, set up DE to point to (N + M)th address
	   LDA 201EH 		; place the address conatining N in accumulator
	   MOV C,A 			; transfer the value of N in register C

LOOP3: MOV A,M 			; transfer the contents of address specified by HL into accumulator
	   STAX D 			; store the contents of accumulator in address specified by DE
	   MVI M,00 		; store 00H in address specified by HL
	   DCX H 			; increment HL to point to the previous address
	   DCX D 			; increment DE to point to the previous address
	   DCR C 			; decrement value of N
	   JNZ LOOP3 		; continue the loop N times
	   HLT 				; stop