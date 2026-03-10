// Define some basic color constants
#define COLOR_BLACK 0x0F
#define COLOR_WHITE 0x30

void main (void) {
    // 1. Turn off screen
    PPU_MASK = 0x00; 
    
    // 2. Load Palette (Background and Sprite)
    PPU_ADDR = 0x3F; PPU_ADDR = 0x00;
    PPU_DATA = 0x21; // Background (Blue)
    
    PPU_ADDR = 0x3F; PPU_ADDR = 0x11; // Sprite Palette 0, Color 1
    PPU_DATA = COLOR_WHITE;

    // 3. Define Sprite 0 in OAM (Memory $0200)
    *((unsigned char*)0x0200) = 120; // Y-coord
    *((unsigned char*)0x0201) = 0x00; // Tile index (the square we made)
    *((unsigned char*)0x0202) = 0x00; // Attributes (No flip)
    *((unsigned char*)0x0203) = 120; // X-coord

    // 4. Turn screen on (Enable Sprites + Background)
    PPU_MASK = 0x1E; 

    while (1) {
        wait_vblank();
        
        // Push the RAM at $0200 to the PPU OAM
        *((unsigned char*)0x4014) = 0x02; 
        
        // Logic: Move the sprite!
        player_x++; 
        *((unsigned char*)0x0203) = player_x;

        // Reset Scroll
        PPU_ADDR = 0x00; PPU_ADDR = 0x00;
        PPU_SCROLL = 0x00; PPU_SCROLL = 0x00;
    }
}
