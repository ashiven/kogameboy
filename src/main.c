#include <stdio.h>

#include "../include/cpu.h"

#define PRIu8 "%hhu"
#define PRIu16 "%hu"

// Source:
// https://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format
#define PRIbin "%c%c%c%c_%c%c%c%c"
#define BYTE_TO_BIN(byte)                                                                      \
    ((byte) & 0x80 ? '1' : '0'), ((byte) & 0x40 ? '1' : '0'), ((byte) & 0x20 ? '1' : '0'),     \
        ((byte) & 0x10 ? '1' : '0'), ((byte) & 0x08 ? '1' : '0'), ((byte) & 0x04 ? '1' : '0'), \
        ((byte) & 0x02 ? '1' : '0'), ((byte) & 0x01 ? '1' : '0')

int main(void) {
    CPU cpu = new_cpu();

    printf("%s: " PRIbin "\n", reg_name(A), BYTE_TO_BIN(cpu.registers.a));

    // print_reg(cpu, A);
    // print_regs(&cpu);

    return 0;
}
