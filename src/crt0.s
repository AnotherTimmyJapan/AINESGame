.import _main
.export __STARTUP__ : abs = 1
.import __STACKSIZE__ ; Linker generated

.segment "HEADER"
    .byte $4e, $45, $53, $1a
    .byte $02 ; 32k PRG
    .byte $01 ; 8k CHR
    .byte $00, $00

.segment "STARTUP"
reset:
    sei
    cld
    ldx #$ff
    txs
    jmp _main

.segment "VECTORS"
    .word 0 ; NMI
    .word reset
    .word 0 ; IRQ

.segment "CHARS"
    .res 8192, $AA ; Fill with a pattern so we can see if it's working
