struct regs sysregs;
struct mmap sysmem;

void writemem(
    uint16_t address,
    uint8_t  value)
{
  uint16_t offset = 0;

  if (address <= ADDR_ROM0_END)
    {
      offset = 0;
    }
  else if (address <= ADDR_ROM1N_END)
    {
      offset = ADDR_ROM1N_START;
    }
  else if (address <= ADDR_VRAM_END)
    {
      offset = ADDR_VRAM_END;
    }
}
