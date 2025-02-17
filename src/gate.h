#pragma once

#include <stdatomic.h>
#include <stdbool.h>
#include <stddef.h>

typedef bool (*prologue_t)(void);
typedef void (*epilogue_t)(void);
typedef void (*clear_t)(void);

typedef struct gate_ctx {
  prologue_t prologue;
  epilogue_t epilogue;
  clear_t clear;
  volatile bool is_queued;
} gate_ctx_t;

extern void gate_init(gate_ctx_t *ctx);
extern void gate_set_dequeue(gate_ctx_t *ctx);
extern bool gate_set_queued(gate_ctx_t *ctx);
