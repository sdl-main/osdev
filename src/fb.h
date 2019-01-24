#ifndef FB_H
#define FB_H

#include "common.h"

#define FB_LOCATION 0xB8000
#define FB_WIDTH 80
#define FB_HEIGHT 25
#define FB_CMD_PORT 0x3d4
#define FB_DATA_PORT 0x3d5
#define FB_CMD_HIGH 14
#define FB_CMD_LOW 15

enum fb_color {
        FB_BLACK = 0,
	FB_BLUE = 1,
	FB_GREEN = 2,
	FB_CYAN = 3,
	FB_RED = 4,
	FB_MAGENTA = 5,
	FB_BROWN = 6,
	FB_LIGHT_GREY = 7,
	FB_DARK_GREY = 8,
	FB_LIGHT_BLUE = 9,
	FB_LIGHT_GREEN = 10,
	FB_LIGHT_CYAN = 11,
	FB_LIGHT_RED = 12,
	FB_LIGHT_MAGENTA = 13,
	FB_LIGHT_BROWN = 14,
	FB_WHITE = 15,
};
void fb_init();
void fb_set_color(uint8_t fg, uint8_t bg);
void fb_set_cursor(uint8_t xx, uint8_t yy);
void fb_put(uint8_t c);
void fb_put_at(uint8_t c, uint8_t x, uint8_t y);
void fb_put_at_c(uint8_t c, uint8_t color, uint8_t x, uint8_t y);
void fb_print(const char* s);
void fb_clear();
void fb_println();
void fb_print_hex(uint32_t n);
void fb_print_dec(uint32_t n);
void fb_println_hex(uint32_t n);
void fb_println_dec(uint32_t n);

#endif /* FB_H */
