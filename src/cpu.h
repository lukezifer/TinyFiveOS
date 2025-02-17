#pragma once

#include <stdint.h>
#include "hal.h"

extern void cpu_enable_interrupts(void);
extern void cpu_disable_interrupts(void);
extern void cpu_die(void);
extern bool cpu_allocate_interrupt(uint8_t int_num, uint8_t int_prio);
