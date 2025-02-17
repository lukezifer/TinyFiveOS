#pragma once

#include <stdint.h>
#include "hal.h"

void cpu_enable_interrupts(void);
void cpu_disable_interrupts(void);
void cpu_die(void);
bool cpu_allocate_interrupt(uint8_t prio, uint8_t interrupt_num);
