
#include "guardian.h"
#include "hal.h"
#include "watchdog_timer.h"

extern char _sbss, _ebss, _end, _eram;
static char *s_heap_start, *s_heap_end, *s_brk;

extern int main(void);

static void save_context(void);
static void restore_context(void);

//struct irq_data g_irq_data[32];

__attribute__((interrupt)) void irq_handler_0(void) {
  save_context();
  __asm__("li a0, 0      \n" // Put interrupt number on the stack as the first argument
          "call guardian \n" // Call guardian()
          "li a7, 93     \n" // Load the ecall number for exit (93) into a7
          "ecall");
  restore_context();
}

__attribute__((interrupt)) void irq_handler_1(void) {
  save_context();
  __asm__("li a0, 1      \n" // Put interrupt number on the stack as the first argument "call guardian \n" // Call guardian() "li a7, 93     \n" // Load the ecall number for exit (93) into a7
          "ecall");
  restore_context();
}

__attribute__((aligned(256))) void irqtab(void) {
  __asm__("j irq_handler_0 \n" // Jump to irq_handler()
          ".rept 31        \n" // 32 entries
          "j irq_handler_1 \n" // Jump to irq_handler()
          ".endr");
}

static void save_context() {
  __asm__("addi sp, sp, -124 \n"
          "sw x1, 120(sp)    \n"
          "sw x2, 116(sp)    \n"
          "sw x3, 112(sp)    \n"
          "sw x4, 108(sp)    \n"
          "sw x5, 104(sp)    \n"
          "sw x6, 100(sp)    \n"
          "sw x7, 96(sp)     \n"
          "sw x8, 92(sp)     \n"
          "sw x9, 88(sp)     \n"
          "sw x10, 84(sp)    \n"
          "sw x11, 80(sp)    \n"
          "sw x12, 76(sp)    \n"
          "sw x13, 72(sp)    \n"
          "sw x14, 68(sp)    \n"
          "sw x15, 64(sp)    \n"
          "sw x16, 60(sp)    \n"
          "sw x17, 56(sp)    \n"
          "sw x18, 52(sp)    \n"
          "sw x19, 48(sp)    \n"
          "sw x20, 44(sp)    \n"
          "sw x21, 40(sp)    \n"
          "sw x22, 36(sp)    \n"
          "sw x23, 32(sp)    \n"
          "sw x24, 28(sp)    \n"
          "sw x25, 24(sp)    \n"
          "sw x26, 20(sp)    \n"
          "sw x27, 16(sp)    \n"
          "sw x28, 12(sp)    \n"
          "sw x29, 8(sp)     \n"
          "sw x30, 4(sp)     \n"
          "sw x31, 0(sp)");
}

static void restore_context() {
  __asm__("lw x1, 120(sp) \n"
          "lw x2, 116(sp) \n"
          "lw x3, 112(sp) \n"
          "lw x4, 108(sp) \n"
          "lw x5, 104(sp) \n"
          "lw x6, 100(sp) \n"
          "lw x7, 96(sp)  \n"
          "lw x8, 92(sp)  \n"
          "lw x9, 88(sp)  \n"
          "lw x10, 84(sp) \n"
          "lw x11, 80(sp) \n"
          "lw x12, 76(sp) \n"
          "lw x13, 72(sp) \n"
          "lw x14, 68(sp) \n"
          "lw x15, 64(sp) \n"
          "lw x16, 60(sp) \n"
          "lw x17, 56(sp) \n"
          "lw x18, 52(sp) \n"
          "lw x19, 48(sp) \n"
          "lw x20, 44(sp) \n"
          "lw x21, 40(sp) \n"
          "lw x22, 36(sp) \n"
          "lw x23, 32(sp) \n"
          "lw x24, 28(sp) \n"
          "lw x25, 24(sp) \n"
          "lw x26, 20(sp) \n"
          "lw x27, 16(sp) \n"
          "lw x28, 12(sp) \n"
          "lw x29, 8(sp)  \n"
          "lw x30, 4(sp)  \n"
          "lw x31, 0(sp)  \n"
          "addi sp, sp, 124");
}


void kernel_init(void) {
	watchdog_timer_disable();
  main();
}

void Reset_Handler(void) {
  s_heap_start = s_brk = &_end, s_heap_end = &_eram;
  for (char *p = &_sbss; p < &_ebss;)
    *p++ = '\0';
  CSR_WRITE(mtvec, irqtab); // Route all interrupts to the irq_handler()
  kernel_init();
}
