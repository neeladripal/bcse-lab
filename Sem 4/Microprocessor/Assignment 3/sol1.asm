	   LDA 2500H 			; store value of N in accumulator
	   MOV C,A 				; copy N in register C to use as counter
	   LXI D,2600H			; set up DE to start storing from 2600H
	   LXI H,2501H			; set up HL to start checking the numbers from 2501H

START: MOV A,M 				; copy contents of HL pair into accumulator
	   RLC 					; left rotate accumulator bits by 1 place
	   JC STORE 			; if MSB is 1, carry flag is updated to 1, store the value
	   RRC 					; right rotate to restore to original byte
	   RRC 					; right rotate accumulator bits by 1 place
	   JNC NEXT				; if LSB is 0, carry flag is updated to 0, do not store the value
	   RLC
	   RLC					; left rotate by 2 places

STORE: RRC 					; finally right rotate to get the original byte
	   STAX D 				; store the byte in address specified by DL
	   INX D 				; increment DE to point to the next address

NEXT:  INX H 				; increment HL to point to the next address
	   DCR C 				; one operation complete, decrement counter
	   JNZ START 			; if counter is not zero, go for next check
	   HLT 					; stop