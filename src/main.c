#define CTRL_PORT1  *((unsigned char*)0x4016)

// Button Bitmasks
#define BUTTON_A      0x80
#define BUTTON_B      0x40
#define BUTTON_SELECT 0x20
#define BUTTON_START  0x10
#define BUTTON_UP     0x08
#define BUTTON_DOWN   0x04
#define BUTTON_LEFT   0x02
#define BUTTON_RIGHT  0x01

unsigned char read_controller() {
    unsigned char state = 0;
    int i;
    // Latch the controller state
    CTRL_PORT1 = 1;
    CTRL_PORT1 = 0;
    // Read 8 buttons
    for (i = 0; i < 8; ++i) {
        state <<= 1;
        state |= (CTRL_PORT1 & 1);
    }
    return state;
}

void main (void) {
    unsigned char buttons;
    
    // ... (Keep your existing PPU/Palette initialization code here) ...

    while (1) {
        wait_vblank();
        OAM_DMA = 0x02; 

        buttons = read_controller();

        // Manual Control!
        if (buttons & BUTTON_RIGHT) player_x++;
        if (buttons & BUTTON_LEFT)  player_x--;
        if (buttons & BUTTON_UP)    player_y--;
        if (buttons & BUTTON_DOWN)  player_y++;

        // Update Sprite 0 position in RAM ($0200)
        *((unsigned char*)0x0200) = player_y;
        *((unsigned char*)0x0203) = player_x;

        // Reset Scroll
        PPU_ADDR = 0x00; PPU_ADDR = 0x00;
        PPU_SCROLL = 0x00; PPU_SCROLL = 0x00;
    }
}
