#include "cpu.h"
#include <stdint.h>

void cpu_enable_interrupts(void) { __asm__ __volatile__("csrsi mstatus, 0x8"); }

void cpu_disable_interrupts(void) {
  __asm__ __volatile__("csrci mstatus, 0x8");
}

void cpu_die() {
  cpu_disable_interrupts();
  __asm__ __volatile__("wfi");
  while (1);
}

bool cpu_allocate_interrupt(uint8_t int_num, uint8_t int_prio) {
  bool result = false;
  if (int_num <= 31 && int_prio <= 15 && int_prio != 0) {
    REG(C3_INTERRUPT)[0x104 / 4] |= BIT(int_num);          // CPU_INT_ENA
    REG(C3_INTERRUPT)[0x118 / 4 + int_num - 1] = int_prio; // CPU_INT_PRI_N
    // REG(C3_INTERRUPT)[0x108 / 4] |= BIT(no);  // Edge
    printf("Allocated CPU IRQ %d, prio %u\n", int_num, int_prio);
    result = true;
  }
  return result;
}
