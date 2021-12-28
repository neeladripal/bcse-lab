	   LDA 2500H			; store the byte in accumulator
	   MVI C,08H  			; store 08H in register C acts to use as counter
	   MVI B,00H			; clear register B to keep count of 1s in the byte

LOOP:  RLC					; rotate the byte right by 1 bit
	   JC SKIP				; if carry is 0, skip to next iteration
	   INR B 				; carry is 1, so increment B

SKIP:  DCR C 				; one bit comparison complete, decrement counter
	   JNZ LOOP 			; if counter is not zero, go for next comparison
	   MOV A,B 				; store count of 1s in accumulator
	   STA 2610H			; store count of 1s in 2610H
	   MVI A,08				; store 08H in accumulator
	   SUB B 				; subtract count of 1s from 08H to get count of 0s
	   STA 2511H 			; store count of 0s in 2511H
	   HLT 					; stop