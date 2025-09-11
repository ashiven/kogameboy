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
  RLCA,  /*Bit rotate left register A not through carry flag*/
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

enum RegisterName { A, B, C, D, E, F, H, L, BC, DE, HL };

typedef struct {
  enum InstructionKind kind;
  enum RegisterName target;
  uint8_t bit_index;
} Instruction;

Instruction new_add(enum RegisterName target);
Instruction new_addhl(enum RegisterName target);
Instruction new_adc(enum RegisterName target);
Instruction new_sub(enum RegisterName target);
Instruction new_sbc(enum RegisterName target);
Instruction new_and(enum RegisterName target);
Instruction new_or(enum RegisterName target);
Instruction new_xor(enum RegisterName target);
Instruction new_cp(enum RegisterName target);
Instruction new_inc(enum RegisterName target);
Instruction new_dec(enum RegisterName target);
Instruction new_ccf();
Instruction new_scf();
Instruction new_rra();
Instruction new_rla();
Instruction new_rrca();
Instruction new_rlca();
Instruction new_cpl();
Instruction new_bit(uint8_t bit_index, enum RegisterName target);
Instruction new_reset(uint8_t bit_index, enum RegisterName target);
Instruction new_set(uint8_t bit_index, enum RegisterName target);
Instruction new_srl(enum RegisterName target);
Instruction new_rr(enum RegisterName target);
Instruction new_rl(enum RegisterName target);
Instruction new_rrc(enum RegisterName target);
Instruction new_rlc(enum RegisterName target);
Instruction new_sra(enum RegisterName target);
Instruction new_sla(enum RegisterName target);
Instruction new_swap(enum RegisterName target);
