#include <assert.h>

#include "../include/cpu.h"

int main() {
    assert(1 != 2);
    CPU cpu = new_cpu();

    Instruction Iset = new_set(3, B);
    execute(&cpu, &Iset);
    assert(cpu.registers.b == 0b00001000);

    Instruction Isrl = new_srl(B);
    execute(&cpu, &Isrl);
    assert(cpu.registers.b == 0b00000100);

    Instruction Iadd = new_add(B);
    execute(&cpu, &Iadd);
    assert(cpu.registers.a == 0b00000100);

    Instruction Irra = new_rra();
    execute(&cpu, &Irra);
    assert(cpu.registers.a == 0b00000010);

    return 0;
}
