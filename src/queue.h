#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "gate.h"

#define QUEUE_SIZE 100

typedef struct {
  gate_ctx_t *items[QUEUE_SIZE];
  uint32_t head;
  uint32_t tail;
  uint32_t size;
} queue_t;

extern void queue_init(queue_t *q);
extern bool queue_isFull(const queue_t *q);
extern bool queue_isEmpty(const queue_t *q);
extern bool queue_enqueue(queue_t *q, gate_ctx_t *item);
extern bool queue_dequeue(queue_t *q, gate_ctx_t **item);
