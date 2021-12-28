	   LDA 204FH 			; store value of N in accumulator
	   MOV C,A 				; copy N in register C to use as counter
	   LDA 204EH 			; store contents of 204EH in accumulator
	   MOV B,A 				; copy value of the number in register B
	   LXI H,2050H 			; set up HL to point to the location of first byte
	   MVI D,00H 			; clear register D to store position of number, if found

LOOP:  MOV A,M 				; place the byte specified by content of HL in accumulator
	   INR D 				; one position moved, increment D
	   CMP B 				; compare (B) and accumulator
	   JNZ NEXT 			; if both are not equal, jump to next iteration
	   MOV A,D 				; copy position in accumulator
	   STA 204DH 			; store the position in 204DH
	   HLT 					; stop

NEXT:  INX H 			    ; increment HL to point to next address
	   DCR C 				; one operation over, decrement counter
	   JNZ LOOP 			; if counter not zero, go for another operation
	   MVI A,FF 			; if (B) not found in the array, place FFH in accumulator
	   STA 204DH 			; store contents of accumulator in 204DH
	   HLT 					; stop