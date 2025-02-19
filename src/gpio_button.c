#include "gpio_button.h"

#include "cpu.h"
#include "hal.h"
#include "plugbox.h"
#include <stdint.h>

static uint32_t button_count = 0;

void gpio_button_interrupt_init(void) {
  cpu_allocate_interrupt((uint8_t)PLUG_BUTTON, 1); // Allocate CPU for BUTTON
  REG(C3_INTERRUPT)[0xf8 / 4] |= BIT(16);          // Enable CPU IRQ
  REG(C3_GPIO)
  [0x74 / 4 + 9] |= (3U << 7) | BIT(13); // Enable intr, any edge
  REG(C3_INTERRUPT)
  [0x40 / 4] = (uint32_t)PLUG_BUTTON; // LAST: Map GPIO IRQ to CPU
  plugbox_assign(PLUG_BUTTON, &gpio_button_gate);
}

void gpio_button_interrupt_clear(void) { GPIO->STATUS &= ~BIT(9); }

bool gpio_button_interrupt_prologue(void) {
  return true;
}

void gpio_button_interrupt_epilogue(void) {
	button_count++;
	printf("Button pressed %lu times\n", button_count);
}

gate_ctx_t gpio_button_gate = {.prologue = gpio_button_interrupt_prologue,
                               .epilogue = gpio_button_interrupt_epilogue,
                               .clear = gpio_button_interrupt_clear,
                               .is_queued = false};
