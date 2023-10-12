#include <stdio.h>
#include <stdint.h>

#include "regsmem.c"
#include "cpu.c"

#define TESTASSERT(testname, resultp) \
    if (resultp) \
      { \
        printf("\033[32m%16s\033[m pass!\n", testname); \
      } \
    else \
      { \
        testresult ++; \
        printf("\033[1;31m%16s\033[m fail\n", testname); \
      }

/*
  test_inc

  Test incurement instructions, one by one. Uses micro test programs
 */
#define TEST_REG_INC(REG, BITS, NAME, OPC) {     \
    BITS = sysregs.REG;                         \
    write_mem(GB_START_ADDR, OPC);               \
    exec(GB_START_ADDR);                        \
    TESTASSERT(NAME, (sysregs.REG == BITS + 1));        \
  }
uint8_t test_inc()
{
  uint8_t testresult = 0;

  uint16_t initial16;
  uint8_t  initial8;

  write_mem(
      GB_START_ADDR + 1,
      0x76);

  TEST_REG_INC (REGBC, initial16, "INC BC", 0x03);
  TEST_REG_INC (REGB,  initial8,  "INC B",  0x04);
  TEST_REG_INC (REGC,  initial8,  "INC C",  0x0C);
  TEST_REG_INC (REGDE, initial16, "INC DE", 0x13);
  TEST_REG_INC (REGD,  initial8,  "INC D",  0x14);
  TEST_REG_INC (REGE,  initial8,  "INC E",  0x1C);
  TEST_REG_INC (REGHL, initial16, "INC HL", 0x23);
  TEST_REG_INC (REGH,  initial8,  "INC H",  0x24);
  TEST_REG_INC (REGL,  initial8,  "INC L",  0x2C);
  TEST_REG_INC (REGSP, initial16, "INC SP", 0x33);
  TEST_REG_INC (REGA,  initial8,  "INC A",  0x3C);

  return testresult;
}

#define TEST_REG_DEC(REG, BITS, NAME, OPC) {     \
    BITS = sysregs.REG;                         \
    write_mem(GB_START_ADDR, OPC);               \
    exec(GB_START_ADDR);                        \
    TESTASSERT(NAME, (sysregs.REG == BITS - 1));        \
  }
uint8_t test_dec()
{
  uint8_t testresult = 0;

  uint16_t initial16;
  uint8_t  initial8;

  write_mem(
      GB_START_ADDR + 1,
      0x76);

  TEST_REG_DEC (REGBC, initial16, "DEC BC", 0x05);
  TEST_REG_DEC (REGB,  initial8,  "DEC B",  0x0B);
  TEST_REG_DEC (REGC,  initial8,  "DEC C",  0x0D);
  TEST_REG_DEC (REGDE, initial16, "DEC DE", 0x15);
  TEST_REG_DEC (REGD,  initial8,  "DEC D",  0x1B);
  TEST_REG_DEC (REGE,  initial8,  "DEC E",  0x1D);
  TEST_REG_DEC (REGHL, initial16, "DEC HL", 0x25);
  TEST_REG_DEC (REGH,  initial8,  "DEC H",  0x2B);
  TEST_REG_DEC (REGL,  initial8,  "DEC L",  0x2D);
  TEST_REG_DEC (REGSP, initial16, "DEC SP", 0x3B);
  TEST_REG_DEC (REGA,  initial8,  "DEC A",  0x3D);

  return testresult;
}

uint8_t test_mem()
{
  // Test some basic addressing by writing to video memory
  write_mem(
      ADDR_VRAM_START + 20,
      0xEE);

  uint8_t testresult = 0;
  uint8_t read_value = read_mem(
      ADDR_VRAM_START + 20);

  if (read_value != sysmem.vram[20])
    {
      printf(
          "\033[1;31mWrite/read 0xEE Fail!\033[m\n");
      testresult ++;
    }

  testresult += test_inc();
  testresult += test_dec();

  if (testresult == 0)
    {
      printf(
          "\033[1;32mAll tests pass!\033[m\n");
    }
  else
    {
      printf(
          "\033[1;31m%d\033[m tests fail.\n",
          testresult);
    }
  return 0;
}

int main(
    int    argc,
    char * argv[])
{
  uint8_t testsum = 0;

  testsum += test_mem();
}

