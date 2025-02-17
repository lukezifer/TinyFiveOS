#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "gate.h"

#define QUEUE_SIZE 100

typedef struct {
	gate_ctx_t items[QUEUE_SIZE];
	uint32_t head;
	uint32_t tail;
}queue_t;

void init_queue(queue_t *q);

bool queue_isFull(queue_t *q);

void queue_enqueue(queue_t *q, gate_ctx_t item);

void queue_dequeue(queue_t *q, gate_ctx_t *item);
