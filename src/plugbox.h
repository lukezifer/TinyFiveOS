#pragma once

#include <stdint.h>

#include "gate.h"
#include "panic.h"

#define GATES_MAX_NUM 32

extern gate_ctx_t* gates[GATES_MAX_NUM];

void plugbox_init(void);
void plugbox_assign(uint32_t interrupt_num, gate_ctx_t *gate);
gate_ctx_t *plugbox_report(uint32_t interrupt_num);
