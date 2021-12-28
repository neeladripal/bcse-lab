	   LDA 2050H 				; store MN in accumulator
	   MOV B,A 					; copy MN into register B
	   LDA 2051H 				; store KL in accumulator
	   MOV C,A 					; copy KL into register C
	   ANI F0H 					; convert KL to K0
	   MOV D,A 					; copy K0 into register D
	   MOV A,B 					; copy MN into accumulator
	   ANI 0FH 					; convert MN to 0N
	   ORA D 					; logical OR contents of D and accumulator to get KN
	   RRC 						
	   RRC
	   RRC
	   RRC						; rotate right 4 times to get NK
	   STA 2052H 				; store NK in 2052H
	   MOV A,C 					; copy KL into accumulator
	   ANI 0FH 					; convert KL to 0L
	   MOV D,A 					; copy 0L into register D
	   MOV A,B					; copy MN into accumulator
	   ANI F0H 					; convert MN to M0
	   ORA D 					; logical OR contents of D and accumulator to get ML
	   RRC
	   RRC
	   RRC
	   RRC 						; rotate right 4 times to get LM
	   STA 2053H 				; store LM in 2053H
	   HLT 						; stop