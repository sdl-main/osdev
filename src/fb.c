#include "fb.h"
#include "kbd.h"

uint8_t x, y; // cursor position
uint8_t color; // fg and bg colors
uint16_t* fb; // pointer to framebuffer

// clear screen, initialise cursor and framebuffer
void fb_init() {
    fb_set_color(FB_WHITE, FB_BLACK);
    x = y = 0;
    fb = (uint16_t*) FB_LOCATION;
    fb_clear();
    fb_set_cursor(0, 0);
}

// compose color byte from fg and bg bytes
uint8_t fb_make_color(uint8_t fg, uint8_t bg) {
    return fg | (bg << 4);
}

// set foreground and background color
void fb_set_color(uint8_t fg, uint8_t bg) {
    color = fb_make_color(fg, bg);
}

// move the carriage
void fb_set_cursor(uint8_t xx, uint8_t yy) {
    x = xx;
    y = yy;
    uint16_t loc = xx + yy * FB_WIDTH;
    
    // send higher byte of cursor location to framebuffer port
    outb(FB_CMD_PORT, FB_CMD_HIGH);
    outb(FB_DATA_PORT, loc >> 8);

    // send lower byte of cursor location to framebuffer port
    outb(FB_CMD_PORT, FB_CMD_LOW);
    outb(FB_DATA_PORT, loc);
}

// scroll screen when the last line is reached
void fb_scroll() {
    // move every line one row up
    for (size_t y = 0; y < FB_HEIGHT-1; ++y) {
        for (size_t x = 0; x < FB_WIDTH; ++x) {
            size_t index1 = x + y * FB_WIDTH;
            size_t index2 = x + (y + 1) * FB_WIDTH;
            fb[index1] = fb[index2];
        }
    }
    
    // fill last line with spaces
    for (size_t x = 0; x < FB_WIDTH; ++x) {
        fb_put_at(' ', x, FB_HEIGHT-1);
    }
}

// put a single char
void fb_put(uint8_t c) {
    if (c == '\n') {
        ++y;
        x = 0;
        if (y == FB_HEIGHT) {
            --y;
            fb_scroll();
        }
    }
    else if (c == '\b') {
        if (!(y == 0 && x == 0)) {
            if (x != 0) {
                --x;
            }
            else {
                x = FB_WIDTH-1;
                --y;
            }
            fb[x + FB_WIDTH * y] = ((uint16_t) color << 8) | (uint16_t) ' ';
        }
    }
    else if (c == KBD_CH_UP) {
        if (y != 0)
            --y;
    }
    else if (c == KBD_CH_DOWN) {
        if (y != FB_HEIGHT-1)
            ++y;
    }
    else if (c == KBD_CH_LEFT) {
        if (x != 0)
            --x;
    }
    else if (c == KBD_CH_RIGHT) {
        if (x != FB_WIDTH-1)
            ++x;
    }
    else {
        fb[x + FB_WIDTH * y] = ((uint16_t) color << 8) | (uint16_t) c;
        ++x;
        if (x == FB_WIDTH) {
            x = 0, ++y;
        }
        if (y == FB_HEIGHT) {
            --y;
            fb_scroll();
        }
    }
    fb_set_cursor(x, y);
}

uint16_t fb_encode(char c, uint8_t color) {
    return ((uint16_t) color << 8) | c;
}

uint16_t fb_encode_c(uint8_t c, uint8_t fg, uint8_t bg) {
    return ((uint16_t) fb_make_color(fg, bg) << 8) | c;
}

int strlen(const char* s) {
    int len = 0;
    while (s[len]) {
        len++;
    }
    return len;
}

// print string
void fb_print(const char* s) {
    int len = strlen(s);
    for (int i = 0; i < len; ++i) {
        fb_put(s[i]);
    }
}

// clear screen
void fb_clear() {
    fb_set_cursor(0, 0);
    fb_set_color(FB_WHITE, FB_BLACK);
    for (int x = 0; x < FB_WIDTH * FB_HEIGHT; ++x) {
        fb_put(' ');
    }
}

void fb_put_at_c(uint8_t c, uint8_t color, uint8_t x, uint8_t y) {
    int index = x + y * FB_WIDTH;
    fb[index] = fb_encode(c, color);
}

void fb_put_at(uint8_t c, uint8_t x, uint8_t y) {
    fb_put_at_c(c, color, x, y);
}

void fb_print_hex(uint32_t n) {
    fb_print("0x");
    size_t i = 8;
    char s[9];
    while (i--) {
        char c = (n & 15) + '0';
        if (c > '9') {
            c += 7;
        }
        s[i] = c;
        n >>= 4;
    }
    s[8] = 0;
    fb_print(s);
}

void fb_print_dec(uint32_t n) {
    if (n == 0) {
        fb_print("0");
        return;
    }
    size_t sz = 0;
    char s[11];
    while (n) {
        s[sz++] = n % 10 + '0';
        n /= 10;
    }
    for (size_t i = 0; i < sz / 2; ++i) {
        char x = s[i];
        s[i] = s[sz-i-1];
        s[sz-i-1] = x;
    }
    s[sz] = 0;
    fb_print(s);
}

void fb_println() {
    fb_put('\n');
}


void fb_println_hex(uint32_t n) {
    fb_print_hex(n);
    fb_println();
}
void fb_println_dec(uint32_t n) {
    fb_print_dec(n);
    fb_println();
}
