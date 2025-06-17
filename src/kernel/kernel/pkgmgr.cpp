#include <Arduino.h>
#include <kernel/packages.h>

package_struct *pkgs = NULL;
static uint32_t id_counter = 0;

package_struct *pkg_create(const char *name, const char *category, int (*pkg_main)(void *params))
{
    // Some C++ mazafacking
    package_struct *head = (package_struct *) malloc(sizeof(package_struct));
    head->id = id_counter;
    head->name = strdup(name); // (char *) malloc(strlen(name) + 1);
    head->category = strdup(category);
    head->pkg_main = pkg_main;
    id_counter += 1;
    return head;
}

int pkg_add(const char *name, const char *category, int (*pkg_main)(void *params))
{
    if (name == NULL || category == NULL || pkg_main == NULL)
    {
        return 1;
    }
    package_struct *head = pkg_create(name, category, pkg_main);
    if (pkgs == NULL)
    {
        pkgs = head;
        return 0;
    }

    package_struct *tmp = head;
    do
    {
        tmp = tmp->next;
    } while (tmp != NULL);

    tmp->next = head;

    return 0;
}

bool pkg_init() {}
