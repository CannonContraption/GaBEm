#include <stdio.h>
#include <stdint.h>

#include "regsmem.c"
#include "cpu.h"

int main(
    int    argc,
    char * argv[])
{
  // Test some basic addressing by writing to video memory
  write_mem(
      ADDR_VRAM_START + 20,
      0xEE);

  uint8_t read_value = read_mem(
      ADDR_VRAM_START + 20);

  if (read_value == sysmem.vram[20])
    {
      printf(
          "\033[1;32mWrite/read 0xEE OK!\033[m\n");
    }
  else
    {
      printf(
          "\033[1;31mWrite/read 0xEE Fail!\033[m\n");
    }
  return 0;
}

