#pragma once

#include "gate.h"

#include <stdint.h>

extern void system_timer_init(void);
extern void system_timer_interrupt_clear(void);
extern bool system_timer_interrupt_prologue(void);
extern void system_timer_interrupt_epilogue(void);

extern uint64_t systick(void);
extern uint64_t uptime_us(void);
extern void delay_us(unsigned long us);
extern void delay_ms(unsigned long ms);

extern gate_ctx_t system_timer_gate;
