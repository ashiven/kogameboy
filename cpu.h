#include "instructions.h"
#include "registers.h"

typedef struct {
  Registers registers;

} CPU;

void execute(CPU *cpu, Instruction *instruction);

uint8_t reg_val(CPU *cpu, enum ArithmeticTarget target);

void add(CPU *cpu, enum ArithmeticTarget target);
