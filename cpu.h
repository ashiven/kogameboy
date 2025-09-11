#include "instructions.h"
#include "registers.h"
#include <stdint.h>

typedef struct {
  Registers registers;
  FlagRegister flag_reg;

} CPU;

void execute(CPU *cpu, Instruction *instruction);

uint8_t reg_val(CPU *cpu, enum RegisterName target);

void set_reg(CPU *cpu, enum RegisterName target, uint8_t val);

void update_flags(CPU *cpu, bool zero, bool subtract, bool carry,
                  bool half_carry);

void add(CPU *cpu, enum RegisterName target);
void addhl(CPU *cpu, enum RegisterName target);
void adc(CPU *cpu, enum RegisterName target);
void sub(CPU *cpu, enum RegisterName target);
void sbc(CPU *cpu, enum RegisterName target);
void and_(CPU *cpu, enum RegisterName target);
void or_(CPU *cpu, enum RegisterName target);
void xor_(CPU *cpu, enum RegisterName target);
void cp(CPU *cpu, enum RegisterName target);
void inc(CPU *cpu, enum RegisterName target);
void dec(CPU *cpu, enum RegisterName target);
void ccf(CPU *cpu, enum RegisterName target);
void scf(CPU *cpu, enum RegisterName target);
void rra(CPU *cpu, enum RegisterName target);
void rla(CPU *cpu, enum RegisterName target);
void rrca(CPU *cpu, enum RegisterName target);
void rlca(CPU *cpu, enum RegisterName target);
void cpl(CPU *cpu, enum RegisterName target);
void bit(CPU *cpu, uint8_t bit_index, enum RegisterName target);
void reset(CPU *cpu, uint8_t bit_index, enum RegisterName target);
void set(CPU *cpu, uint8_t bit_index, enum RegisterName target);
void srl(CPU *cpu, enum RegisterName target);
void rr(CPU *cpu, enum RegisterName target);
void rl(CPU *cpu, enum RegisterName target);
void rrc(CPU *cpu, enum RegisterName target);
void rlc(CPU *cpu, enum RegisterName target);
void sra(CPU *cpu, enum RegisterName target);
void sla(CPU *cpu, enum RegisterName target);
void swap(CPU *cpu, enum RegisterName target);
