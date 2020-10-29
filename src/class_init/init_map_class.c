/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** create_server
*/

#include "map_class.h"
#include <string.h>

static item_t find_that(struct map_s *this, char *key)
{
    for (int index = 0; this->tab[index].key != NULL; index++) {
        if (strcmp(this->tab[index].key, key) == 0)
            return (this->tab[index]);
    }
    return ((item_t){.key = NULL, .value = NULL});
}

static void *get_value(struct map_s *this, char *key)
{
    for (int index = 0; this->tab[index].key != NULL; index++) {
        if (strcmp(this->tab[index].key, key) == 0)
            return (this->tab[index].value);
    }
    return (NULL);
}

map_t init_map(item_t *tab)
{
    map_t map;

    map.tab = tab;
    map.find_that = &find_that;
    map.get_value = &get_value;
    return map;
}
