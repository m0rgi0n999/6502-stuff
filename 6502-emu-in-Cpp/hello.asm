processor 6502
  org $8000     ; start program at $8000
START:
  LDX #$00      ; Load 0 into the X register
  TXS           ; Transfer X to the stack pointer
  BRK           ; Break
