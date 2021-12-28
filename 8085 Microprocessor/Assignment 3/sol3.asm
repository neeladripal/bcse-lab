         	LXI H,2060H			; set up HL to point to address of N
  		 	MOV C,M 			; transfer value of N in register C
   			MVI A,00 			; clear accumulator to store nth fibonacci number
   			MVI B,01 			; set B = 01H as the 2nd fibonacci number
   			CALL FIBONACCI 		; compute the nth fibonacci number
   			STA 2050H			; store the result in 2050H
   			HLT 				; stop

FIBONACCI:	DCR C 				; decrement value of N by 1
  			RZ 					; return if N is 0
   			ADD B 				; add (B) to get the next fibonacci number
   			MOV D,A 			; transfer (A) to register D
   			MOV A,B 			; transfer (B) to accumulator
   			MOV B,D 			; transfer contents of D to B
   			JMP FIBONACCI 		; unconditional jump to the subroutine