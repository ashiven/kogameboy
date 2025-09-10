#include "instructions.h"

const Instruction new_add(enum ArithmeticTarget target) {
  const Instruction add = {ADD, target};
  return add;
};

const Instruction new_addhl(enum ArithmeticTarget target) {
  const Instruction addhl = {ADDHL, target};
  return addhl;
};

const Instruction new_adc(enum ArithmeticTarget target) {
  const Instruction adc = {ADC, target};
  return adc;
};

const Instruction new_sub(enum ArithmeticTarget target) {
  const Instruction sub = {SUB, target};
  return sub;
};

const Instruction new_sbc(enum ArithmeticTarget target) {
  const Instruction sbc = {SBC, target};
  return sbc;
};

const Instruction new_and(enum ArithmeticTarget target) {
  const Instruction and = {AND, target};
  return and;
};

const Instruction new_or(enum ArithmeticTarget target) {
  const Instruction or = {OR, target};
  return or;
};

const Instruction new_xor(enum ArithmeticTarget target) {
  const Instruction xor = {XOR, target};
  return xor;
};

const Instruction new_cp(enum ArithmeticTarget target) {
  const Instruction cp = {CP, target};
  return cp;
};

const Instruction new_inc(enum ArithmeticTarget target) {
  const Instruction inc = {INC, target};
  return inc;
};

const Instruction new_dec(enum ArithmeticTarget target) {
  const Instruction dec = {DEC, target};
  return dec;
};

const Instruction new_ccf(enum ArithmeticTarget target) {
  const Instruction ccf = {CCF, target};
  return ccf;
};

const Instruction new_scf(enum ArithmeticTarget target) {
  const Instruction scf = {SCF, target};
  return scf;
};

const Instruction new_rra(enum ArithmeticTarget target) {
  const Instruction rra = {RRA, target};
  return rra;
};

const Instruction new_rla(enum ArithmeticTarget target) {
  const Instruction rla = {RLA, target};
  return rla;
};

const Instruction new_rrca(enum ArithmeticTarget target) {
  const Instruction rrca = {RRCA, target};
  return rrca;
};

const Instruction new_rrla(enum ArithmeticTarget target) {
  const Instruction rrla = {RRLA, target};
  return rrla;
};

const Instruction new_cpl(enum ArithmeticTarget target) {
  const Instruction cpl = {CPL, target};
  return cpl;
};

const Instruction new_bit(enum ArithmeticTarget target) {
  const Instruction bit = {BIT, target};
  return bit;
};

const Instruction new_reset(enum ArithmeticTarget target) {
  const Instruction reset = {RESET, target};
  return reset;
};

const Instruction new_set(enum ArithmeticTarget target) {
  const Instruction set = {SET, target};
  return set;
};

const Instruction new_srl(enum ArithmeticTarget target) {
  const Instruction srl = {SRL, target};
  return srl;
};

const Instruction new_rr(enum ArithmeticTarget target) {
  const Instruction rr = {RR, target};
  return rr;
};

const Instruction new_rl(enum ArithmeticTarget target) {
  const Instruction rl = {RL, target};
  return rl;
};

const Instruction new_rrc(enum ArithmeticTarget target) {
  const Instruction rrc = {RRC, target};
  return rrc;
};

const Instruction new_rlc(enum ArithmeticTarget target) {
  const Instruction rlc = {RLC, target};
  return rlc;
};

const Instruction new_sra(enum ArithmeticTarget target) {
  const Instruction sra = {SRA, target};
  return sra;
};

const Instruction new_sla(enum ArithmeticTarget target) {
  const Instruction sla = {SLA, target};
  return sla;
};

const Instruction new_swap(enum ArithmeticTarget target) {
  const Instruction swap = {SWAP, target};
  return swap;
};
