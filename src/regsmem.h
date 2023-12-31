#ifndef REGSMEM_H
#define REGSMEM_H

typedef union
{
  uint16_t u16;
  uint8_t  u8[2];
} uint;

/*
   ___  ______________________________  ____
  / _ \/ __/ ___/  _/ __/_  __/ __/ _ \/ __/
 / , _/ _// (_ // /_\ \  / / / _// , _/\ \  
/_/|_/___/\___/___/___/ /_/ /___/_/|_/___/ 
 */

typedef struct
{
  uint     af;
  uint     bc;
  uint     de;
  uint     hl;
  uint16_t sp;
  uint16_t pc;
} regs;

/* Allow access as regs.REGAF (for example) */
#define REGAF af.u16
#define REGBC bc.u16
#define REGDE de.u16
#define REGHL hl.u16
#define REGSP sp
#define REGPC pc

#define REGA  af.u8[0]
#define REGB  bc.u8[0]
#define REGC  bc.u8[1]
#define REGD  de.u8[0]
#define REGE  de.u8[1]
#define REGH  hl.u8[0]
#define REGL  hl.u8[1]

#define FLAGSREG af.u8[1]

/*
   __  _________  _______  _____  __
  /  |/  / __/  |/  / __ \/ _ \ \/ /
 / /|_/ / _// /|_/ / /_/ / , _/\  / 
/_/  /_/___/_/  /_/\____/_/|_| /_/ 
   ___   ___  ___  ___  _________________  _______
  / _ | / _ \/ _ \/ _ \/ __/ __/ __/  _/ |/ / ___/
 / __ |/ // / // / , _/ _/_\ \_\ \_/ //    / (_ / 
/_/ |_/____/____/_/|_/___/___/___/___/_/|_/\___/ 
 */

typedef struct
{
  uint8_t rombank0  [0x4000];
  uint8_t rombank1n [0x4000];
  uint8_t vram      [0x2000];
  uint8_t extended  [0x2000];
  uint8_t l_wram    [0x1000];
  uint8_t h_wram    [0x1000];
  uint8_t oam         [0xa0];
  uint8_t ioregs      [0x7F];
  uint8_t hram        [0x7e];
  uint8_t interrupt_enable;
} mmap;

#define ADDR_ROM0_START         0x0
#define ADDR_ROM0_END        0x3FFF
#define ADDR_ROM1N_START     0x4000
#define ADDR_ROM1N_END       0x7FFF
#define ADDR_VRAM_START      0x8000
#define ADDR_VRAM_END        0x9FFF
#define ADDR_EXTEND_START    0xA000
#define ADDR_EXTEND_END      0xBFFF
#define ADDR_L_WRAM_START    0xC000
#define ADDR_L_WRAM_END      0xCFFF
#define ADDR_H_WRAM_START    0xD000
#define ADDR_H_WRAM_END      0xDFFF
#define ADDR_ECHO_RAM_START  0xE000
#define ADDR_ECHO_RAM_END    0xFDFF
#define ADDR_OAM_START       0xFE00
#define ADDR_OAM_END         0xFE9F
#define ADDR_UNUSABLE_START  0xFEA0
#define ADDR_UNUSABLE_END    0xFEFF
#define ADDR_IOREGS_START    0xFF00
#define ADDR_IOREGS_END      0xFF7F
#define ADDR_HRAM_START      0xFF80
#define ADDR_HRAM_END        0xFFFE
#define ADDR_INTERRUPT       0xFFFF


/*
   ____              __  _         
  / __/_ _____  ____/ /_(_)__  ___ 
 / _// // / _ \/ __/ __/ / _ \/ _ \
/_/  \_,_/_//_/\__/\__/_/\___/_//_/
                                   
   ___           __       __                  
  / _ \_______  / /____  / /___ _____  ___ ___
 / ___/ __/ _ \/ __/ _ \/ __/ // / _ \/ -_|_-<
/_/  /_/  \___/\__/\___/\__/\_, / .__/\__/___/
                           /___/_/
 */

void     write_himem         (uint16_t address, uint8_t value);
void     write_mem           (uint16_t address, uint8_t value);
int8_t write_mem_chunk       (uint16_t address, uint8_t * buf, uint16_t count);
uint8_t  read_himem          (uint16_t address);
uint8_t  read_mem            (uint16_t address);

/*
    ______        __  _             _____                       __  _             
   /_  __/__ ___ / /_(_)__  ___ _  / ___/__  ___ _  _____ ___  / /_(_)__  ___  ___
    / / / -_|_-</ __/ / _ \/ _ `/ / /__/ _ \/ _ \ |/ / -_) _ \/ __/ / _ \/ _ \(_-<
   /_/  \__/___/\__/_/_//_/\_, /  \___/\___/_//_/___/\__/_//_/\__/_/\___/_//_/___/
                          /___/  
*/

/* Usual address to start a program, for test function */
#define GB_START_ADDR 0x100

#endif /* #ifndef REGSMEM_H */
