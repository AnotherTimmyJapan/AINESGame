.export _main
.export __STARTUP__ : abs = 1

.segment "HEADER"
    .byte $4e, $45, $53, $1a ; "NES" + EOF
    .byte $02                ; 2x 16KB PRG
    .byte $01                ; 1x 8KB CHR
    .byte $00, $00           ; Mapper 0, NROM
    .res 8, $00              ; Padding

.segment "CHARS"
    ; A simple 8x8 square tile
    .byte %00111100
    .byte %01111110
    .byte %11111111
    .byte %11111111
    .byte %11111111
    .byte %11111111
    .byte %01111110
    .byte %00111100
    .res 8184, $00 ; Fill the rest of the 8KB with zeros

