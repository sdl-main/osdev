#include "kbd.h"
#include "isr.h"
#include "pic.h"
#include "fb.h"

uint8_t key_map[2][128] =
{
    {
        0, KBD_CH_ESCAPE, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',  'q',
        'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0, 'a', 's', 'd',
        'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v', 'b',
        'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, KBD_CH_F1, KBD_CH_F2, KBD_CH_F3, KBD_CH_F4, KBD_CH_F5, KBD_CH_F6,
        KBD_CH_F7, KBD_CH_F8, KBD_CH_F9, KBD_CH_F10, 0, 0, KBD_CH_HOME, KBD_CH_UP, KBD_CH_PGUP, '-', KBD_CH_LEFT, '5', KBD_CH_RIGHT, '+', KBD_CH_END, KBD_CH_DOWN,
        KBD_CH_PGDN, KBD_CH_INSERT, KBD_CH_DELETE, 0, 0, 0, KBD_CH_F11, KBD_CH_F12, 0
	},
    {
        0,  KBD_CH_ESCAPE, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b', '\t',  'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
        0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '@', '`', 0, '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0, '*', 0, ' ', 0,
        KBD_CH_F1, KBD_CH_F2, KBD_CH_F3, KBD_CH_F4, KBD_CH_F5, KBD_CH_F6, KBD_CH_F7, KBD_CH_F8, 
        KBD_CH_F9, KBD_CH_F10, 0, 0, KBD_CH_HOME, KBD_CH_UP, KBD_CH_PGUP, '-', KBD_CH_LEFT, '5', KBD_CH_RIGHT, '+', KBD_CH_END,
        KBD_CH_DOWN, KBD_CH_PGDN, KBD_CH_INSERT, KBD_CH_DELETE, 0, 0, 0, KBD_CH_F11, KBD_CH_F12, 0
    },
};

void kbd_push(char c) {
    fb_put(c);
}

uint8_t kbd_status = 0;

void handler(registers_t* reg) {
    pic_send_eoi(reg->int_no-0x20);
    uint8_t scancode = kbd_read();
    //fb_println_hex(scancode);
    // is last bit is clear then key is pressed
    if (!(scancode & 0x80)) {
        switch (scancode) {
        case KBD_KEY_LSHIFT:
        case KBD_KEY_RSHIFT:
            kbd_status |= KBD_MASK_SHIFT;
            break;
        case KBD_KEY_LCTRL:
            kbd_status |= KBD_MASK_CTRL;
            break;
        case KBD_KEY_LALT:
            kbd_status |= KBD_MASK_ALT;
            break;
        default:
            if ((kbd_status & KBD_MASK_SHIFT) ||
                (kbd_status & KBD_MASK_CAPS) && !(kbd_status & KBD_MASK_SHIFT))
                kbd_push(key_map[1][scancode]);
            else
                kbd_push(key_map[0][scancode]);
        }
    }
    else {
        // clear last bit
        scancode ^= 0x80;
        switch (scancode) {
        case KBD_KEY_LSHIFT:
        case KBD_KEY_RSHIFT:
            kbd_status ^= KBD_MASK_SHIFT;
            break;
        case KBD_KEY_LCTRL:
            kbd_status ^= KBD_MASK_CTRL;
            break;
        case KBD_KEY_LALT:
            kbd_status ^= KBD_MASK_ALT;
            break;
        }
    }
    if (scancode != -1) {
        
    }
}

void kbd_init() {
    register_int_handler(IRQ1, handler);
}

uint8_t kbd_read() {
    uint16_t cnt = 50000;
    uint8_t status;
    while (--cnt) {
        status = inb(KBD_CMD_PORT);
        if (status & 0x01)
            break;
    }
    if (!cnt)
        return -1;
    return inb(KBD_DATA_PORT);
}

void kbd_send(uint8_t data) {
    int cnt = 50000;
    uint8_t status;
    while (--cnt) {
        status = inb(KBD_CMD_PORT);
        if (!(status & 0x02)) {
            outb(KBD_DATA_PORT, data);
            return;
        }
    }
}
