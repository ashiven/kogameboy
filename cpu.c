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
    cp(cpu, instruction->target);
  case INC:
    inc(cpu, instruction->target);
  case DEC:
    dec(cpu, instruction->target);
  case CCF:
    ccf(cpu, instruction->target);
  case SCF:
    scf(cpu, instruction->target);
  case RRA:
    rra(cpu, instruction->target);
  case RLA:
    rla(cpu, instruction->target);
  case RRCA:
    rrca(cpu, instruction->target);
  case RLCA:
    rlca(cpu, instruction->target);
  case CPL:
    cpl(cpu, instruction->target);
  case BIT:
    bit(cpu, instruction->bit_index, instruction->target);
  case RESET:
    reset(cpu, instruction->bit_index, instruction->target);
  case SET:
    set(cpu, instruction->bit_index, instruction->target);
  case SRL:
    srl(cpu, instruction->target);
  case RR:
    rr(cpu, instruction->target);
  case RL:
    rl(cpu, instruction->target);
  case RRC:
    rrc(cpu, instruction->target);
  case RLC:
    rlc(cpu, instruction->target);
  case SRA:
    sra(cpu, instruction->target);
  case SLA:
    sla(cpu, instruction->target);
  case SWAP:
    swap(cpu, instruction->target);
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

void update_flags(CPU *cpu, bool zero, bool subtract, bool half_carry,
                  bool carry) {
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

/* Rotate A right through carry
 * - lsb becomes new carry
 * - carry becomes new msb
 * - the rest of the bits are right shifted
 *
 * c   b7 b6 b5 b4 b3 b2 b1 b0
 *
 * b0  c b7 b6 b5 b4 b3 b2 b1
 */
void rra(CPU *cpu, enum RegisterName target) {
  uint8_t lsb = get_reg(cpu, A) & 1;
  // NOTE: The fill-in value for logic shifts is 0, while it is a sign extension
  // for right arithmetic shifts. Just keep that in mind. (However, since we are
  // working with unsigned values, we should only get logic shifts)
  uint8_t res = get_carry(&cpu->flag_reg) << 7 | get_reg(cpu, A) >> 1;

  bool zero = res == 0;
  bool subtract = false;
  bool half_carry = false;
  bool carry = lsb == 1;
  update_flags(cpu, zero, subtract, half_carry, carry);

  set_reg(cpu, A, res);
}

/* Rotate A left through carry
 * - msb becomes new carry
 * - carry becomes new lsb
 * - the rest of the bits are left shifted
 *
 * c   b7 b6 b5 b4 b3 b2 b1 b0
 *
 * b7  b6 b5 b4 b3 b2 b1 b0 c
 */
void rla(CPU *cpu, enum RegisterName target) {
  uint8_t msb = get_reg(cpu, A) & (1 << 7);
  uint8_t res = get_carry(&cpu->flag_reg) | get_reg(cpu, A) << 1;

  bool zero = res == 0;
  bool subtract = false;
  bool half_carry = false;
  bool carry = msb == 1;
  update_flags(cpu, zero, subtract, half_carry, carry);

  set_reg(cpu, A, res);
}

/* Rotate A right and set carry to lsb
 * - lsb becomes new carry
 * - the rest of the bits are right shifted
 *
 * c   b7 b6 b5 b4 b3 b2 b1 b0
 *
 * b0  0 b7 b6 b5 b4 b3 b2 b1
 */
void rrca(CPU *cpu, enum RegisterName target) {
  uint8_t lsb = get_reg(cpu, A) & 1;
  uint8_t res = get_reg(cpu, A) >> 1;

  bool zero = res == 0;
  bool subtract = false;
  bool half_carry = false;
  bool carry = lsb == 1;
  update_flags(cpu, zero, subtract, half_carry, carry);

  set_reg(cpu, A, res);
}

/* Rotate A left and set carry to msb
 * - msb becomes new carry
 * - the rest of the bits are left shifted
 *
 * c   b7 b6 b5 b4 b3 b2 b1 b0
 *
 * b7  b6 b5 b4 b3 b2 b1 b0 0
 */
void rlca(CPU *cpu, enum RegisterName target) {
  uint8_t msb = get_reg(cpu, A) & (1 << 7);
  uint8_t res = get_reg(cpu, A) << 1;

  bool zero = res == 0;
  bool subtract = false;
  bool half_carry = false;
  bool carry = msb == 1;
  update_flags(cpu, zero, subtract, half_carry, carry);

  set_reg(cpu, A, res);
}

void cpl(CPU *cpu, enum RegisterName target) {
  uint8_t res = ~get_reg(cpu, A);

  bool zero = cpu->flag_reg.zero;
  bool subtract = true;
  bool half_carry = true;
  bool carry = cpu->flag_reg.carry;
  update_flags(cpu, zero, subtract, half_carry, carry);

  set_reg(cpu, A, res);
}

void bit(CPU *cpu, uint8_t bit_index, enum RegisterName target) {
  uint8_t test_bit = (get_reg(cpu, target) >> bit_index) & 1;

  bool zero = test_bit == 0;
  bool subtract = false;
  bool half_carry = true;
  bool carry = cpu->flag_reg.carry;
  update_flags(cpu, zero, subtract, half_carry, carry);
}

/* Reset bit at bit_index to 0
 * For example, to reset b6:
 *
 * b7 b6 b5 b4 b3 b2 b1 b0
 *
 * &
 *
 * 1  0  1  1  1  1  1  1
 * */
void reset(CPU *cpu, uint8_t bit_index, enum RegisterName target) {
  uint8_t res = get_reg(cpu, target) & ~(1 << bit_index);

  set_reg(cpu, target, res);
}

/* Set bit at bit_index to 1
 * For example, to set b6:
 *
 * b7 b6 b5 b4 b3 b2 b1 b0
 *
 * ||
 *
 * 0  1  0  0  0  0  0  0
 * */
void set(CPU *cpu, uint8_t bit_index, enum RegisterName target) {
  uint8_t res = get_reg(cpu, target) || (1 << bit_index);

  set_reg(cpu, target, res);
}

void srl(CPU *cpu, enum RegisterName target) {
  uint8_t lsb = get_reg(cpu, target) & 1;
  uint8_t res = get_reg(cpu, target) >> 1;

  bool zero = res == 0;
  bool subtract = false;
  bool half_carry = false;
  bool carry = lsb == 1;
  update_flags(cpu, zero, subtract, half_carry, carry);

  set_reg(cpu, target, res);
}

/* Rotate target right through carry
 * - lsb becomes new carry
 * - carry becomes new msb
 * - the rest of the bits are right shifted
 *
 * c   b7 b6 b5 b4 b3 b2 b1 b0
 *
 * b0  c b7 b6 b5 b4 b3 b2 b1
 */
void rr(CPU *cpu, enum RegisterName target) {
  uint8_t lsb = get_reg(cpu, target) & 1;
  uint8_t res = get_carry(&cpu->flag_reg) << 7 | get_reg(cpu, target) >> 1;

  bool zero = res == 0;
  bool subtract = false;
  bool half_carry = false;
  bool carry = lsb == 1;
  update_flags(cpu, zero, subtract, half_carry, carry);

  set_reg(cpu, target, res);
}

/* Rotate target left through carry
 * - msb becomes new carry
 * - carry becomes new lsb
 * - the rest of the bits are left shifted
 *
 * c   b7 b6 b5 b4 b3 b2 b1 b0
 *
 * b7  b6 b5 b4 b3 b2 b1 b0 c
 */
void rl(CPU *cpu, enum RegisterName target) {
  uint8_t msb = get_reg(cpu, target) & (1 << 7);
  uint8_t res = get_carry(&cpu->flag_reg) | get_reg(cpu, target) << 1;

  bool zero = res == 0;
  bool subtract = false;
  bool half_carry = false;
  bool carry = msb == 1;
  update_flags(cpu, zero, subtract, half_carry, carry);

  set_reg(cpu, target, res);
}

/* Rotate target right and set carry to lsb
 * - lsb becomes new carry
 * - the rest of the bits are right shifted
 *
 * c   b7 b6 b5 b4 b3 b2 b1 b0
 *
 * b0  0 b7 b6 b5 b4 b3 b2 b1
 */
void rrc(CPU *cpu, enum RegisterName target) {
  uint8_t lsb = get_reg(cpu, target) & 1;
  uint8_t res = get_reg(cpu, target) >> 1;

  bool zero = res == 0;
  bool subtract = false;
  bool half_carry = false;
  bool carry = lsb == 1;
  update_flags(cpu, zero, subtract, half_carry, carry);

  set_reg(cpu, target, res);
}

/* Rotate A left and set carry to msb
 * - msb becomes new carry
 * - the rest of the bits are left shifted
 *
 * c   b7 b6 b5 b4 b3 b2 b1 b0
 *
 * b7  b6 b5 b4 b3 b2 b1 b0 0
 */
void rlc(CPU *cpu, enum RegisterName target) {
  uint8_t msb = get_reg(cpu, target) & (1 << 7);
  uint8_t res = get_reg(cpu, target) << 1;

  bool zero = res == 0;
  bool subtract = false;
  bool half_carry = false;
  bool carry = msb == 1;
  update_flags(cpu, zero, subtract, half_carry, carry);

  set_reg(cpu, target, res);
}

/* Shift target right into carry (also sign extend)
 * - lsb becomes new carry
 *
 * c  b7 b6 b5 b4 b3 b2 b1 b0
 *
 * b0 b7 b7 b6 b5 b4 b3 b2 b1
 */
void sra(CPU *cpu, enum RegisterName target) {
  uint8_t lsb = get_reg(cpu, target) & 1;
  uint8_t msb = get_reg(cpu, target) & (1 << 7);
  uint8_t res = msb | get_reg(cpu, target) >> 1;

  bool zero = res == 0;
  bool subtract = false;
  bool half_carry = false;
  bool carry = lsb == 1;
  update_flags(cpu, zero, subtract, half_carry, carry);

  set_reg(cpu, target, res);
}

/* Shift target left into carry
 * - msb becomes new carry
 *
 * c  b7 b6 b5 b4 b3 b2 b1 b0
 *
 * b7 b6 b5 b4 b3 b2 b1 b0 0
 */
void sla(CPU *cpu, enum RegisterName target) {
  uint8_t msb = get_reg(cpu, target) & (1 << 7);
  uint8_t res = get_reg(cpu, target) << 1;

  bool zero = res == 0;
  bool subtract = false;
  bool half_carry = false;
  bool carry = msb == 1;
  update_flags(cpu, zero, subtract, half_carry, carry);

  set_reg(cpu, target, res);
}

void swap(CPU *cpu, enum RegisterName target) {
  uint8_t lower_half = get_reg(cpu, target) & 0xF;
  uint8_t upper_half = (get_reg(cpu, target) >> 4) & 0xF;
  uint8_t res = lower_half << 4 | upper_half;

  bool zero = res == 0;
  bool subtract = false;
  bool half_carry = false;
  bool carry = false;
  update_flags(cpu, zero, subtract, half_carry, carry);

  set_reg(cpu, target, res);
}
