#include "cpu.h"

static uint8_t bytes_read;
static uint8_t bytes_total;
static uint8_t instruction;

static void inc_flags(
    uint8_t value)
{
  regs.FLAGSREG &= ~(FLAG_N);
  if (!value)
    regs.FLAGSREG |= FLAG_Z;
  if (value & 0x7 == 0)
    regs.FLAGSREG |= FLAG_H;
}
/*
  inc()

  Increment instruction. Takes some register based on the instruction and
  increments whatever is there.
 */
#define _INC_REG(register) { regs.register ++; inc_flags(regs.register); }
static void inc ()
{
  switch(instruction)
    {
    case 0x03:
      _INC_REG (regs.REGBC);
      break;
    case 0x04:
      _INC_REG (regs.REGB);
      break;
    case 0x0C:
      _INC_REG (regs.REGC);
      break;
    case 0x13:
      _INC_REG (regs.REGDE);
      break;
    case 0x14:
      _INC_REG (regs.REGD);
      break;
    case 0x1C:
      _INC_REG (regs.REGE);
      break;
    case 0x23:
      _INC_REG (regs.REGHL);
      break;
    case 0x24:
      _INC_REG (REGS.REGH);
      break;
    case 0x2C:
      _INC_REG (REGS.REGL);
      break;
    case 0x33:
      _INC_REG (REGS.REGSP);
      break;
    case 0x34:
      write_mem(
          regs.REGHL,
          read_mem (regs.REGHL) + 1);
      regs.REGHL ++;
      break;
    case 0x3C:
      _INC_REG (regs.REGA);
      break;
    }
}

static void dec_flags(
    uint8_t value)
{
  regs.FLAGSREG |= FLAG_N;
  if (!value)
    regs.FLAGSREG |= FLAG_Z;
  if (value & 0x7 == 0x7)
    regs.FLAGSREG |= FLAG_H;
}
/*
  dec()

  Decrement instruction. Takes some register based on the instruction and
  decrements whatever is there.
 */
#define _DEC_REG(register) { regs.register --; dec_flags(regs.register); }
static void dec ()
{
  switch (instruction)
    {
    case 0x05:
      _DEC_REG (regs.REGB);
      break;
    case 0x0B:
      _DEC_REG (regs.REGBC);
      break;
    case 0x0D:
      _DEC_REG (regs.REGC);
      break;
    case 0x15:
      _DEC_REG (regs.REGD);
      break;
    case 0x1B:
      _DEC_REG (regs.REGDE);
      break;
    case 0x1D:
      _DEC_REG (regs.REGE);
      break;
    case 0x25:
      _DEC_REG (regs.REGH);
      break;
    case 0x2B:
      _DEC_REG (regs.REGHL);
      break;
    case 0x2D:
      _DEC_REG (regs.REGL);
      break;
    case 0x35:
      write_mem(
          regs.REGHL,
          read_mem (regs.REGHL) - 1);
      break;
    case 0x3B:
      _DEC_REG (regs.REGSP);
      break;
    case 0x3D:
      _DEC_REG (regs.REGA);
      break;
    }
}

static void add (
    uint8_t * instruction)
{
  uint augend;
  uint addend;
}

int exec(
    uint8_t address)
{
  uint8_t cycles = 0;

  for (;;)
    {
      instruction = read_mem(
          address);

      switch (instruction)
        {
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
              "EMULATOR INTERNAL ERROR: Invalid opcode 0x%x !?\n",
              instruction);
        }

      cycles      += is[instruction].cycles;
      instruction += is[instruction].bytes;
      
    }
}
