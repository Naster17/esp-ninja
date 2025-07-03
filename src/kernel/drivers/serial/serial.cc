#include <Arduino.h>

void serial_begin(int baud)
{
    Serial.begin(baud);
}

void serial_begin_ex(unsigned long baud, uint32_t config, int8_t rxPin, int8_t txPin, bool invert,
                     unsigned long timeout_ms, uint8_t rxfifo_full_thrhd)
{
    Serial.begin(baud, config, rxPin, txPin, invert, timeout_ms, rxfifo_full_thrhd);
}

void serial_print(const char *s)
{
    Serial.print(s);
}

void serial_printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int size = vsnprintf(nullptr, 0, format, args) + 1;
    char *buffer = (char *) malloc(size);
    vsnprintf(buffer, size, format, args);
    va_end(args);

    serial_print(buffer);
    free(buffer);
}
