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

package_struct *pkg_create(const char *name, const char *category, int (*pkg_main)(void *params));

int pkg_add(const char *name, const char *category, int (*pkg_main)(void *params));

void pkg_print(package_struct *head);
void pkg_debug();
#endif
