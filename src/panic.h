#pragma once

#include "gate.h"

void panic_epilogue(void);
bool panic_prologue(void);
void panic_clear(void);

extern gate_ctx_t panic_gate;
