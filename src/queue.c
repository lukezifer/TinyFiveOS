#include "queue.h"

void queue_init(queue_t *q) {
  q->head = 0;
  q->tail = 0;
  q->size = 0;
}

bool queue_isFull(const queue_t *q) { return q->size == QUEUE_SIZE; }

bool queue_isEmpty(const queue_t *q) { return q->size == 0; }

bool queue_enqueue(queue_t *q, gate_ctx_t *item) {
  if (queue_isFull(q)) {
    return false;
  }
  q->items[q->tail] = item;
  q->tail = (q->tail + 1) % QUEUE_SIZE;
  q->size++;
  return true;
}

bool queue_dequeue(queue_t *q, gate_ctx_t **item) {
  if (queue_isEmpty(q)) {
    return false;
  }
  *item = q->items[q->head];
  q->head = (q->head + 1) % QUEUE_SIZE;
  q->size--;
  return true;
}
