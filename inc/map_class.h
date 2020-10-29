/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** create_server
*/

#ifndef __MAP_CLASS__
#define __MAP_CLASS__

#include "project_macro.h"

typedef struct item_s {
    string key;
    void *value;
} item_t;

typedef struct map_s {
    item_t *tab;
    item_t (*find_that)(struct map_s *this, string key);
    void *(*get_value)(struct map_s *this, string key);
} map_t;

map_t init_map(item_t *tab);

#endif //__MAP_CLASS__
