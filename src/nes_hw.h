#ifndef NES_HW_H
#define NES_HW_H

/* PPU Registers */
#define PPU_CTRL    *((volatile unsigned char*)0x2000)
#define PPU_MASK    *((volatile unsigned char*)0x2001)
#define PPU_STATUS  *((volatile unsigned char*)0x2002)
#define PPU_OAMADDR *((volatile unsigned char*)0x2003)
#define PPU_OAMDATA *((volatile unsigned char*)0x2004)
#define PPU_SCROLL  *((volatile unsigned char*)0x2005)
#define PPU_ADDR    *((volatile unsigned char*)0x2006)
#define PPU_DATA    *((volatile unsigned char*)0x2007)

/* APU & I/O Registers */
#define OAM_DMA     *((volatile unsigned char*)0x4014)
#define JOYPAD1     *((volatile unsigned char*)0x4016)
#define JOYPAD2     *((volatile unsigned char*)0x4017)

#endif
