#include "system_timer.h"

#include "hal.h"
#include "cpu.h"

typedef struct {  // 10.6 (complete)
	volatile uint32_t CONF;
	volatile uint32_t UNIT0_OP;
	volatile uint32_t UNIT1_OP;
	volatile uint32_t UNIT0_LOAD_HI;
	volatile uint32_t UNIT0_LOAD_LO;
	volatile uint32_t UNIT1_LOAD_HI;
	volatile uint32_t UNIT1_LOAD_LO;
	volatile uint32_t TARGET0_HI;
	volatile uint32_t TARGET0_LO;
	volatile uint32_t TARGET1_HI;
	volatile uint32_t TARGET1_LO;
	volatile uint32_t TARGET2_HI;
	volatile uint32_t TARGET2_LO;
	volatile uint32_t TARGET0_CONF;
	volatile uint32_t TARGET1_CONF;
	volatile uint32_t TARGET2_CONF;
	volatile uint32_t UNIT0_VALUE_HI;
	volatile uint32_t UNIT0_VALUE_LO;
	volatile uint32_t UNIT1_VALUE_HI;
	volatile uint32_t UNIT1_VALUE_LO;
	volatile uint32_t COMP0_LOAD;
	volatile uint32_t COMP1_LOAD;
	volatile uint32_t COMP2_LOAD;
	volatile uint32_t UNIT0_LOAD;
	volatile uint32_t UNIT1_LOAD;
	volatile uint32_t INT_ENA;
	volatile uint32_t INT_RAW;
	volatile uint32_t INT_CLR;
	volatile uint32_t INT_ST;
	volatile uint32_t RESERVED0[34];
	volatile uint32_t DATE;
} systimer_t;

#define SYSTIMER ((systimer_t *) C3_SYSTIMER)

gate_ctx_t system_timer_gate =
{
	.prologue = system_timer_interrupt_prologue,
	.epilogue = system_timer_interrupt_epilogue,
	.clear = system_timer_interrupt_clear,
	.is_queued = false
};

void system_timer_init(void)
{
  SYSTIMER->TARGET0_CONF = BIT(30) | 16000;  // Set period
  SYSTIMER->COMP0_LOAD = BIT(0);             // Reload period
  SYSTIMER->CONF |= BIT(24);                 // Enable comparator 0
  SYSTIMER->INT_ENA |= 7U;                   // Enable interrupts on all targets

  cpu_allocate_interrupt(1, 1);
  REG(C3_INTERRUPT)[0xfc / 4] |= BIT(5) | BIT(6) | BIT(7);  // Enable CPU IRQ
  //REG(C3_INTERRUPT)[0xfc / 4] |= BIT(5);                    // Enable CPU IRQ
  REG(C3_INTERRUPT)[0x94 / 4] = 1;  // LAST: Map systimer IRQ to CPU
}

void system_timer_interrupt_clear(void)
{
	SYSTIMER->INT_CLR = 7U; // Clear all 3 units
}

bool system_timer_interrupt_prologue(void)
{
	return false;
}

void system_timer_interrupt_epilogue(void)
{
}

uint64_t systick(void)
{
	SYSTIMER->UNIT0_OP = BIT(30); // TRM 10.5
	spin(1);
	return ((uint64_t) SYSTIMER->UNIT0_VALUE_HI << 32) | SYSTIMER->UNIT0_VALUE_LO;
}

uint64_t uptime_us(void) {
  return systick() >> 4;
}

void delay_us(unsigned long us) {
  uint64_t until = uptime_us() + us;
  while (uptime_us() < until) spin(1);
}

void delay_ms(unsigned long ms) {
  delay_us(ms * 1000);
}
