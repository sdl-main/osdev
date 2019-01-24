#ifndef PIC_H
#define PIC_H

#include "common.h"

#define PIC1_CMD 0x20
#define PIC2_CMD 0xA0
#define PIC1_DATA 0x21
#define PIC2_DATA 0xA1
#define PIC_EOI 0x20
#define PIC_INIT 0x11
#define ICW4_8086 0x01

void pic_init();
void pic_remap(uint8_t offset1, uint8_t offset2);
void pic_set_mask(uint8_t irq);
void pic_clr_mask(uint8_t irq);
void pic_send_eoi(uint8_t irq);

#endif /* PIC_H */
