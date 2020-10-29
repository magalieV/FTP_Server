/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** create_server
*/

#include <stdio.h>
#include <stdlib.h>
#include "server_project.h"

static void is_same_part(char first, char second, unsigned int *counter,
    bool *delimiter_before)
{
    if (first != second) {
        *delimiter_before = false;
        return;
    }
    if (!*delimiter_before) {
        *counter += 1;
    }
    *delimiter_before = true;
}

static bool is_delimiter(char c, const string delimiter)
{
    if (c == '\0')
        return (true);
    for (unsigned int index = 0; delimiter[index]; index++) {
        if (delimiter[index] == c)
            return (true);
    }
    return (false);
}

static unsigned int found_part_number(const string str, const string delimiter)
{
    unsigned int counter = 0;
    bool delimiter_before = true;

    if (!str or !delimiter)
        return (0);
    for (unsigned int index = 0; str[index]; index++) {
        for (unsigned int idx = 0; delimiter[idx]; idx++) {
            is_same_part(str[index], delimiter[idx], &counter,
                &delimiter_before);
        }
    }
    return (counter);
}

static string copy_char(const string str, unsigned int *index,
    unsigned int size, const string delimiter)
{
    string new_str = NULL;

    new_str = malloc(sizeof(char) * (size + 1));
    if (!new_str)
        throw_error("Malloc error on split", EXIT_FAIL);
    for (size = *index; str[size]; size++) {
        if (is_delimiter(str[size], delimiter))
            break;
        new_str[size - *index] = str[size];
    }
    new_str[size - *index] = '\0';
    *index = size;
    return (new_str);
}

array split(string str, string delimiter)
{
    array new_array = NULL;
    unsigned int size = 0, depth = 0;
    unsigned int size_array = found_part_number(str, delimiter);

    if (size_array == 0 or is_delimiter(str[0], delimiter))
        return (NULL);
    new_array = malloc(sizeof(char *) * (size_array + 1));
    if (!new_array)
        throw_error("Malloc error on split", EXIT_FAIL);
    for (unsigned int index = 0; str[index]; index++) {
        while (str[index] and is_delimiter(str[index], delimiter))
            index++;
        for (size = 0; !is_delimiter(str[index + size], delimiter); size++);
        if (size == 0 or str[index + size] == '\0')
            break;
        new_array[depth] = copy_char(str, &index, size, delimiter);
        depth++;
        new_array[depth] = NULL;
    }
    return (new_array);
}