	   		LXI H,2050H 		; set up HL to point to first number in array
	   		LDA 204FH 			; store value of N in 204FH
	   		MOV C,A 			; place N in register C to use as counter
	   		MOV B,M 			; copy the first number in register B
	   		INX H  				; increment H to point to the address of second number
	   		DCR C 				; one operation complete, decrement counter

NXTBYTE:	MOV A,M 			; place number pointed to by HL pair in accumulator
	   		CMP B 				; compare contents of register B and accumulator
	   		JC NEXT				; check if carry flag is 0
	   		MOV B,A 			; if carry flag is 1, contents of register B is greater, copy 							; contents of B into accumulator

NEXT:	   	INX H 				; increment HL to point to next address
	   		DCR C 				; one operation complete, decrement counter
	   		JNZ NXTBYTE 		; jump to check the next number
	  	 	MOV A,B 			; copy the maximum number into accumulator
	   		STA 2070H 			; store the contents of accumulator in 2070H
	   		HLT					; stop