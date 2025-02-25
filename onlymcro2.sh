mov #-1,r2
mov IX,r3
mov r2,r4
cmp #0,r2
cmp IX,r7
cmp r2,r3
add #1,r4
add IX,r5
add r1,r5
sub #200,r4
sub IX,r1
sub r1,r7
lea IX,r6
jmp &next
jmp IX
bne &next
bne IX
jsr &next
jsr IX
clr r2
clr IX
not r3
not IX
inc r4
inc IX
dec r5
dec IX
red r6
red IX
prn r7
prn IX
.extern IX
prn #2000
prn r2
prn IX
rts
stop
.entry next
.data 1,2,3
.string "abc"
next: add r2,r3
prn &next
mac
mcro mac
clr &next
not &next
inc &next
clr r1,r2
clr #333
not #444
red #777
mcroend
not #22
inc #44
dec #55
jmp #66
bne #77
jsr #88
lea #99
jmp r3
bne r4
jsr r5
add r1
sub r2
mov r3 ,#2000