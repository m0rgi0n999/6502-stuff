;       BUBBLE SORT PROGRAM
;
        # = $0
;
TAB     .WORD $600
;
        # = $200
;
SORT    LDX #0          ;SET 'EXCHANGED' TO 0
        LDA (TAB,X)
        TAY             ;NUMBER OF ELEMENTS IS IN Y
LOOP    LDA (TAB),Y     ;READ ELEMENT E(I)
        DEY             ;DECREMENT NUMBER OF ELEMENTS TO READ
        BEQ FINISH      ;END IF NO MORE ELEMENTS
        CMP (TAB),Y     ;COMPARE TO E'(I)
        BCS LOOP        ;GET NEXT ELEMENT IF E(I)>E'(I)
EXCH    TAX             ;EXCHANGE ELEMENTS
        LDA (TAB),Y
        INY
        STA (TAB),Y
        TXA
        DEY
        STA (TAB),Y
        LDX #1          ;SET 'EXCHANGED' TO 1
        BNE LOOP        ;GET NEXT ELEMENT
FINISH  TXA             ;SHIFT 'EXCHANGED' TO A REG. FOR COMPARE...
        BNE SORT        ;IF SOME EXCHANGES MADE, DO ANOTHER PASS.
        RTS
        .END