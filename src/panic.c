#include "panic.h"
#include "gate.h"
#include "cpu.h"

gate_ctx_t panic_gate =
{
	.prologue = panic_prologue,
	.epilogue = panic_epilogue,
	.clear = panic_clear,
	.is_queued = false
};

void panic_epilogue(void)
{
 	//printf("Panic: panic_gate epilogue\n");
}

bool panic_prologue(void)
{
	//printf("Panic: panic_gate prologue\n");
	cpu_die();
	return false;
}

void panic_clear(void)
{
	//printf("Panic: panic_gate clear\n");
}
