#include "src/registers.h"
#include <stdio.h>

#define PRIu8 "%hhu"
#define PRIu16 "%hu"

int main() {

  Registers regs = new_regs();
  set_bc(&regs, 0x0100);
  uint16_t bc = get_bc(&regs);
  printf(PRIu16, bc);

  return 0;
}
