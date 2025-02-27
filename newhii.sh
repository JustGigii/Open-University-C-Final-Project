; file ps.as
.entry list 
.extern w
main: add r3, list
loop: prn #48
lea w, r6
inc r6
mov r3, k
sub r1 ,r4
bne &end
dec w
.entry main 
jmp &loop
add l3,l3
end: stop
str: .string "a"
list: .data 6, -9
.data -100
k: .data 31
.extern l3


