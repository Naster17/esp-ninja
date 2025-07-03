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
    head->next = NULL;

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

    package_struct *tmp = pkgs;
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }

    tmp->next = head;
    return 0;
}

void pkg_print(package_struct *head)
{
    Serial.printf("ID: %d\n", head->id);
    Serial.printf("Name: %s\n", head->name);
    Serial.printf("Category: %s\n", head->category);
    int result = head->pkg_main(NULL);
    Serial.printf("Result: %d\n", result);
}

void pkg_debug()
{
    package_struct *tmp = pkgs;
    do
    {
        pkg_print(tmp);
        tmp = tmp->next;
    } while (tmp != NULL);
}
