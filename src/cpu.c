#include "cpu.h"

static uint8_t bytes_read;
static uint8_t bytes_total;
static uint8_t c_inst; /* Current instruction */

static void inc_flags(
    uint8_t value)
{
  sysregs.FLAGSREG &= ~(FLAG_N);
  if (!value)
    sysregs.FLAGSREG |= FLAG_Z;
  if (value & 0x7 == 0)
    sysregs.FLAGSREG |= FLAG_H;
}
/*
  inc()

  Increment instruction. Takes some register based on the instruction and
  increments whatever is there.
 */
#define _INC_REG(register) { sysregs.register ++; inc_flags(sysregs.register); }
static void inc ()
{
  switch(c_inst)
    {
    case 0x03:
      _INC_REG (REGBC);
      break;
    case 0x04:
      _INC_REG (REGB);
      break;
    case 0x0C:
      _INC_REG (REGC);
      break;
    case 0x13:
      _INC_REG (REGDE);
      break;
    case 0x14:
      _INC_REG (REGD);
      break;
    case 0x1C:
      _INC_REG (REGE);
      break;
    case 0x23:
      _INC_REG (REGHL);
      break;
    case 0x24:
      _INC_REG (REGH);
      break;
    case 0x2C:
      _INC_REG (REGL);
      break;
    case 0x33:
      _INC_REG (REGSP);
      break;
    case 0x34:
      write_mem(
          sysregs.REGHL,
          read_mem (sysregs.REGHL) + 1);
      sysregs.REGHL ++;
      break;
    case 0x3C:
      _INC_REG (REGA);
      break;
    }
}

static void dec_flags(
    uint8_t value)
{
  sysregs.FLAGSREG |= FLAG_N;
  if (!value)
    sysregs.FLAGSREG |= FLAG_Z;
  if (value & 0x7 == 0x7)
    sysregs.FLAGSREG |= FLAG_H;
}
/*
  dec()

  Decrement instruction. Takes some register based on the instruction and
  decrements whatever is there.
 */
#define _DEC_REG(register) { sysregs.register --; dec_flags(sysregs.register); }
static void dec ()
{
  switch (c_inst)
    {
    case 0x05:
      _DEC_REG (REGB);
      break;
    case 0x0B:
      _DEC_REG (REGBC);
      break;
    case 0x0D:
      _DEC_REG (REGC);
      break;
    case 0x15:
      _DEC_REG (REGD);
      break;
    case 0x1B:
      _DEC_REG (REGDE);
      break;
    case 0x1D:
      _DEC_REG (REGE);
      break;
    case 0x25:
      _DEC_REG (REGH);
      break;
    case 0x2B:
      _DEC_REG (REGHL);
      break;
    case 0x2D:
      _DEC_REG (REGL);
      break;
    case 0x35:
      write_mem(
          sysregs.REGHL,
          read_mem (sysregs.REGHL) - 1);
      break;
    case 0x3B:
      _DEC_REG (REGSP);
      break;
    case 0x3D:
      _DEC_REG (REGA);
      break;
    }
}

static void add (
    uint8_t * inst)
{
  uint augend;
  uint addend;
}

int exec(
    uint16_t address)
{
  uint8_t cycles = 0;

  for (;;)
    {
      c_inst = read_mem(
          address);

      switch (c_inst)
        {
        case 0x76: /* Halt */
          return 0x76;
        case 0x00: /* NOP */
          break;
        case 0x03: /* INC */
        case 0x04:
        case 0x0C:
        case 0x13:
        case 0x14:
        case 0x1C:
        case 0x23:
        case 0x24:
        case 0x2C:
        case 0x33:
        case 0x34:
        case 0x3C:
          inc();
          break;
        case 0x05: /* DEC */
        case 0x0B:
        case 0x0D:
        case 0x15:
        case 0x1B:
        case 0x1D:
        case 0x25:
        case 0x2B:
        case 0x2D:
        case 0x35:
        case 0x3B:
        case 0x3D:
          dec();
          break;
        default:
          fprintf(
              stderr,
              "EMULATOR INTERNAL ERROR: Invalid opcode 0x%x !?\n",
              c_inst);
          return -1;
        }

      cycles  += is[c_inst].duration_tstates * 4;
      address += is[c_inst].bytes;
      
    }
}
