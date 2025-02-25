; 1. Label edge cases
LABEL_TOO_LONGGGGGGGGGGGGGGGGGGGGGGGGGGG: mov r1, r2  
INVALID_LABEL#: mov r2, r3  
1INVALID_LABEL: add @r3, @r4  ; Label starts with a number
LABEL-WITH-HYPHEN: sub @r4, @r5  ; Illegal character in label
LABEL$WITH$DOLLAR: not @r5       ; Illegal character in label
