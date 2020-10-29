/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** create_server
*/

#include <stdio.h>
#include <stdlib.h>
#include "project_macro.h"

void throw_error(const string message, int error_value)
{
    fprintf(stderr, "%s%s%s\n", message, C_RED, C_RESET);
    exit(error_value);
}