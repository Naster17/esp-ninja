#ifndef KERNEL_SERIAL_DRIVER_H
#define KERNEL_SERIAL_DRIVER_H

#include <stddef.h>
#include <stdint.h>

void serial_begin(int baud);

void serial_begin_ex(unsigned long baud, uint32_t config, int8_t rxPin, int8_t txPin, bool invert,
                     unsigned long timeout_ms, uint8_t rxfifo_full_thrhd);

void serial_print(const char *s);

void serial_printf(const char *format, ...);

#endif
