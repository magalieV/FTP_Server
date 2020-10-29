/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** create_server
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "socket_info.h"
#include "server_project.h"

static struct sockaddr_in create_socket_info_server(string info)
{
    struct sockaddr_in socket_info;

    bzero(&socket_info, sizeof(socket_info));
    socket_info.sin_family = AF_INET;
    if (atoi(info) < 0)
        throw_error("Server port must be positive", EXIT_FAIL);
    socket_info.sin_port = htons(atoi(info));
    socket_info.sin_addr.s_addr = htonl(INADDR_ANY);
    return (socket_info);
}

static void init_server(const int *socket_value,
    struct sockaddr_in *socket_info)
{
    int result = 0;

    result = bind(*socket_value, (struct sockaddr *)socket_info,
        sizeof(*socket_info));
    if (result < 0) {
        throw_error("Bind error", EXIT_FAIL);
    }
    result = listen(*socket_value, MAX_CLIENT);
    if (result == -1) {
        throw_error("Listen error", EXIT_FAIL);
    }
}

socket_array_t create_server(string info)
{
    socket_array_t socket_array = init_socket_array();
    int socket_value = socket(AF_INET, SOCK_STREAM, 0);
    int value = 1;
    struct sockaddr_in socket_info;

    printf("%s[SERVER FTP] %sStarting server.%s\n", C_YELLOW,
        C_BLUE, C_RESET);
    if (socket_value == -1) {
        throw_error("Error socket", EXIT_FAIL);
    }
    if (setsockopt(socket_value, SOL_SOCKET, SO_REUSEADDR, (char *)&value,
        sizeof(value)) < 0) {
        throw_error("Setsockopt error", EXIT_FAIL);
    }
    socket_info = create_socket_info_server(info);
    init_server(&socket_value, &socket_info);
    socket_array.add_server(&socket_array, 0, socket_value);
    return (socket_array);
}
