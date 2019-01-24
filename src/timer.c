#include "timer.h"
#include "isr.h"

static const uint8_t IRQ_TIMER = 32;

uint32_t tick;

void timer_handler(registers_t* reg) {
    ++tick;
}

void init_timer() {
    tick = 0;
    register_int_handler(IRQ_TIMER, timer_handler);
}
