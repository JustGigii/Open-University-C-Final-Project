TTT
JKJ
mov #4,r3
mcro TTT
sub r1,#2
clr r1
mcroend
mcro JKJ
stop
mcroend
mcro YOU
bne &next
mcroend
next: stop
prn #4
