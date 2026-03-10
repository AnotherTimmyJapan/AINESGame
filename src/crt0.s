.import _main
.export __STARTUP__ : abs = 1
.export _wait_vblank

.segment "HEADER"
    .byte $4e, $45, $53, $1a
    .byte $02 ; 32k PRG
    .byte $01 ; 8k CHR
    .byte $00, $00

.segment "CODE"
_wait_vblank:
    bit $2002
:   bit $2002
    bpl :-
    rts

reset:
    sei
    cld
    ldx #$00
    stx $2000
    stx $2001
    
    ; Wait for PPU to stabilize
    jsr _wait_vblank
    jsr _wait_vblank

    ldx #$ff
    txs
    jmp _main

nmi:
    rti ; Return from interrupt (does nothing for now)

irq:
    rti

.segment "VECTORS"
    .word nmi    ; $FFFA (NMI)
    .word reset  ; $FFFC (Reset)
    .word irq    ; $FFFE (IRQ)

.segment "CHARS"
    ; Tile 0: A solid 8x8 square (The "Player")
    .byte %11111111
    .byte %11111111
    .byte %11111111
    .byte %11111111
    .byte %11111111
    .byte %11111111
    .byte %11111111
    .byte %11111111
    ; The NES uses 2 bytes per row for color depth, 
    ; so we need another 8 bytes for the second plane.
    .byte %00000000
    .byte %00000000
    .byte %00000000
    .byte %00000000
    .byte %00000000
    .byte %00000000
    .byte %00000000
    .byte %00000000
    
    .res 8176, $00 ; Fill the rest of the 8KB with empty space (black)
