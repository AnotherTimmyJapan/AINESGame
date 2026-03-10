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

