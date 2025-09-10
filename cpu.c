#include "cpu.h"
#include <stdint.h>

void execute(CPU *cpu, Instruction *instruction) {
  switch (instruction->kind) {
  case ADD:
    add(cpu, instruction->target);
  case ADDHL:
    addhl(cpu, instruction->target);
  case ADC:
    adc(cpu, instruction->target);
  case SUB:
    sub(cpu, instruction->target);
  case SBC:
    sbc(cpu, instruction->target);
  case AND:
    and_(cpu, instruction->target);
  case OR:
    or_(cpu, instruction->target);
  case XOR:
    xor_(cpu, instruction->target);
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

uint8_t get_reg(CPU *cpu, enum RegisterName reg) {
  switch (reg) {
  case A:
    return get_reg(cpu, A);
  case B:
    return cpu->registers.b;
  case C:
    return cpu->registers.c;
  case D:
    return cpu->registers.d;
  case E:
    return cpu->registers.e;
  case F:
    return cpu->registers.f;
  case H:
    return cpu->registers.h;
  case L:
    return cpu->registers.l;
  case BC:
    return get_bc(&cpu->registers);
  case DE:
    return get_de(&cpu->registers);
  case HL:
    return get_hl(&cpu->registers);
  }
}

void set_reg(CPU *cpu, enum RegisterName reg, uint8_t val) {
  switch (reg) {
  case A:
    cpu->registers.a = val;
  case B:
    cpu->registers.b = val;
  case C:
    cpu->registers.c = val;
  case D:
    cpu->registers.d = val;
  case E:
    cpu->registers.e = val;
  case F:
    cpu->registers.f = val;
  case H:
    cpu->registers.h = val;
  case L:
    cpu->registers.l = val;
  case BC:
    set_bc(&cpu->registers, val);
  case DE:
    set_de(&cpu->registers, val);
  case HL:
    set_hl(&cpu->registers, val);
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

void add(CPU *cpu, enum RegisterName target) {
  uint8_t val = get_reg(cpu, target);
  // TODO: overflowing add
  uint8_t res = get_reg(cpu, A) + val;

  bool zero = res == 0;
  bool subtract = false;
  // TODO: overflowing add res
  bool carry = false;
  // NOTE: checks if lower half of the res byte is greater than binary 1111
  bool half_carry = (val & 0xF) + (get_reg(cpu, A) & 0xF) > 0xF;
  update_flags(cpu, zero, subtract, carry, half_carry);

  set_reg(cpu, A, res);
}

// TODO: target has to be either BC, DE, HL, or SP
void addhl(CPU *cpu, enum RegisterName target) {
  uint8_t val = get_reg(cpu, target);
  // TODO: overflowing add
  uint16_t res = get_hl(&cpu->registers) + val;

  bool zero = res == 0;
  bool subtract = false;
  // TODO: overflowing add res
  bool carry = false;
  // NOTE: checks if lower half of the res byte is greater than binary 1111_1111
  bool half_carry = (val & 0xFF) + (get_hl(&cpu->registers) & 0xFF) > 0xFF;
  update_flags(cpu, zero, subtract, carry, half_carry);

  set_hl(&cpu->registers, res);
}

void adc(CPU *cpu, enum RegisterName target) {
  uint8_t val = get_reg(cpu, target);
  uint8_t carry_val = (cpu->registers.f >> CARRY_BIT_POS) & 1;
  // TODO: overflowing add
  uint8_t res = get_reg(cpu, A) + val + carry_val;

  bool zero = res == 0;
  bool subtract = false;
  // TODO: overflowing add res
  bool carry = false;
  // NOTE: checks if lower half of the res byte is greater than binary 1111
  bool half_carry =
      (get_reg(cpu, A) & 0xF) + (val & 0xF) + (carry_val & 0xF) > 0xF;
  update_flags(cpu, zero, subtract, carry, half_carry);

  set_reg(cpu, A, res);
}

void sub(CPU *cpu, enum RegisterName target) {
  uint8_t val = get_reg(cpu, target);
  uint8_t res = get_reg(cpu, A) - val;

  bool zero = res == 0;
  bool subtract = true;
  bool carry = false;
  bool half_carry = false;
  update_flags(cpu, zero, subtract, carry, half_carry);

  set_reg(cpu, A, res);
}

void sbc(CPU *cpu, enum RegisterName target) {
  uint8_t val = get_reg(cpu, target);
  uint8_t carry_val = (cpu->registers.f >> CARRY_BIT_POS) & 1;
  uint8_t res = get_reg(cpu, A) - val - carry_val;

  bool zero = res == 0;
  bool subtract = true;
  bool carry = false;
  bool half_carry = false;
  update_flags(cpu, zero, subtract, carry, half_carry);

  set_reg(cpu, A, res);
}

void and_(CPU *cpu, enum RegisterName target) {
  uint8_t val = get_reg(cpu, target);
  uint8_t res = get_reg(cpu, A) && val;

  bool zero = res == 0;
  bool subtract = false;
  bool carry = false;
  bool half_carry = false;
  update_flags(cpu, zero, subtract, carry, half_carry);

  set_reg(cpu, A, res);
}

void or_(CPU *cpu, enum RegisterName target) {
  uint8_t val = get_reg(cpu, target);
  uint8_t res = get_reg(cpu, A) || val;

  bool zero = res == 0;
  bool subtract = false;
  bool carry = false;
  bool half_carry = false;
  update_flags(cpu, zero, subtract, carry, half_carry);

  set_reg(cpu, A, res);
}

void xor_(CPU *cpu, enum RegisterName target) {
  uint8_t val = get_reg(cpu, target);
  uint8_t res = get_reg(cpu, A) ^ val;

  bool zero = res == 0;
  bool subtract = false;
  bool carry = false;
  bool half_carry = false;
  update_flags(cpu, zero, subtract, carry, half_carry);

  set_reg(cpu, A, res);
}

void cp(CPU *cpu, enum RegisterName target) {
  uint8_t val = get_reg(cpu, target);
  uint8_t res = get_reg(cpu, A) - val;

  bool zero = res == 0;
  bool subtract = true;
  bool carry = false;
  bool half_carry = false;
  update_flags(cpu, zero, subtract, carry, half_carry);
}

void inc(CPU *cpu, enum RegisterName target) {
  uint8_t val = get_reg(cpu, target);
  uint8_t res = val + 1;

  bool zero = res == 0;
  bool subtract = false;
  bool carry = false;
  bool half_carry = false;
  update_flags(cpu, zero, subtract, carry, half_carry);

  set_reg(cpu, target, res);
}

void dec(CPU *cpu, enum RegisterName target) {
  uint8_t val = get_reg(cpu, target);
  uint8_t res = val - 1;

  bool zero = res == 0;
  bool subtract = true;
  bool carry = false;
  bool half_carry = false;
  update_flags(cpu, zero, subtract, carry, half_carry);

  set_reg(cpu, target, res);
}

void ccf(CPU *cpu, enum RegisterName target) {
  bool zero = cpu->flag_reg.zero;
  bool subtract = false;
  bool half_carry = false;
  bool carry = !cpu->flag_reg.carry;
  update_flags(cpu, zero, subtract, half_carry, carry);
}

void scf(CPU *cpu, enum RegisterName target) {
  bool zero = cpu->flag_reg.zero;
  bool subtract = false;
  bool half_carry = false;
  bool carry = true;
  update_flags(cpu, zero, subtract, half_carry, carry);
}
