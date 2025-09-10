#include "instructions.h"
#include "registers.h"

typedef struct {
  Registers registers;

} CPU;

void execute(CPU *cpu, Instruction *instruction);
