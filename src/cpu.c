#include "cpu.h"
#include <stdint.h>

void execute(CPU *cpu, Instruction *instruction) {
  switch (instruction->kind) {
  case ADD:
    add(cpu, instruction->target);
    break;
  case ADDHL:
    addhl(cpu, instruction->target);
    break;
  case ADC:
    adc(cpu, instruction->target);
    break;
  case SUB:
    sub(cpu, instruction->target);
    break;
  case SBC:
    sbc(cpu, instruction->target);
    break;
  case AND:
    and_(cpu, instruction->target);
    break;
  case OR:
    or_(cpu, instruction->target);
    break;
  case XOR:
    xor_(cpu, instruction->target);
    break;
  case CP:
    cp(cpu, instruction->target);
    break;
  case INC:
    inc(cpu, instruction->target);
    break;
  case DEC:
    dec(cpu, instruction->target);
    break;
  case CCF:
    ccf(cpu);
    break;
  case SCF:
    scf(cpu);
    break;
  case RRA:
    rra(cpu);
    break;
  case RLA:
    rla(cpu);
    break;
  case RRCA:
    rrca(cpu);
    break;
  case RLCA:
    rlca(cpu);
    break;
  case CPL:
    cpl(cpu);
    break;
  case BIT:
    bit(cpu, instruction->bit_index, instruction->target);
    break;
  case RESET:
    reset(cpu, instruction->bit_index, instruction->target);
    break;
  case SET:
    set(cpu, instruction->bit_index, instruction->target);
    break;
  case SRL:
    srl(cpu, instruction->target);
    break;
  case RR:
    rr(cpu, instruction->target);
    break;
  case RL:
    rl(cpu, instruction->target);
    break;
  case RRC:
    rrc(cpu, instruction->target);
    break;
  case RLC:
    rlc(cpu, instruction->target);
    break;
  case SRA:
    sra(cpu, instruction->target);
    break;
  case SLA:
    sla(cpu, instruction->target);
    break;
  case SWAP:
    swap(cpu, instruction->target);
    break;
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
  return 0;
}

void set_reg(CPU *cpu, enum RegisterName reg, uint8_t val) {
  switch (reg) {
  case A:
    cpu->registers.a = val;
    break;
  case B:
    cpu->registers.b = val;
    break;
  case C:
    cpu->registers.c = val;
    break;
  case D:
    cpu->registers.d = val;
    break;
  case E:
    cpu->registers.e = val;
    break;
  case F:
    cpu->registers.f = val;
    break;
  case H:
    cpu->registers.h = val;
    break;
  case L:
    cpu->registers.l = val;
    break;
  case BC:
    set_bc(&cpu->registers, val);
    break;
  case DE:
    set_de(&cpu->registers, val);
    break;
  case HL:
    set_hl(&cpu->registers, val);
    break;
  }
}

void update_flags(CPU *cpu, bool zero, bool subtract, bool half_carry,
                  bool carry) {
  cpu->flag_reg.zero = zero;
  cpu->flag_reg.subtract = subtract;
  cpu->flag_reg.half_carry = half_carry;
  cpu->flag_reg.carry = carry;

  cpu->registers.f = flag_reg_to_byte(&cpu->flag_reg);
}

void add(CPU *cpu, enum RegisterName target) {
  uint8_t acc = get_reg(cpu, A);
  uint8_t val = get_reg(cpu, target);
  // This will wrap around i.e.
  // acc = 1111_1111 and val = 0000_0010
  // --> res = 0000_0001
  uint8_t res = acc + val;

  bool zero = res == 0;
  bool subtract = false;
  bool half_carry = (acc & 0xF) + (val & 0xF) > 0xF;
  bool carry = acc + val > 0xFF;
  update_flags(cpu, zero, subtract, half_carry, carry);

  set_reg(cpu, A, res);
}

void addhl(CPU *cpu, enum RegisterName target) {
  uint16_t acc = get_reg(cpu, HL);
  // val is one of the 16 bit regs: BC, DE, HL, SP
  uint16_t val = get_reg(cpu, target);
  uint16_t res = acc + val;

  bool zero = res == 0;
  bool subtract = false;
  bool half_carry = (acc & 0xFF) + (val & 0xFF) > 0xFF;
  bool carry = acc + val > 0xFFFF;
  update_flags(cpu, zero, subtract, half_carry, carry);

  set_reg(cpu, HL, res);
}

void adc(CPU *cpu, enum RegisterName target) {
  uint8_t acc = get_reg(cpu, A);
  uint8_t val = get_reg(cpu, target);
  uint8_t c = get_carry(&cpu->flag_reg);
  uint8_t res = acc + val + c;

  bool zero = res == 0;
  bool subtract = false;
  bool half_carry = (acc & 0xF) + (val & 0xF) + (c & 0xF) > 0xF;
  bool carry = acc + val + c > 0xFF;
  update_flags(cpu, zero, subtract, half_carry, carry);

  set_reg(cpu, A, res);
}

void sub(CPU *cpu, enum RegisterName target) {
  uint8_t acc = get_reg(cpu, A);
  uint8_t val = get_reg(cpu, target);
  uint8_t res = acc - val;

  bool zero = res == 0;
  bool subtract = true;
  bool half_carry = (acc & 0xF) >= (val & 0xF);
  bool carry = acc >= val;
  update_flags(cpu, zero, subtract, half_carry, carry);

  set_reg(cpu, A, res);
}

void sbc(CPU *cpu, enum RegisterName target) {
  uint8_t acc = get_reg(cpu, A);
  uint8_t val = get_reg(cpu, target);
  uint8_t c = get_carry(&cpu->flag_reg);
  uint8_t res = acc - val - c;

  bool zero = res == 0;
  bool subtract = true;
  bool half_carry = (acc & 0xF) >= (val & 0xF) + (c & 0xF);
  bool carry = acc >= (val + c);
  update_flags(cpu, zero, subtract, half_carry, carry);

  set_reg(cpu, A, res);
}

void and_(CPU *cpu, enum RegisterName target) {
  uint8_t acc = get_reg(cpu, A);
  uint8_t val = get_reg(cpu, target);
  uint8_t res = acc && val;

  bool zero = res == 0;
  bool subtract = false;
  bool half_carry = true;
  bool carry = false;
  update_flags(cpu, zero, subtract, half_carry, carry);

  set_reg(cpu, A, res);
}

void or_(CPU *cpu, enum RegisterName target) {
  uint8_t acc = get_reg(cpu, A);
  uint8_t val = get_reg(cpu, target);
  uint8_t res = acc || val;

  bool zero = res == 0;
  bool subtract = false;
  bool half_carry = true;
  bool carry = false;
  update_flags(cpu, zero, subtract, half_carry, carry);

  set_reg(cpu, A, res);
}

void xor_(CPU *cpu, enum RegisterName target) {
  uint8_t acc = get_reg(cpu, A);
  uint8_t val = get_reg(cpu, target);
  uint8_t res = acc ^ val;

  bool zero = res == 0;
  bool subtract = false;
  bool half_carry = true;
  bool carry = false;
  update_flags(cpu, zero, subtract, half_carry, carry);

  set_reg(cpu, A, res);
}

void cp(CPU *cpu, enum RegisterName target) {
  uint8_t acc = get_reg(cpu, A);
  uint8_t val = get_reg(cpu, target);
  uint8_t res = acc - val;

  bool zero = res == 0;
  bool subtract = true;
  bool half_carry = (acc & 0xF) >= (val & 0xF);
  bool carry = acc >= val;
  update_flags(cpu, zero, subtract, half_carry, carry);
}

void inc(CPU *cpu, enum RegisterName target) {
  uint8_t val = get_reg(cpu, target);
  uint8_t res = val + 1;

  bool zero = res == 0;
  bool subtract = false;
  bool half_carry = (val & 0xF) + 1 > 0xF;
  bool carry = cpu->flag_reg.carry;
  update_flags(cpu, zero, subtract, half_carry, carry);

  set_reg(cpu, target, res);
}

void dec(CPU *cpu, enum RegisterName target) {
  uint8_t val = get_reg(cpu, target);
  uint8_t res = val - 1;

  bool zero = res == 0;
  bool subtract = true;
  bool half_carry = (val & 0xF) >= 1;
  bool carry = cpu->flag_reg.carry;
  update_flags(cpu, zero, subtract, half_carry, carry);

  set_reg(cpu, target, res);
}

void ccf(CPU *cpu) {
  bool zero = cpu->flag_reg.zero;
  bool subtract = false;
  bool half_carry = false;
  bool carry = !cpu->flag_reg.carry;
  update_flags(cpu, zero, subtract, half_carry, carry);
}

void scf(CPU *cpu) {
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
void rra(CPU *cpu) {
  uint8_t acc = get_reg(cpu, A);
  uint8_t lsb = acc & 1;
  uint8_t c = get_carry(&cpu->flag_reg);
  uint8_t res = c << 7 | acc >> 1;

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
void rla(CPU *cpu) {
  uint8_t acc = get_reg(cpu, A);
  uint8_t msb = (acc >> 7) & 1;
  uint8_t c = get_carry(&cpu->flag_reg);
  uint8_t res = acc << 1 | c;

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
 * b0  b0 b7 b6 b5 b4 b3 b2 b1
 */
void rrca(CPU *cpu) {
  uint8_t acc = get_reg(cpu, A);
  uint8_t lsb = acc & 1;
  uint8_t res = lsb << 7 | acc >> 1;

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
 * b7  b6 b5 b4 b3 b2 b1 b0 b7
 */
void rlca(CPU *cpu) {
  uint8_t acc = get_reg(cpu, A);
  uint8_t msb = (acc >> 7) & 1;
  uint8_t res = acc << 1 | msb;

  bool zero = res == 0;
  bool subtract = false;
  bool half_carry = false;
  bool carry = msb == 1;
  update_flags(cpu, zero, subtract, half_carry, carry);

  set_reg(cpu, A, res);
}

void cpl(CPU *cpu) {
  uint8_t acc = get_reg(cpu, A);
  uint8_t res = ~acc;

  bool zero = cpu->flag_reg.zero;
  bool subtract = true;
  bool half_carry = true;
  bool carry = cpu->flag_reg.carry;
  update_flags(cpu, zero, subtract, half_carry, carry);

  set_reg(cpu, A, res);
}

void bit(CPU *cpu, uint8_t bit_index, enum RegisterName target) {
  uint8_t val = get_reg(cpu, target);
  uint8_t bit = (val >> bit_index) & 1;

  bool zero = bit == 0;
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
  uint8_t val = get_reg(cpu, target);
  uint8_t res = val & ~(1 << bit_index);

  set_reg(cpu, target, res);
}

/* Set bit at bit_index to 1
 * For example, to set b6:
 *
 * b7 b6 b5 b4 b3 b2 b1 b0
 *
 * |
 *
 * 0  1  0  0  0  0  0  0
 * */
void set(CPU *cpu, uint8_t bit_index, enum RegisterName target) {
  uint8_t val = get_reg(cpu, target);
  uint8_t res = val | (1 << bit_index);

  set_reg(cpu, target, res);
}

/* Shift target right into carry
 * - lsb becomes new carry
 * - msb becomes 0
 * - the rest of the bits are right shifted
 *
 * c   b7 b6 b5 b4 b3 b2 b1 b0
 *
 * b0  0 b7 b6 b5 b4 b3 b2 b1
 */
void srl(CPU *cpu, enum RegisterName target) {
  uint8_t val = get_reg(cpu, target);
  uint8_t lsb = val & 1;
  uint8_t res = val >> 1;

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
  uint8_t val = get_reg(cpu, target);
  uint8_t lsb = val & 1;
  uint8_t c = get_carry(&cpu->flag_reg);
  uint8_t res = c << 7 | val >> 1;

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
  uint8_t val = get_reg(cpu, target);
  uint8_t msb = (val >> 7) & 1;
  uint8_t c = get_carry(&cpu->flag_reg);
  uint8_t res = val << 1 | c;

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
 * b0  b0 b7 b6 b5 b4 b3 b2 b1
 */
void rrc(CPU *cpu, enum RegisterName target) {
  uint8_t val = get_reg(cpu, target);
  uint8_t lsb = val & 1;
  uint8_t res = (lsb << 7) | val >> 1;

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
 * b7  b6 b5 b4 b3 b2 b1 b0 b7
 */
void rlc(CPU *cpu, enum RegisterName target) {
  uint8_t val = get_reg(cpu, target);
  uint8_t msb = (val >> 7) & 1;
  uint8_t res = val << 1 | msb;

  bool zero = res == 0;
  bool subtract = false;
  bool half_carry = false;
  bool carry = msb == 1;
  update_flags(cpu, zero, subtract, half_carry, carry);

  set_reg(cpu, target, res);
}

/* Shift target right into carry (also sign extend)
 * - lsb becomes new carry
 * - msb is duplicated
 * - bits are right shifted
 *
 * c  b7 b6 b5 b4 b3 b2 b1 b0
 *
 * b0 b7 b7 b6 b5 b4 b3 b2 b1
 */
void sra(CPU *cpu, enum RegisterName target) {
  uint8_t val = get_reg(cpu, target);
  uint8_t lsb = val & 1;
  uint8_t msb = (val >> 7) & 1;
  uint8_t res = msb << 7 | val >> 1;

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
  uint8_t val = get_reg(cpu, target);
  uint8_t msb = (val >> 7) & 1;
  uint8_t res = val << 1;

  bool zero = res == 0;
  bool subtract = false;
  bool half_carry = false;
  bool carry = msb == 1;
  update_flags(cpu, zero, subtract, half_carry, carry);

  set_reg(cpu, target, res);
}

void swap(CPU *cpu, enum RegisterName target) {
  uint8_t val = get_reg(cpu, target);
  uint8_t lower_nibble = val & 0xF;
  uint8_t upper_nibble = (val >> 4) & 0xF;
  uint8_t res = lower_nibble << 4 | upper_nibble;

  bool zero = res == 0;
  bool subtract = false;
  bool half_carry = false;
  bool carry = false;
  update_flags(cpu, zero, subtract, half_carry, carry);

  set_reg(cpu, target, res);
}
