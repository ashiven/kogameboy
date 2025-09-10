#include "cpu.h"
#include <stdint.h>

void execute(CPU *cpu, Instruction *instruction) {
  switch (instruction->kind) {
  case ADD:
    add(cpu, instruction->target);
  case ADDHL:
    addhl(cpu, instruction->target);
  case ADC:
  case SUB:
  case SBC:
  case AND:
  case OR:
  case XOR:
  case CP:
  case INC:
  case DEC:
  case CCF:
  case SCF:
  case RRA:
  case RLA:
  case RRCA:
  case RRLA:
  case CPL:
  case BIT:
  case RESET:
  case SET:
  case SRL:
  case RR:
  case RL:
  case RRC:
  case RLC:
  case SRA:
  case SLA:
  case SWAP:
  }
}

uint8_t reg_val(CPU *cpu, enum ArithmeticTarget target) {
  switch (target) {
  case A:
    return cpu->registers.a;
  case B:
    return cpu->registers.b;
  case C:
    return cpu->registers.c;
  case D:
    return cpu->registers.d;
  case E:
    return cpu->registers.e;
  case H:
    return cpu->registers.h;
  case L:
    return cpu->registers.l;
  }
}

void update_flags(CPU *cpu, bool zero, bool subtract, bool carry,
                  bool half_carry) {
  cpu->flag_reg.zero = zero;
  cpu->flag_reg.subtract = subtract;
  cpu->flag_reg.carry = carry;
  cpu->flag_reg.half_carry = half_carry;

  cpu->registers.f = flag_reg_to_byte(&cpu->flag_reg);
}

void add(CPU *cpu, enum ArithmeticTarget target) {
  uint8_t target_val = reg_val(cpu, target);
  // TODO: overflowing add
  uint8_t res = cpu->registers.a + target_val;

  bool zero = res == 0;
  bool subtract = false;
  // TODO: overflowing add res
  bool carry = false;
  // NOTE: checks if lower half of the res byte is greater than binary 1111
  bool half_carry = (target_val & 0xF) + (cpu->registers.a & 0xF) > 0xF;

  update_flags(cpu, zero, subtract, carry, half_carry);

  cpu->registers.a = res;
}

void addhl(CPU *cpu, enum ArithmeticTarget target) {
  uint8_t target_val = reg_val(cpu, target);
  // TODO: overflowing add
  uint16_t res = get_hl(&cpu->registers) + target_val;

  bool zero = res == 0;
  bool subtract = false;
  // TODO: overflowing add res
  bool carry = false;
  // NOTE: checks if lower half of the res byte is greater than binary 1111_1111
  bool half_carry =
      (target_val & 0xFF) + (get_hl(&cpu->registers) & 0xFF) > 0xFF;

  update_flags(cpu, zero, subtract, carry, half_carry);

  set_hl(&cpu->registers, res);
}
