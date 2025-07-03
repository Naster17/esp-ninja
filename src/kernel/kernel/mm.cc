#include <Arduino.h>

#include <kernel/mm.h>

uint32_t free_mem = 0;

uint32_t mem_free_get_kb()
{
    return xPortGetFreeHeapSize() / 1024;
}

const char *mem_free_get_str()
{
    char *buf = (char *) malloc(16);
    sprintf(buf, "%dkb", (xPortGetFreeHeapSize() / 1024));
    return buf;
}
