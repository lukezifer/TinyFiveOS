#include "guard.h"

#include "cpu.h"
#include "gate.h"
#include "queue.h"

static queue_t epilogue_queue;
static volatile bool epilogue_is_locked = false;



void guard_init(void)
{
	epilogue_is_locked = false;
	init_queue(&epilogue_queue);
}

void guard_enter(void)
{
	cpu_disable_interrupts();
	if(epilogue_is_locked)
	{
		//printf("Guard: nested enter\n");
		cpu_die();
	}
	epilogue_is_locked = true;
	cpu_enable_interrupts();
}

void guard_leave(void)
{
	gate_ctx_t *item_ctx = NULL;
	while(1)
	{
		cpu_disable_interrupts();
		queue_dequeue(&epilogue_queue, item_ctx);
		if(item_ctx == NULL)
		{
			gate_set_dequeue(item_ctx);
			cpu_enable_interrupts();
			item_ctx->epilogue();
		} else {
			if(epilogue_is_locked == false)
			{
				//printf("Guard: nested leave\n");
				cpu_die();
			}
			epilogue_is_locked = false;
			cpu_enable_interrupts();
			break;
		}
	}
}

void guard_relay(gate_ctx_t *item_ctx)
{
	if(gate_set_queued(item_ctx))
	{
		//printf("Guard: already queued\n");
		return;
	}
	else
	{
		queue_enqueue(&epilogue_queue, *item_ctx);
		if(epilogue_is_locked == false)
		{
			epilogue_is_locked = true;
			cpu_enable_interrupts();
			guard_leave();
		}
	}
}
