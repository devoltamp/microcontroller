; subtract the r1 from r0 & put it inside r7
org 0000h

; moving data
mov r0, #50h
mov r1, #20h

mov a, r0
clr c
subb a, r1
mov r7, a
; sjmp $
end