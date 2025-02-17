#pragma once

#include <stdint.h>

#include "gate.h"
#include "panic.h"

#define GATES_MAX_NUM 32

extern gate_ctx_t *gates[GATES_MAX_NUM];

typedef enum {
  PLUG_SYSTEM_TIMER = 1,
  PLUG_BUTTON = 2,
  PLUG_PANIC = 31,
} plugbox_vector_t;

extern void plugbox_init(void);
extern void plugbox_assign(plugbox_vector_t vec_num, gate_ctx_t *gate);
extern gate_ctx_t *plugbox_report(plugbox_vector_t vec_num);
