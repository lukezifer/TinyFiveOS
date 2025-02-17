
#include "guardian.h"
#include "hal.h"
#include "watchdog_timer.h"
#include <stdint.h>

extern char _sbss, _ebss, _end, _eram;
static char *s_heap_start, *s_heap_end, *s_brk;

extern int main(void);

__attribute__((interrupt)) void irq_handler(void)
{
	uint32_t mcause = CSR_READ(mcause);
	uint32_t mepc = CSR_READ(mepc);
	if((mcause & BIT(31))) {
		uint32_t no = mcause << 1 >> 1;
		guardian(no);
	} else {
		CSR_WRITE(mepc, mepc + 4);
	}
}

__attribute__((aligned(256))) void irq_table(void) {
  __asm__(".rept 32      \n" // 32 entries
          "j irq_handler \n" // Jump to irq_handler()
          ".endr");
}

void kernel_init(void) {
	watchdog_timer_disable();
  main();
}

void Reset_Handler(void) {
  s_heap_start = s_brk = &_end, s_heap_end = &_eram;
  for (char *p = &_sbss; p < &_ebss;)
    *p++ = '\0';
  CSR_WRITE(mtvec, irq_table); // Route all interrupts to the irq_handler()
  kernel_init();
}
