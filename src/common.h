#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

void outb(uint16_t port, uint8_t data);
uint8_t inb(uint16_t port);

#endif /* COMMON_H */
