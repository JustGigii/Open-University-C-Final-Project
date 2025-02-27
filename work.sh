mcro til
sub r1,r3
mcroend
til
stop
next: clr r1
.data 2000,450
.extern OUT 
bne &next
add OUT,OUT
main: prn #5
.entry main
.string "a"

