#include "gate.h"


void gate_init(gate_ctx_t *ctx)
{
	ctx->is_queued = false;
	ctx->prologue = NULL;
	ctx->epilogue = NULL;
	ctx->clear = NULL;
}

void gate_set_dequeue(gate_ctx_t *ctx){
	//__sync_lock_release(&ctx->is_queued);
	//atomic_flag_clear(&(ctx->is_queued));
	ctx->is_queued = false;
	
}
bool gate_set_queued(gate_ctx_t *ctx){
	//return __sync_lock_test_and_set(&ctx->is_queued, 1) == 1;
	//return atomic_flag_test_and_set(&(ctx->is_queued));
	bool result = ctx->is_queued;
	ctx->is_queued = true;
	return result;
}
