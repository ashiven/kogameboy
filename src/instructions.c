#include "../include/instructions.h"

#include <stdint.h>

Instruction new_add(enum RegisterName target) {
    Instruction add = {ADD, target, 0};
    return add;
}

Instruction new_addhl(enum RegisterName target) {
    Instruction addhl = {ADDHL, target, 0};
    return addhl;
}

Instruction new_adc(enum RegisterName target) {
    Instruction adc = {ADC, target, 0};
    return adc;
}

Instruction new_sub(enum RegisterName target) {
    Instruction sub = {SUB, target, 0};
    return sub;
}

Instruction new_sbc(enum RegisterName target) {
    Instruction sbc = {SBC, target, 0};
    return sbc;
}

Instruction new_and(enum RegisterName target) {
    Instruction and = {AND, target, 0};
    return and;
}

Instruction new_or(enum RegisterName target) {
    Instruction or_ = {OR, target, 0};
    return or_;
}

Instruction new_xor(enum RegisterName target) {
    Instruction xor = {XOR, target, 0};
    return xor;
}

Instruction new_cp(enum RegisterName target) {
    Instruction cp_ = {CP, target, 0};
    return cp_;
}

Instruction new_inc(enum RegisterName target) {
    Instruction inc = {INC, target, 0};
    return inc;
}

Instruction new_dec(enum RegisterName target) {
    Instruction dec = {DEC, target, 0};
    return dec;
}

Instruction new_ccf(void) {
    Instruction ccf = {CCF, 0, 0};
    return ccf;
}

Instruction new_scf(void) {
    Instruction scf = {SCF, 0, 0};
    return scf;
}

Instruction new_rra(void) {
    Instruction rra = {RRA, 0, 0};
    return rra;
}

Instruction new_rla(void) {
    Instruction rla = {RLA, 0, 0};
    return rla;
}

Instruction new_rrca(void) {
    Instruction rrca = {RRCA, 0, 0};
    return rrca;
}

Instruction new_rrla(void) {
    Instruction rrla = {RLCA, 0, 0};
    return rrla;
}

Instruction new_cpl(void) {
    Instruction cpl = {CPL, 0, 0};
    return cpl;
}

Instruction new_bit(uint8_t bit_index, enum RegisterName target) {
    Instruction bit = {BIT, target, bit_index};
    return bit;
}

Instruction new_reset(uint8_t bit_index, enum RegisterName target) {
    Instruction reset = {RESET, target, bit_index};
    return reset;
}

Instruction new_set(uint8_t bit_index, enum RegisterName target) {
    Instruction set = {SET, target, bit_index};
    return set;
}

Instruction new_srl(enum RegisterName target) {
    Instruction srl = {SRL, target, 0};
    return srl;
}

Instruction new_rr(enum RegisterName target) {
    Instruction rr_ = {RR, target, 0};
    return rr_;
}

Instruction new_rl(enum RegisterName target) {
    Instruction rl_ = {RL, target, 0};
    return rl_;
}

Instruction new_rrc(enum RegisterName target) {
    Instruction rrc = {RRC, target, 0};
    return rrc;
}

Instruction new_rlc(enum RegisterName target) {
    Instruction rlc = {RLC, target, 0};
    return rlc;
}

Instruction new_sra(enum RegisterName target) {
    Instruction sra = {SRA, target, 0};
    return sra;
}

Instruction new_sla(enum RegisterName target) {
    Instruction sla = {SLA, target, 0};
    return sla;
}

Instruction new_swap(enum RegisterName target) {
    Instruction swap = {SWAP, target, 0};
    return swap;
}
