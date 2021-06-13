	   LXI H,21FF
	   MOV B,M 				; store value of N in register B to use as counter
	   LXI H,2100			; set up HL to start checking the numbers from 2501H
	   LXI D,0000			; clear DE to store the sum

LOOP:  MOV A,M 				; copy contents of HL pair into accumulator
	   ANI 81 				; logical AND 10000001 and contents of accumulator
	   CPI 81				; compare the result with 81H
	   JNZ NEXT				; if not equal, either MSB or LSB or both equal to 0, skip to next iteration
	   MOV A,D 				; transfer the sum in accumulator
	   MOV D,M 				; copy the byte to register D
	   ADD D 				; add (D) to accumulator
	   MOV D,A 				; transfer sum to D
	   JNC NEXT 			; check if carry bit generated
	   INR E 				; if carry flag is set, increment E

NEXT:  INX H 				; increment HL to point to next address
	   DCR B 				; one operation complete, decrement counter
	   JNZ LOOP 			; if counter is not zero, go for next check
	   XCHG 				; transfer the sum to HL pair
	   SHLD 2500H 			; store the sum in 2500H and 2501H
	   HLT 					; stop