#include "dt.h"

extern void gdt_flush(uint32_t);
extern void idt_flush(uint32_t);

void init_gdt();
void init_idt();

gdt_entry_t gdt[5];
gdt_ptr_t gdt_ptr;

idt_entry_t idt[256];
idt_ptr_t idt_ptr;

void init_descriptor_tables() {
    init_gdt();
    init_idt();
}


void init_gdt() {
    gdt_ptr.limit = sizeof (gdt_entry_t) * 5 - 1;
    gdt_ptr.base = (uint32_t)&gdt;

    // fill table
    gdt_set_entry(0, 0, 0, 0, 0); // null
    gdt_set_entry(1, 0, 0xffffffff, 0x9a, 0xcf); // kernel code
    gdt_set_entry(2, 0, 0xffffffff, 0x92, 0xcf); // kernel data
    gdt_set_entry(3, 0, 0xffffffff, 0xfa, 0xcf); // user code
    gdt_set_entry(4, 0, 0xffffffff, 0xf2, 0xcf); // used data
    
    gdt_flush((uint32_t)(&gdt_ptr)); // tell cpu where the gdt is
}


void gdt_set_entry(uint8_t n, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
    gdt[n].base_low = base & 0xffff;
    gdt[n].base_mid = (base >> 16) & 0xff;
    gdt[n].base_high = (base >> 24) & 0xffff;
    gdt[n].limit_low = limit & 0xffff;
    gdt[n].access = access;
    gdt[n].granularity = (granularity & 0xf0) | ((limit >> 16) & 0x0f);
}

void init_idt() {
    idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
    idt_ptr.base = (uint32_t)&idt;

    idt_set_entry(0, (uint32_t)isr0, 0x08, 0xEE);
    idt_set_entry(1, (uint32_t)isr1, 0x08, 0xEE);
    idt_set_entry(2,  (uint32_t)isr2, 0x08, 0xEE);
    idt_set_entry(3,  (uint32_t)isr3, 0x08, 0xEE);
    idt_set_entry(4,  (uint32_t)isr4, 0x08, 0xEE);
    idt_set_entry(5,  (uint32_t)isr5, 0x08, 0xEE);
    idt_set_entry(6,  (uint32_t)isr6, 0x08, 0xEE);
    idt_set_entry(7,  (uint32_t)isr7, 0x08, 0xEE);
    idt_set_entry(8,  (uint32_t)isr8, 0x08, 0xEE);
    idt_set_entry(9,  (uint32_t)isr9, 0x08, 0xEE);
    idt_set_entry(10, (uint32_t)isr10, 0x08, 0xEE);
    idt_set_entry(11, (uint32_t)isr11, 0x08, 0xEE);
    idt_set_entry(12, (uint32_t)isr12, 0x08, 0xEE);
    idt_set_entry(13, (uint32_t)isr13, 0x08, 0xEE);
    idt_set_entry(14, (uint32_t)isr14, 0x08, 0xEE);
    idt_set_entry(15, (uint32_t)isr15, 0x08, 0xEE);
    idt_set_entry(16, (uint32_t)isr16, 0x08, 0xEE);
    idt_set_entry(17, (uint32_t)isr17, 0x08, 0xEE);
    idt_set_entry(18, (uint32_t)isr18, 0x08, 0xEE);
    idt_set_entry(19, (uint32_t)isr19, 0x08, 0xEE);
    idt_set_entry(20, (uint32_t)isr20, 0x08, 0xEE);
    idt_set_entry(21, (uint32_t)isr21, 0x08, 0xEE);
    idt_set_entry(22, (uint32_t)isr22, 0x08, 0xEE);
    idt_set_entry(23, (uint32_t)isr23, 0x08, 0xEE);
    idt_set_entry(24, (uint32_t)isr24, 0x08, 0xEE);
    idt_set_entry(25, (uint32_t)isr25, 0x08, 0xEE);
    idt_set_entry(26, (uint32_t)isr26, 0x08, 0xEE);
    idt_set_entry(27, (uint32_t)isr27, 0x08, 0xEE);
    idt_set_entry(28, (uint32_t)isr28, 0x08, 0xEE);
    idt_set_entry(29, (uint32_t)isr29, 0x08, 0xEE);
    idt_set_entry(30, (uint32_t)isr30, 0x08, 0xEE);
    idt_set_entry(31, (uint32_t)isr31, 0x08, 0xEE);

    idt_set_entry(32, (uint32_t)irq0, 0x08, 0x8E);
    idt_set_entry(32, (uint32_t)irq0, 0x08, 0x8E);
    idt_set_entry(33, (uint32_t)irq1, 0x08, 0x8E);
    idt_set_entry(34, (uint32_t)irq2, 0x08, 0x8E);
    idt_set_entry(35, (uint32_t)irq3, 0x08, 0x8E);
    idt_set_entry(36, (uint32_t)irq4, 0x08, 0x8E);
    idt_set_entry(37, (uint32_t)irq5, 0x08, 0x8E);
    idt_set_entry(38, (uint32_t)irq6, 0x08, 0x8E);
    idt_set_entry(39, (uint32_t)irq7, 0x08, 0x8E);
    idt_set_entry(40, (uint32_t)irq8, 0x08, 0x8E);
    idt_set_entry(41, (uint32_t)irq9, 0x08, 0x8E);
    idt_set_entry(42, (uint32_t)irq10, 0x08, 0x8E);
    idt_set_entry(43, (uint32_t)irq11, 0x08, 0x8E);
    idt_set_entry(44, (uint32_t)irq12, 0x08, 0x8E);
    idt_set_entry(45, (uint32_t)irq13, 0x08, 0x8E);
    idt_set_entry(46, (uint32_t)irq14, 0x08, 0x8E);
    idt_set_entry(47, (uint32_t)irq15, 0x08, 0x8E);
    
    idt_flush((uint32_t)&idt_ptr);
}

void idt_set_entry(uint8_t n, uint32_t base, uint16_t selector, uint8_t flags) {
    idt[n].base_low = base & 0xffff;
    idt[n].base_high = (base >> 16) & 0xffff;
    idt[n].selector = selector;
    idt[n].flags = flags;
    idt[n].zero = 0;
}
