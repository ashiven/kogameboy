#include "cpu.h"
#include <stdint.h>

void execute(CPU *cpu, Instruction *instruction) {

  switch (instruction->kind) {
  case ADD:
    add(cpu, instruction->target);
  case ADDHL:
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

void add(CPU *cpu, enum ArithmeticTarget target) {
  uint8_t target_val = reg_val(cpu, target);
  // TODO: overflowing add
  uint8_t res = cpu->registers.a + target_val;
  cpu->registers.a = res;
}
