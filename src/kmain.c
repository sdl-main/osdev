#include "dt.h"
#include "fb.h"
#include "pic.h"
#include "timer.h"
#include "kbd.h"

void kmain() {
    init_descriptor_tables();
    fb_init();
    pic_init();
    init_timer();
    kbd_init();
    //fb_print("Hello World!\n");
    //fb_print("aba ");
    asm volatile("sti");
    for(;;) {
        asm("hlt");
    }
}
