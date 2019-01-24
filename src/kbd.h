#ifndef KBD_H
#define KBD_H

#include "common.h"

#define KBD_CMD_PORT 0x64
#define KBD_DATA_PORT 0x60

#define KBD_KEY_A 0x1E
#define KBD_KEY_B 0x30
#define KBD_KEY_C 0x2E
#define KBD_KEY_D 0x20
#define KBD_KEY_E 0x12
#define KBD_KEY_F 0x21
#define KBD_KEY_G 0x22
#define KBD_KEY_H 0x23
#define KBD_KEY_I 0x17
#define KBD_KEY_J 0x24
#define KBD_KEY_K 0x25
#define KBD_KEY_L 0x26
#define KBD_KEY_M 0x32
#define KBD_KEY_N 0x31
#define KBD_KEY_O 0x18
#define KBD_KEY_P 0x19
#define KBD_KEY_Q 0x10
#define KBD_KEY_R 0x13
#define KBD_KEY_S 0x1F
#define KBD_KEY_T 0x14
#define KBD_KEY_U 0x16
#define KBD_KEY_V 0x2F
#define KBD_KEY_W 0x11
#define KBD_KEY_X 0x2D
#define KBD_KEY_Y 0x15
#define KBD_KEY_Z 0x2C

#define KBD_KEY_0 0x0B
#define KBD_KEY_1 0x02
#define KBD_KEY_2 0x03
#define KBD_KEY_3 0x04
#define KBD_KEY_4 0x05
#define KBD_KEY_5 0x06
#define KBD_KEY_6 0x07
#define KBD_KEY_7 0x08
#define KBD_KEY_8 0x09
#define KBD_KEY_9 0x0A

#define KBD_KEY_GRAVIS 0x29
#define KBD_KEY_MINUS 0x0C
#define KBD_KEY_EQUAL 0x0D
#define KBD_KEY_BACKSLASH 0x2B
#define KBD_KEY_BACKSPACE 0x0E
#define KBD_KEY_SPACE 0x39
#define KBD_KEY_TAB 0x0F
#define KBD_KEY_CAPS 0x3A
#define KBD_KEY_LSHIFT 0x2A
#define KBD_KEY_LCTRL 0x1D
#define KBD_KEY_LALT 0x38
#define KBD_KEY_RSHIFT 0x36
#define KBD_KEY_ENTER 0x1C
#define KBD_KEY_ESC 0x01

#define KBD_KEY_F1 0x3B
#define KBD_KEY_F2 0x3C
#define KBD_KEY_F3 0x3D
#define KBD_KEY_F4 0x3E
#define KBD_KEY_F5 0x3F
#define KBD_KEY_F6 0x40
#define KBD_KEY_F7 0x41
#define KBD_KEY_F8 0x42
#define KBD_KEY_F9 0x43
#define KBD_KEY_F10 0x44
#define KBD_KEY_F11 0x57
#define KBD_KEY_F12 0x58

#define KBD_KEY_LBRACE 0x1A
#define KBD_KEY_RBRACE 0x1B
#define KBD_KEY_NUM 0x45
#define KBD_KEY_SEMICOLON 0x27
#define KBD_KEY_APOSTROPHE 0x28
#define KBD_KEY_COMMA 0x33
#define KBD_KEY_DOT 0x34
#define KBD_KEY_SLASH 0x35

#define KBD_MASK_SHIFT 0x01
#define KBD_MASK_CAPS 0x02
#define KBD_MASK_CTRL 0x04
#define KBD_MASK_ALT 0x08

#define KBD_CH_ESCAPE 0x1B
#define KBD_CH_F1 0x80
#define KBD_CH_F2 0x81
#define KBD_CH_F3 0x82
#define KBD_CH_F4 0x83
#define KBD_CH_F5 0x84
#define KBD_CH_F6 0x85
#define KBD_CH_F7 0x86
#define KBD_CH_F8 0x87
#define KBD_CH_F9 0x88
#define KBD_CH_F10 0x89
#define KBD_CH_F11 0x8A
#define KBD_CH_F12 0x8B

#define KBD_CH_HOME 0x8C
#define KBD_CH_END 0x8D
#define KBD_CH_UP 0x8E
#define KBD_CH_LEFT 0x8F
#define KBD_CH_RIGHT 0x90
#define KBD_CH_DOWN 0x91
#define KBD_CH_PGUP 0x92
#define KBD_CH_PGDN 0x93
#define KBD_CH_INSERT 0x94
#define KBD_CH_DELETE 0x95
#define KBD_CH_F1 0x96




void kbd_init();
void kbd_send(uint8_t data);
uint8_t kbd_read();


#endif /* KBD_H */
