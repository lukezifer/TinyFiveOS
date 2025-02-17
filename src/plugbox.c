#include "plugbox.h"

gate_ctx_t* gates[GATES_MAX_NUM];

void plugbox_init(void)
{
	for (int i = 0; i < GATES_MAX_NUM; i++)
{
		gates[i] = &panic_gate;
	}
}

void plugbox_assign(uint32_t interrupt_num, gate_ctx_t *gate)
{
	if(interrupt_num < GATES_MAX_NUM)
	{
		gates[interrupt_num] = gate;
	}
}

gate_ctx_t *plugbox_report(uint32_t interrupt_num)
{
	if (interrupt_num >= GATES_MAX_NUM)
	{
		interrupt_num = GATES_MAX_NUM - 1; // this will cause a panic
	}
		return gates[interrupt_num];
}
