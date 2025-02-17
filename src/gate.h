#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdatomic.h>

typedef bool (*prologue_t)(void);
typedef void (*epilogue_t)(void);
typedef void (*clear_t)(void);

typedef struct gate_ctx {
	prologue_t prologue;
	epilogue_t epilogue;
	clear_t clear;
	volatile bool is_queued;
} gate_ctx_t;

void gate_init(gate_ctx_t *ctx);

void gate_set_dequeue(gate_ctx_t *ctx);

bool gate_set_queued(gate_ctx_t *ctx);
