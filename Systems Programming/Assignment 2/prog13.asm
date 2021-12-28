new_line macro
	mov ah,02h
	mov dl,0dh
	int 21h
	mov dl,0ah
	int 21h
endm

;macro to print space
space macro
	mov ah,02h
	mov dl,' '
	int 21h
endm

;macro to print a message
printm macro mess
	lea dx,mess
	mov ah,09h
	int 21h
endm

;macro to exit
exitp macro
	mov ah,4ch
	int 21h
endm


.model small
.stack 100h
.data
	oupmsg1 db "System time (hh:mm:ss) -> $"
	oupmsg2 db "System date (dd/mm/yy) -> $"
.code      
	disp proc       ; Beginning of disp procedure
		aam           ; ASCII adjust after multiplication [ax register]
		mov bx, ax    ; loading adjusted value to bx
		add bx, 3030h ; Add 3030 to properly print the data
		mov dl, bh    ; To print first digit of data
		mov ah, 02h
		int 21h
		mov dl, bl    ; To print second digit of data
		mov ah, 02h
		int 21h
		ret           
	disp endp
	main proc
		mov ax,@data
		mov ds,ax
		printm oupmsg1
        mov ah, 2ch     ; To get system time [HH in ch, MM in cl, SS in dh]
        int 21h         
        mov al, ch      ; hour in ch
        call disp       
        mov dl, ':'     ; copy : to dl to print
        mov ah, 02h     
        int 21h          
        mov al, cl      ; minutes in cl
        call disp       
        mov dl, ':'     ; To print : as above
        mov ah, 02h     
        int 21h         
        mov al, dh      ; seconds in dh as SS
        call disp       
        new_line
		printm oupmsg2
        mov ah, 2Ah     ; To get system date [DD in dl , MM in dh, YYYY in cx]
        int 21h         
        mov al, dl      ; day in dl
        call disp       
        mov dl, '/'     ; To print /
        mov ah, 02h
        int 21h
        mov al, dh      ; month in dh
        call disp       
        mov dl, '/'     ; To print /
        mov ah, 02h
        int 21h
        add cx, 0F830h  ; Add 0F830 to adjust hexadecimal effects on year
        mov ax, cx      ; year in ax 
        call disp       
        exitp     
	main endp
end main           