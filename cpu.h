#include "instructions.h"
#include "registers.h"
#include <stdint.h>

typedef struct {
  Registers registers;
  FlagRegister flag_reg;

} CPU;

void execute(CPU *cpu, Instruction *instruction);

uint8_t reg_val(CPU *cpu, enum ArithmeticTarget target);

void update_flags(CPU *cpu, bool zero, bool subtract, bool carry,
                  bool half_carry);

void add(CPU *cpu, enum ArithmeticTarget target);

void addhl(CPU *cpu, enum ArithmeticTarget target);
