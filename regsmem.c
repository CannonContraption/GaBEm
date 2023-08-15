#include "regsmem.h"

struct regs sysregs;
struct mmap sysmem;

void write_himem(
    uint16_t address,
    uint8_t  value)
{
  uint16_t local_address = address;
  if (address <= ADDR_ECHO_RAM_END)
    {
      address -= 0x2000;
      write_mem(
          address,
          value);
    }
  else if (address <= ADDR_OAM_END)
    {
      local_address -= ADDR_OAM_START;
      sysmem.oam [local_address] = value;
    }
  else if (address <= ADDR_UNUSABLE_END)
    {
      // implement Nintendo's DMG corruption bug!
    }
  else if (address <= ADDR_IOREGS_END)
    {
      local_address -= ADDR_IOREGS_START;
      sysmem.ioregs [local_address] = value;
    }
  else if (address <= ADDR_HRAM_END)
    {
      local_address -= ADDR_HRAM_START;
      sysmem.hram [local_address] = value;
    }
  else
    {
      sysmem.interrupt_enable = value;
    }
}

void write_mem(
    uint16_t address,
    uint8_t  value)
{
  if (address >= ADDR_ECHO_RAM_START)
    {
      write_himem(
          address,
          value);
      return;
    }

  ((uint8_t *) &sysmem) [address] = value;
}


uint8_t read_himem(
    uint16_t address)
{
  uint16_t local_address = address;
  if (address <= ADDR_ECHO_RAM_END)
    {
      local_address -= 0x2000;
      return read_mem(
          local_address);
    }
  if (address <= ADDR_OAM_END)
    {
      local_address -= ADDR_OAM_START;
      return sysmem.oam [local_address];
    }
  if (address <= ADDR_UNUSABLE_END)
    {
      return 0;
    }
  if (address <= ADDR_IOREGS_END)
    {
      local_address -= ADDR_IOREGS_START;
      return sysmem.ioregs [local_address];
    }
  else if (address <= ADDR_HRAM_END)
    {
      local_address -= ADDR_HRAM_START;
      return sysmem.hram [local_address];
    }
  else
    {
      return sysmem.interrupt_enable;
    }
}

uint8_t read_mem(
    uint16_t address)
{
  if (address >= ADDR_ECHO_RAM_START)
    {
      return read_himem(
          address);
    }

  return ((uint8_t *) &sysmem) [address];
}
