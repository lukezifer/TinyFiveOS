// SPDX-FileCopyrightText: 2022-2023 Cesanta Software Limited
// SPDX-License-Identifier: MIT

#include "hal.h"
#include "cpu.h"
#include "system_timer.h"
#include "guard.h"
#include "plugbox.h"
#include "gpio_button.h"

#define BLINK_PERIOD_MS 500  // LED blinking period in millis
#define LOG_PERIOD_MS 1000   // Info log period in millis

//void SystemInit(void) {  // Called automatically by startup code
//  clock_init();
//}
//
//static volatile uint64_t s_ticks;  // Milliseconds since boot
//void SysTick_Handler(void) {       // SyStick IRQ handler, triggered every 1ms
//  s_ticks++;
//}
//
static void log_task(void) {  // Print a log every LOG_PERIOD_MS
//static uint64_t timer = 0;
//if (timer_expired(&timer, LOG_PERIOD_MS, s_ticks)) {
//  printf("tick: %5lu, CPU %lu MHz\n", (unsigned long) s_ticks,
//         clock_sys_freq() / 1000000);
//}
}

//static void button_handler(void *param) {
//  uint16_t pin = (uint16_t) (uintptr_t) param;
//  printf("Button %u %s\n", pin, gpio_read(pin) ? "pressed" : "released");
//}

int main(void) {

  cpu_disable_interrupts();

  gpio_input(BUTTON_PIN);
  uart_init(UART_DEBUG, 115200);
	plugbox_init();
	system_timer_init();
	guard_init();
  cpu_enable_interrupts();
	printf("Hello, world! %u\n", 1);

//  gpio_set_irq_handler(BUTTON_PIN, button_handler, (void *) BUTTON_PIN);
	gpio_button_interrupt_init();
  
  for (;;) {
		guard_enter();
    log_task();
		guard_leave();
  }

  return 0;
}
