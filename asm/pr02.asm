org 0000h
; address EQU 30H
mov a,#73h
mov r0,a
inc r0
inc @r0
; literal copy
; MOV R5, #42
; MOV A, R5
; MOV address, A
; SJMP $
end