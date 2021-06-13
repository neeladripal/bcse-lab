START:	   LXI H,2050H 			; set up HL to point to the address of first number
	   MVI D,00 				; clear register D to set up a flag
	   LDA 204FH 				; store value of N in accumulator
	   MOV C,A 					; copy N in register C to use as counter
	   DCR C 					; N - 1 opeartions needed, so decrement counter

CHECK:	   MOV A,M 				; place the byte specified by content of HL in accumulator
	   INX H 					; increment HL to point to next byte
	   CMP M 					; compare contents of accumulator and byte specified by HL
	   JNC NXTBYT 				; if (A) > second byte, do not exchange values
	   MOV B,M 					; get second byte for exchange
	   MOV M,A 					; store first byte in second location
	   DCX H 					; point to first location
	   MOV M,B 					; store second byte in first location
	   INX H 					; get ready for next comparison
	   MVI D,01H 				; load 1 in D as reminder for exchange

NXTBYT:	   DCR C 				; one comparison complete for the current iteration of array traversal, decrement counter
	   JNZ CHECK 				; if comparison counter not 0, go for next comparison
	   MOV A,D 					; copy reminder flag in accumulator
	   RAR						; check if reminder is set
	   JC START					; go for another traversal through the array until all swaps are done
	   HLT 						; stop