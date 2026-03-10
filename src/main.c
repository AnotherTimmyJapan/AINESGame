// 1. Define NES PPU Registers
#define PPU_CTRL    *((unsigned char*)0x2000)
#define PPU_MASK    *((unsigned char*)0x2001)
#define PPU_STATUS  *((unsigned char*)0x2002)
#define PPU_SCROLL  *((unsigned char*)0x2005)
#define PPU_ADDR    *((unsigned char*)0x2006)
#define PPU_DATA    *((unsigned char*)0x2007)
#define OAM_DMA     *((unsigned char*)0x4014)

// 2. Define Colors
#define COLOR_WHITE 0x30
#define COLOR_BLUE  0x21

// 3. Global Variables
unsigned char player_x = 120;
unsigned char player_y = 120;

// 4. Function to wait for the screen to finish drawing
void wait_vblank() {
    while (!(PPU_STATUS & 0x80));
}

void main (void) {
    // Turn off screen to load data
    PPU_MASK = 0x00; 
    
    // Load Palette
    PPU_ADDR = 0x3F; PPU_ADDR = 0x00;
    PPU_DATA = COLOR_BLUE; // Background
    
    PPU_ADDR = 0x3F; PPU_ADDR = 0x11; 
    PPU_DATA = COLOR_WHITE; // Sprite Color

    // Turn screen on (Enable Sprites + Background)
    PPU_MASK = 0x1E; 

    while (1) {
        wait_vblank();
        
        // Push the sprite data to the PPU
        OAM_DMA = 0x02; 
        
        // Game Logic: Move the player right
        player_x++; 
        
        // Update Sprite 0 X-coordinate in RAM
        *((unsigned char*)0x0203) = player_x;
        // Update Sprite 0 Y-coordinate in RAM
        *((unsigned char*)0x0200) = player_y;

        // Reset Scroll (Important: prevents screen shaking)
        PPU_ADDR = 0x00; PPU_ADDR = 0x00;
        PPU_SCROLL = 0x00; PPU_SCROLL = 0x00;
    }
}
