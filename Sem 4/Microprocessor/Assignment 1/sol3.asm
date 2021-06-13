LDA 2500H		; store the number in accumulator
ANI 0FH 		; logical AND (00001111) to get least significant 4 bits
MOV B,A 		; transfer contents of accumulator to register B
LDA 2500H 		; store the number in accumulator
RRC
RRC
RRC
RRC 			; right rotate 4 times
ANI 0F 			; logical AND (00001111) to get most significant 4 bits
ADD B 			; add the least significant 4 bits and most significant 4 bits
STA 2550H 		; store the result in 2550H
HLT 			; stop