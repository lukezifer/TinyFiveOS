#include "plugbox.h"

gate_ctx_t *gates[GATES_MAX_NUM];

void plugbox_init(void) {
  for (int i = 0; i < GATES_MAX_NUM; i++) {
    gates[i] = &panic_gate;
  }
}

void plugbox_assign(plugbox_vector_t vec_num, gate_ctx_t *gate) {
  if (vec_num < GATES_MAX_NUM) {
    gates[vec_num] = gate;
  }
}

gate_ctx_t *plugbox_report(plugbox_vector_t vec_num) {
  if (vec_num >= GATES_MAX_NUM) {
    vec_num = GATES_MAX_NUM - 1; // this will cause a panic
  }
  return gates[vec_num];
}
