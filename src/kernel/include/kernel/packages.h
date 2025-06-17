// System Apps Header
#ifndef USR_APPS_H
#define USR_APPS_H

#include <Arduino.h>

typedef struct package_struct
{
    int id;
    char *name;
    char *category;
    int (*pkg_main)(void *params);
    package_struct *next;
} package_struct;

bool pkg_init();
int pkg_add();

#endif
