// SPDX-FileCopyrightText: 2022-2023 Cesanta Software Limited
// SPDX-License-Identifier: MIT

#include "cpu.h"
#include "gpio_button.h"
#include "guard.h"
#include "hal.h"
#include "plugbox.h"
#include "system_timer.h"

#define BLINK_PERIOD_MS 500 // LED blinking period in millis
#define LOG_PERIOD_MS 1000  // Info log period in millis

static void log_task(void) { // dummy task
  uint32_t count = 0;
  while (count < 500000) {
    count++;
  }
}

int main(void) {

  cpu_disable_interrupts();

  gpio_input(BUTTON_PIN);
  uart_init(UART_DEBUG, 115200);
  plugbox_init();
  system_timer_init();
  guard_init();
  cpu_enable_interrupts();

  //  gpio_set_irq_handler(BUTTON_PIN, button_handler, (void *) BUTTON_PIN);
  gpio_button_interrupt_init();

  for (;;) {
    guard_enter();
    log_task();
    guard_leave();
  }

  return 0;
}
