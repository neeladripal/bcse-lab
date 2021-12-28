	   LDA 2000H
	   MOV B,A 				; store lower byte of 1st number in register B
	   LDA 2002H			; store lower byte of 2nd number in accumulator
	   ADD B 				; add the two lower bytes
	   STA 2200H 			; store the result in 2200H
	   MVI A,00H 			; store 00H in accumulator
	   ADC A 				; add carry bit into accumalator
	   MOV C,A 				; store the carry from lower byte addition in register C
	   LDA 2001H
	   MOV B,A 				; store higher byte of 1st number in register B
	   LDA 2003H 			; store higher byte of 2nd number in accumulator
	   ADD B 				; add the two higher bytes
	   MOV D,A 				; move the result in register D
	   MVI A,00H			; store 00H in accumulator
	   ADC A 				; add carry bit into accumalator
	   MOV B,A 				; store the carry from higher byte addition in register B
	   MOV A,D				; store the higher bit sum in accumulator
	   ADD C 				; add the carry from lower byte addition
	   STA 2201H 			; store the sum in 2201H
	   ADC B 				; add the carry bit from higher bit addition to this sum along with carry
	   STA 2202H 			; store the final carry value in 2202H
	   HLT 					; stop