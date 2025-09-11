#include "instructions.h"
#include <stdint.h>

const Instruction new_add(enum RegisterName target) {
  const Instruction add = {ADD, target};
  return add;
};

const Instruction new_addhl(enum RegisterName target) {
  const Instruction addhl = {ADDHL, target};
  return addhl;
};

const Instruction new_adc(enum RegisterName target) {
  const Instruction adc = {ADC, target};
  return adc;
};

const Instruction new_sub(enum RegisterName target) {
  const Instruction sub = {SUB, target};
  return sub;
};

const Instruction new_sbc(enum RegisterName target) {
  const Instruction sbc = {SBC, target};
  return sbc;
};

const Instruction new_and(enum RegisterName target) {
  const Instruction and = {AND, target};
  return and;
};

const Instruction new_or(enum RegisterName target) {
  const Instruction or = {OR, target};
  return or;
};

const Instruction new_xor(enum RegisterName target) {
  const Instruction xor = {XOR, target};
  return xor;
};

const Instruction new_cp(enum RegisterName target) {
  const Instruction cp = {CP, target};
  return cp;
};

const Instruction new_inc(enum RegisterName target) {
  const Instruction inc = {INC, target};
  return inc;
};

const Instruction new_dec(enum RegisterName target) {
  const Instruction dec = {DEC, target};
  return dec;
};

const Instruction new_ccf(enum RegisterName target) {
  const Instruction ccf = {CCF, target};
  return ccf;
};

const Instruction new_scf(enum RegisterName target) {
  const Instruction scf = {SCF, target};
  return scf;
};

const Instruction new_rra(enum RegisterName target) {
  const Instruction rra = {RRA, target};
  return rra;
};

const Instruction new_rla(enum RegisterName target) {
  const Instruction rla = {RLA, target};
  return rla;
};

const Instruction new_rrca(enum RegisterName target) {
  const Instruction rrca = {RRCA, target};
  return rrca;
};

const Instruction new_rrla(enum RegisterName target) {
  const Instruction rrla = {RLCA, target};
  return rrla;
};

const Instruction new_cpl(enum RegisterName target) {
  const Instruction cpl = {CPL, target};
  return cpl;
};

const Instruction new_bit(uint8_t bit_index, enum RegisterName target) {
  const Instruction bit = {BIT, target, bit_index};
  return bit;
};

const Instruction new_reset(uint8_t bit_index, enum RegisterName target) {
  const Instruction reset = {RESET, target, bit_index};
  return reset;
};

const Instruction new_set(uint8_t bit_index, enum RegisterName target) {
  const Instruction set = {SET, target, bit_index};
  return set;
};

const Instruction new_srl(enum RegisterName target) {
  const Instruction srl = {SRL, target};
  return srl;
};

const Instruction new_rr(enum RegisterName target) {
  const Instruction rr = {RR, target};
  return rr;
};

const Instruction new_rl(enum RegisterName target) {
  const Instruction rl = {RL, target};
  return rl;
};

const Instruction new_rrc(enum RegisterName target) {
  const Instruction rrc = {RRC, target};
  return rrc;
};

const Instruction new_rlc(enum RegisterName target) {
  const Instruction rlc = {RLC, target};
  return rlc;
};

const Instruction new_sra(enum RegisterName target) {
  const Instruction sra = {SRA, target};
  return sra;
};

const Instruction new_sla(enum RegisterName target) {
  const Instruction sla = {SLA, target};
  return sla;
};

const Instruction new_swap(enum RegisterName target) {
  const Instruction swap = {SWAP, target};
  return swap;
};
