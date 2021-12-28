       LDA 2200H
	   MOV B,A 				; place value of N in register B to use as counter
	   LXI H,2500H			; set up HL to point to first byte
	   MVI A,00				; clear accumulator to store sum
	   MVI C,00   			; clear register C to store carry

LOOP:  ADC M 				; add the content of addess specified by HL pair to accumulator
	   INX H 				; increment HL to point to the address of next number
	   JNC NEXT 			; if carry not generated, skip to next iteration
	   INR C 				; increment the carry

NEXT:  DCR B 				; one operation complete, decrement counter
	   JNZ LOOP 			; continue with the next iteration
	   STA 2300H			; store lower byte of the sum
	   MOV A,C 				; transfer carry to accumulator
	   STA 2301H 			; store higher byte of the sum
	   HLT 					; stop