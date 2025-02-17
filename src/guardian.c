#include "guardian.h"

#include "guard.h"
#include "plugbox.h"

void guardian(uint32_t interrupt_num) {
  gate_ctx_t *gate = plugbox_report(interrupt_num);
  bool wants = gate->prologue();
  gate->clear();
  if (wants) {
    guard_relay(gate);
  }
}
