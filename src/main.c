/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** create_server
*/

#include "../inc/socket_info.h"
#include "server_project.h"
#include <stdio.h>
#include <zconf.h>
#include <string.h>

void help(int ac, char *argv[])
{
    if (ac != 2 or !argv[1][0] or strcmp("--help", argv[1]) != 0)
        return;
    printf("USAGE: ./myftp port path\n");
    printf("\tport is the port number on which the server socket listens\n");
    printf("\tpath is the path to the home directory for the Anonymous"
        " user\n");
}

int main(int ac, char *argv[])
{
    socket_array_t socket_array;
    string buffer = malloc(sizeof(char) * (PATH_MAX + 1));

    help(ac, argv);
    if (ac < 2 or ac > 3 or !argv[1] or !argv[2])
        return (84);
    if (!(realpath(argv[2], buffer))) {
        fprintf(stderr, "%sError : not a real path%s\n",
            C_RED, C_RESET);
        return (84);
    }
    socket_array = create_server(argv[1]);
    socket_array.real_path = buffer;
    server_loop(&socket_array);
    return (0);
}