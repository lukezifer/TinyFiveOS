#pragma once

#include "gate.h"

extern void guard_init(void);
extern void guard_enter(void);
extern void guard_leave(void);
extern void guard_relay(gate_ctx_t *item_ctx);
