	   LXI H,2200H			; store 2200H into HL pair
	   MOV A,M    			; copy first number to register B
	   INX H                ; increment HL to point to 2201H
	   MOV B,M    			; copy second number to register B
	   MVI C,00H 			; clear register C to store carry
	   ADD B   				; add contents of B to accumulator
	   JNC STORE 			; if carry not generated, jump to store the sum
	   INR C 				; increment the carry

STORE: INX H 			  	; increment HL to point to 2202H
	   MOV M,A 				; store the sum in address specified by HL
	   INX H 				; increment HL to point to 2203H
	   MOV M,C 				; store the carry in address specified by HL
	   HLT 					; stop