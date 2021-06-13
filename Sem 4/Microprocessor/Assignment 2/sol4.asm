	   LDA 204FH 					; store value of N in accumulator
	   MOV C,A 						; copy N in register C to use as counter
	   LXI H,2050H 					; set up HL to point to address of first byte
	   LXI D,2100H 					; set up DL to point to address 2100H to store the even numbers
	   MVI B,00H 					; clear register B to count no of even values

STARTEVEN:	   MOV A,M 				; place contents of HL in accumulator
			   ANI 01H				; check if the last bit is 1
			   JNZ NTEVEN 			; if last bit is 1, number is odd, jump to next iteration
			   MOV A,M 				; place the number in accumulator again
			   STAX D 				; store the content of accumulator to address pointed by DL
			   INX D 				; increment DL to point to next address
			   INR B 				; increment B because (A) is even

NTEVEN:	   	   INX H 				; increment HL to point to next address
			   DCR C 				; one operation over, decrement counter
			   JNZ STARTEVEN 		; if counter not zero, go for another operation
			   MOV A,B 				; copy the count of even values in accumulator
			   STA 2300H 			; store the count value in 2300H

			   LDA 204FH 			; store value of N in accumulator
			   MOV C,A 				; copy N in register C to use as counter
			   LXI H,2050H 			; set up HL to point to address of first byte
			   LXI D,2200H 			; set up DL to point to address 2200H to store the odd numbers
			   MVI B,00H 			; clear register B to count no of odd values

STARTODD:	   MOV A,M 				; place contents of HL in accumulator
			   ANI 01H				; check if the last bit is 1
			   JZ NTODD 			; if last bit is 0, number is even, jump to next iteration
			   MOV A,M 				; place the number in accumulator again
			   STAX D 				; store the content of accumulator to address pointed by DL
			   INX D 				; increment DL to point to next address
			   INR B 				; increment B because (A) is odd

NTODD:	   	   INX H 				; increment HL to point to next address
			   DCR C 				; one operation over, decrement counter
			   JNZ STARTODD 		; if counter not zero, go for another operation
			   MOV A,B 				; copy the count of odd values in accumulator
			   STA 2301H 			; store the count value in 2301H
			   HLT 					; stop