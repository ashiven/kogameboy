#include "registers.h"
#include <stdint.h>

Registers new_regs() {
  Registers regs = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
  return regs;
}

uint16_t get_bc(Registers *regs) {
  return (uint16_t)(regs->b) << 8 | (uint16_t)regs->c;
}

void set_bc(Registers *regs, uint16_t val) {
  regs->b = (uint8_t)((val & 0xFF00) >> 8);
  regs->c = (uint8_t)(val & 0x00FF);
}

uint16_t get_de(Registers *regs) {
  return (uint16_t)(regs->d) << 8 | (uint16_t)regs->e;
}

void set_de(Registers *regs, uint16_t val) {
  regs->d = (uint8_t)((val & 0xFF00) >> 8);
  regs->e = (uint8_t)(val & 0x00FF);
}

uint16_t get_hl(Registers *regs) {
  return (uint16_t)(regs->h) << 8 | (uint16_t)regs->l;
}

void set_hl(Registers *regs, uint16_t val) {
  regs->h = (uint8_t)((val & 0xFF00) >> 8);
  regs->l = (uint8_t)(val & 0x00FF);
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

/* get_zero_bit returns 0000_0001 if zero flag is set
 * and 0000_0000 otherwise.
 */
uint8_t get_zero(FlagRegister *flag_reg) { return flag_reg->zero ? 1 : 0; }

/* get_subtract_bit returns 0000_0001 if subtract flag is set
 * and 0000_0000 otherwise.
 */
uint8_t get_subtract(FlagRegister *flag_reg) {
  return flag_reg->subtract ? 1 : 0;
}

/* get_half_carry_bit returns 0000_0001 if half_carry flag is set
 * and 0000_0000 otherwise.
 */
uint8_t get_half_carry(FlagRegister *flag_reg) {
  return flag_reg->half_carry ? 1 : 0;
}

/* get_carry_bit returns 0000_0001 if carry flag is set
 * and 0000_0000 otherwise.
 */
uint8_t get_carry(FlagRegister *flag_reg) { return flag_reg->carry ? 1 : 0; }
