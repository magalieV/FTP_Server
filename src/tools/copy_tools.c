/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** create_server
*/

#include "server_project.h"
#include <string.h>

static string remove_useless_char(const string path)
{
    string str = malloc(sizeof(char) * (strlen(path) + 1));
    unsigned int index = 0;
    unsigned int idx = 0;

    if (path[0] == '.' and path[1] and path[1] != '.')
        index++;
    for (idx = 0; path[index]; idx++) {
        str[idx] = path[index];
        index++;
    }
    str[idx] = '\0';
    return (str);
}

string get_path_name(const string path, const string old_path,
    bool cdup)
{
    string str = NULL;
    string new_path = NULL;

    new_path = remove_useless_char(path);
    if (new_path[0] == '/')
        return (new_path);
    else if (strcmp(new_path, "..") == 0 and cdup)
        return (go_to_parent(old_path));
    if (strcmp(new_path, "..") == 0 and !cdup)
        return (new_path);
    str = malloc(sizeof(char) * (strlen(new_path) + strlen(old_path) + 2));
    if (!str)
        throw_error("Malloc error (get_path_name)", EXIT_FAIL);
    str[0] = '\0';
    str = strcat(str, old_path);
    if (old_path[strlen(old_path) - 1] != '/' and new_path[0] != '/')
        str = strcat(str, "/");
    str = strcat(str, new_path);
    free(new_path);
    return (str);
}