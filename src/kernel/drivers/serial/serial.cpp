#include <Arduino.h>

void serial_begin(int baud)
{
    Serial.begin(baud);
}

void serial_println(const char *s)
{
    Serial.println(s);
}

