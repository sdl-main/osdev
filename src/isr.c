#include "isr.h"
#include "pic.h"
#include "fb.h"

isr_t int_handlers[256];

uint8_t bo = 0;

void isr_handler(registers_t* reg) {
    if (int_handlers[reg->int_no] != 0) { 
        isr_t handler = int_handlers[reg->int_no]; 
        handler(reg); 
    }
    else { 
        fb_print("Received interrupt: ");
        fb_print_hex(reg->int_no);
        fb_print(" (Error code: ");
        fb_print_hex(reg->err_code);
        fb_print(")\n");
    }
}

void register_int_handler(uint8_t num, isr_t handler) {
    int_handlers[num] = handler;
}


void irq_handler(registers_t* reg) {
    pic_send_eoi(reg->int_no - 0x20);
    if (int_handlers[reg->int_no] != 0) { 
        isr_t handler = int_handlers[reg->int_no]; 
        handler(reg); 
    }
    else { 
        fb_print("Received interrupt request: ");
        fb_print_hex(reg->int_no);
        fb_print(" (Error code: ");
        fb_print_hex(reg->err_code);
        fb_print(")\n");
    }
}
