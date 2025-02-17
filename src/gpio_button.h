#pragma once

#include "gate.h"

#include <stdbool.h>

extern void gpio_button_interrupt_init(void);
extern void gpio_button_interrupt_clear(void);
extern bool gpio_button_interrupt_prologue(void);
extern void gpio_button_interrupt_epilogue(void);

extern gate_ctx_t gpio_button_gate;
