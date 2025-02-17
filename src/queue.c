#include "queue.h"

void init_queue(queue_t *q) {
	q->head = 0;
	q->tail = 0;
}

bool queue_isFull(queue_t *q) {
	return (q->tail == QUEUE_SIZE);
}

void queue_enqueue(queue_t *q, gate_ctx_t item) {
	if (!queue_isFull(q)) {
		q->items[q->tail] = item;
		q->tail++;
	}
}

void queue_dequeue(queue_t *q, gate_ctx_t *item) {
	if (q->head != q->tail) {
		*item = q->items[q->head];
		q->head++;
	} else {
		item = NULL;
	}
}
