	    LHLD 2050H 				; store contents of 2050H in L and 2051H in H
	    XCHG 					; place A in E and B in D
	    CALL MLTPLY				; multiply A and B
	    SHLD 2052H				; store the product in 2052H and 2053H
	    HLT						; stop

MLTPLY:	MOV A,D 				; copy B in accumulator
	    MVI D,00H 				; clear D to use in DAD instruction
	    LXI H,0000 				; clear HL
	    MVI B,08H 				; set up B to count eight rotations

NXTBIT:	RAR					    ; check if multiplier bit is 1
	    JNC NOADD 				; if not, skip adding multiplicand
	    DAD D 					; if multiplier is 1, add multiplicand to HL and place the partial result in HL

NOADD:	XCHG					; place multiplicand in HL
	    DAD H 					; and shift left
	    XCHG 					; retrive shifted multiplicand in DL
	    DCR B 					; one operation complete, decrement counter
	    JNZ NXTBIT 				; go back to check next multiplier bit
	    RET 					; stop