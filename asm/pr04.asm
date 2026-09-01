org 0000h
mov a, #01h
add a, #50h
mov r0, #01h
; add a, r0
add a, @r0
end