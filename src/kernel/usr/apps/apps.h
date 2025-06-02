// System Apps Header
#ifndef USR_APPS_H
#define USR_APPS_H

#include <Arduino.h>

#define MAX_APPS 256

// Thank you Arduino not support __attribute__((constructor))
typedef struct Apps
{
    int count;
    struct list
    {
        int id;
        String app_name;
        String category;
        void (*entry)(void *lp_param);

    } list[MAX_APPS];

} Apps;

extern Apps *apps;

bool apps_system();
bool apps_user();

int app_add(String app_name, String category, void (*entry)(void *lp_param));

bool apps_init();
int apps_loaded();

#endif
