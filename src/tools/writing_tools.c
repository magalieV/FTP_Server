/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** create_server
*/

#include "server_project.h"
#include "map_class.h"
#include "sentence_parser_value.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

static string copy_path(const string path, string new_path,
    unsigned int path_size, string tmp)
{
    unsigned int index = 0, idx = 0;

    for (index = 0; path[index]; index++) {
        if (path[index] == '/' and path[index + 1] != '\0') {
            tmp[idx] = '\0';
            new_path = strcat(new_path, tmp);
            free(tmp);
            idx = 0;
            tmp = malloc(sizeof(char) * (path_size));
            tmp[idx++] = '/';
        } else
            tmp[idx++] = path[index];
    }
    if (strlen(new_path) == 0 or strlen(new_path) == 1) {
        new_path[0] = '/';
        new_path[1] = '\0';
    }
    free(tmp);
    return (new_path);
}

string go_to_parent(const string path)
{
    string new_path = NULL;
    string tmp = NULL;
    unsigned int path_size = 0;

    if (!path)
        return (NULL);
    if ((path_size = strlen(path)) == 1)
        return ((string)path);
    new_path = malloc(sizeof(char) * (path_size));
    tmp = malloc(sizeof(char) * (path_size));
    if (!new_path or !tmp)
        throw_error("Malloc error", EXIT_FAIL);
    tmp[0] = '\0';
    new_path[0] = '\0';
    new_path = copy_path(path, new_path, path_size, tmp);
    return (new_path);
}

string replace_a_char(char to_replace, char new_char, string str)
{
    string new_str = NULL;

    if (!str)
        return (NULL);
    new_str = strdup(str);
    for (int index = 0; str[index]; index++) {
        if (str[index] == to_replace)
            new_str[index] = new_char;
    }
    return (new_str);
}

bool write_message(int fd, void *key)
{
    static int counter = 0;
    static map_t map_value;
    char *buffer = NULL;
    char *message = NULL;
    char *value = NULL;

    if (counter == 0) {
        counter++;
        map_value = init_map((item_t *)answer_value_map);
    }
    if (key == NULL)
        return (false);
    message = map_value.get_value(&map_value, key);
    value = (string)key;
    buffer = malloc(sizeof(char) * (strlen(value) + strlen(message) + 3));
    if (!buffer)
        throw_error("Malloc error", EXIT_FAIL);
    sprintf(buffer, "%s %s\n", value, message);
    write(fd, buffer, strlen(buffer));
    return (true);
}

unsigned int tab_len(const array arr)
{
    unsigned int counter = 0;

    if (!arr or !*arr)
        return (0);
    for (counter = 0; arr[counter]; counter++);
    return (counter);
}