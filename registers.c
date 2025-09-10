#include "registers.h"
#include <stdint.h>

Registers new_regs() {
  Registers regs = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
  return regs;
}

uint16_t get_bc(Registers *reg) {
  return (uint16_t)(reg->b) << 8 | (uint16_t)reg->c;
}

void set_bc(Registers *reg, uint16_t val) {
  reg->b = (uint8_t)((val & 0xFF00) >> 8);
  reg->c = (uint8_t)(val & 0x00FF);
}

FlagRegister new_flag_reg() {
  FlagRegister flag_reg = {false, false, false, false};
  return flag_reg;
}

uint8_t flag_reg_to_byte(FlagRegister *flag_reg) {
  uint8_t zero = ((flag_reg->zero) ? 1 : 0) << ZERO_BIT_POS;
  uint8_t subtract = ((flag_reg->subtract) ? 1 : 0) << SUBTRACT_BIT_POS;
  uint8_t half_carry = ((flag_reg->half_carry) ? 1 : 0) << HALF_CARRY_BIT_POS;
  uint8_t carry = (((flag_reg->carry) ? 1 : 0) << CARRY_BIT_POS);

  return zero | subtract | half_carry | carry;
}

FlagRegister byte_to_flag_reg(uint8_t byte) {
  FlagRegister flag_reg = {
      (((byte >> ZERO_BIT_POS) & 1) == 1) ? true : false,
      (((byte >> SUBTRACT_BIT_POS) & 1) == 1) ? true : false,
      (((byte >> HALF_CARRY_BIT_POS) & 1) == 1) ? true : false,
      (((byte >> CARRY_BIT_POS) & 1) == 1) ? true : false,
  };

  return flag_reg;
}
