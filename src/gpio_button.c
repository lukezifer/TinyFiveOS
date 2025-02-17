#include "gpio_button.h"

#include "hal.h"
#include "cpu.h"

void gpio_button_interrupt_init(void) {
	cpu_allocate_interrupt(2, 1);                      // Allocate CPU IRQ 9
  REG(C3_INTERRUPT)[0xf8 / 4] |= BIT(16);             // Enable CPU IRQ
  REG(C3_GPIO) [0x74 / 4 + 9] |= (3U << 7) | BIT(13); // Enable intr, any edge
  REG(C3_INTERRUPT)[0x40 / 4] = (uint32_t) 9;         // LAST: Map GPIO IRQ to CPU
}

void gpio_button_interrupt_clear(void) {
  GPIO->STATUS &= ~BIT(9);
}

bool gpio_button_interrupt_prologue(void) {
	return true;
}

void gpio_button_interrupt_epilogue(void) {
//  printf("Button %u %s\n", pin, gpio_read(pin) ? "pressed" : "released");
}
