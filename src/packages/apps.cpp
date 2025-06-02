#include <kernel/package.h>

Apps *apps = (Apps *) malloc(sizeof(Apps));

bool apps_init()
{
    memset((void *) apps, 0, sizeof(Apps));
    return true;
}

int apps_loaded()
{
    return apps->count;
}

int app_add(String app_name, String category, void (*entry)(void *lp_param))
{
    for (int i = 0; i < apps->count + 1; i++)
    {
        if (apps->list[i].app_name == app_name)
            return 1;
    }

    apps->count += 1;
    apps->list[apps->count].id = apps->count;
    apps->list[apps->count].app_name = app_name;
    apps->list[apps->count].category = category;
    apps->list[apps->count].entry = entry;

    return 0;
}
