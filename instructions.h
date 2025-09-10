#include <stdint.h>

enum InstructionKind {
  ADD,   /*Add target to register A*/
  ADDHL, /*Add target to register HL*/
  ADC,   /*Add target and value of carry flag to register A*/
  SUB,   /*Subtract target from register A*/
  SBC,   /*Subtract target and carry flag from register A*/
  AND,   /*Bitwise AND between target and register A*/
  OR,    /*Bitwise OR between target and register A*/
  XOR,   /*Bitwise XOR between target and register A*/
  CP,    /*Subtract without storing the result in A*/
  INC,   /*Increment the value in target by 1*/
  DEC,   /*Decrement the value in target by 1*/
  CCF,   /*Toggle value of the carry flag*/
  SCF,   /*Set carry flag to true*/
  RRA,   /*Bit rotate right register A through carry flag*/
  RLA,   /*Bit rotate left register A through carry flag*/
  RRCA,  /*Bit rotate right register A not through carry flag*/
  RRLA,  /*Bit rotate left register A not through carry flag*/
  CPL,   /*Toggle every bit of the A register*/
  BIT,   /*Test whether a specific bit of register A is set*/
  RESET, /*Reset a bit of target to 0*/
  SET,   /*Set a bit of target to 1*/
  SRL,   /*Bit shift target to the right by 1*/
  RR,    /*Bit rotate right target through carry flag*/
  RL,    /*Bit rotate left target through carry flag*/
  RRC,   /*Bit rotate right target not through carry flag*/
  RLC,   /*Bit rotate left target not through carry flag*/
  SRA,   /*Arithmetic shift target to the right by 1*/
  SLA,   /*Arithmetic shift target to the left by 1*/
  SWAP,  /*swap the upper and lower halfs (4 Bits each) of the target*/
};

enum ArithmeticTarget { A, B, C, D, E, H, L };

typedef struct {
  enum InstructionKind kind;
  enum ArithmeticTarget target;
  enum ArithmeticTarget source;
} Instruction;

const Instruction new_add(enum ArithmeticTarget target);
const Instruction new_addhl(enum ArithmeticTarget target);
const Instruction new_adc(enum ArithmeticTarget target);
const Instruction new_sub(enum ArithmeticTarget target);
const Instruction new_sbc(enum ArithmeticTarget target);
const Instruction new_and(enum ArithmeticTarget target);
const Instruction new_or(enum ArithmeticTarget target);
const Instruction new_xor(enum ArithmeticTarget target);
const Instruction new_cp(enum ArithmeticTarget target);
const Instruction new_inc(enum ArithmeticTarget target);
const Instruction new_dec(enum ArithmeticTarget target);
const Instruction new_ccf(enum ArithmeticTarget target);
const Instruction new_scf(enum ArithmeticTarget target);
const Instruction new_rra(enum ArithmeticTarget target);
const Instruction new_rla(enum ArithmeticTarget target);
const Instruction new_rrca(enum ArithmeticTarget target);
const Instruction new_rrla(enum ArithmeticTarget target);
const Instruction new_cpl(enum ArithmeticTarget target);
const Instruction new_bit(enum ArithmeticTarget target);
const Instruction new_reset(enum ArithmeticTarget target);
const Instruction new_set(enum ArithmeticTarget target);
const Instruction new_srl(enum ArithmeticTarget target);
const Instruction new_rr(enum ArithmeticTarget target);
const Instruction new_rl(enum ArithmeticTarget target);
const Instruction new_rrc(enum ArithmeticTarget target);
const Instruction new_rlc(enum ArithmeticTarget target);
const Instruction new_sra(enum ArithmeticTarget target);
const Instruction new_sla(enum ArithmeticTarget target);
const Instruction new_swap(enum ArithmeticTarget target);
