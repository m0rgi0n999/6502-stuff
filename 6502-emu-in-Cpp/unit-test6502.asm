; example.asm
.org $8000
LDX #$00         ; Load X register with 0
TXS              ; Transfer X to Stack Pointer
INX              ; Increment X register
JMP $8000        ; Jump to the start
