#include "pic.h"
#include "dt.h"

void pic_init() {
    pic_remap(0x20, 0x28);
}

void pic_remap(uint8_t offset1, uint8_t offset2) {
    int mask1 = inb(PIC1_DATA);
    int mask2 = inb(PIC2_DATA);

    outb(PIC1_CMD, PIC_INIT);
    outb(PIC2_CMD, PIC_INIT);

    outb(PIC1_DATA, offset1);
    outb(PIC2_DATA, offset2);

    outb(PIC1_DATA, 0x4);
    outb(PIC2_DATA, 0x2);

    outb(PIC1_DATA, ICW4_8086);
    outb(PIC2_DATA, ICW4_8086);

    outb(PIC1_DATA, mask1);
    outb(PIC2_DATA, mask2);
}

void pic_set_mask(uint8_t irq) {
    uint16_t port = PIC1_DATA;
    if (irq >= 8) {
        port = PIC2_DATA;
        irq -= 8;
    }
    uint8_t mask = inb(port);
    outb(port, mask | (1 << irq));
}

void pic_clr_mask(uint8_t irq) {
    uint16_t port = PIC1_DATA;
    if (irq >= 8) {
        port = PIC2_DATA;
        irq -= 8;
    }
    uint8_t mask = inb(port);
    outb(port, mask & ~(1 << irq));
}

void pic_send_eoi(uint8_t irq) {
    if (irq >= 8) {
        outb(PIC2_CMD, PIC_EOI);
    }
    outb(PIC1_CMD, PIC_EOI);
}
