/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** create_server
*/

#include "socket_info.h"
#include "server_project.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<time.h>
#include <arpa/inet.h>

static size_t go_to_passive_mode(socket_array_t *so_inf, unsigned int index)
{
    size_t port = 1024;

    srand(time(0));
    so_inf->socket_array[index].s_transmission_mode = PASSIVE;
    so_inf->socket_array[index].s_passive.fd = socket(AF_INET, SOCK_STREAM, 0);
    so_inf->socket_array[index].s_passive.s_addr.sin_family = AF_INET;
    so_inf->socket_array[index].s_passive.s_addr.sin_port = htons(port);
    so_inf->socket_array[index].s_passive.s_addr.sin_addr.s_addr =
        so_inf->socket_array[index].s_addr.sin_addr.s_addr;
    while (bind(so_inf->socket_array[index].s_passive.fd,
        (const struct sockaddr *)&so_inf->socket_array[index].s_passive.s_addr,
        sizeof(so_inf->socket_array[index].s_passive.s_addr)) < 0) {
        port = rand() % (65635 - 1024) + 1024;
        so_inf->socket_array[index].s_passive.s_addr.sin_port = htons(port);
    }
    if (listen(so_inf->socket_array[index].s_passive.fd, 100) < 0)
        throw_error("Listen error", EXIT_FAIL);
    return (port);
}

static void go_to_active_mode(socket_array_t *so_inf, unsigned int index,
    const string cmd, int socket_value)
{
    array ip = malloc(sizeof(char *) * 7);
    string buffer = NULL;
    string tmp = strdup(cmd);

    if (!(ip[0] = strtok(tmp, ",")) or !(ip[1] = strtok(NULL, ","))
    or !(ip[2] = strtok(NULL, ",")) or !(ip[3] = strtok(NULL, ",")))
        write_message(socket_value, "501");
    if (!(ip[4] = strtok(NULL, ",")) or !(ip[5] = strtok(NULL, ",")))
        write_message(socket_value, "501");
    buffer = malloc(sizeof(char) * (strlen(ip[0]) + strlen(ip[1])
        + strlen(ip[2]) + strlen(ip[3]) + 4));
    if (!buffer)
        throw_error("Malloc error", EXIT_FAIL);
    sprintf(buffer, "%s.%s.%s.%s", ip[0], ip[1], ip[2], ip[3]);
    so_inf->socket_array[index].s_transmission_mode = ACTIVE;
    so_inf->socket_array[index].s_active.s_addr.sin_addr.s_addr =
        inet_addr(buffer);
    so_inf->socket_array[index].s_active.s_addr.sin_port =
        htons((atoi(ip[4]) * 256) + atoi(ip[5]));
    free(tmp);
}

bool command_pasv(socket_array_t *socket_info, const array cmd,
    unsigned int index, const string str)
{
    user_info_t user_info = socket_info->get_user_info(socket_info, index);
    socket_info_t socket_value = socket_info->at(socket_info, index);
    string ip = NULL;
    string buffer = NULL;
    size_t port = 1;

    if (!user_info.s_login or !user_info.s_pass) {
        write_message(socket_value.s_socket_value, "530");
        return (false);
    }
    port = go_to_passive_mode(socket_info, index);
    ip = replace_a_char('.', ',',
        socket_info->at(socket_info, index).s_ip_addr);
    buffer = malloc(sizeof(char) * (strlen(ip) + 40) + (sizeof(port) * 2));
    buffer[0] = '\0';
    sprintf(buffer, "227 Entering Passive Mode (%s,%ld,%ld).\r\n",
        ip, port / 256, port % 256);
    write(socket_value.s_socket_value, buffer, strlen(buffer));
    1 ? free(ip), free(buffer) : 0;
    return (true);
}

bool command_port(socket_array_t *so, const array cmd,
    unsigned int idx, const string str)
{
    user_info_t user_info = so->get_user_info(so, idx);
    socket_info_t socket = so->at(so, idx);

    if (!user_info.s_login or !user_info.s_pass
    or tab_len(cmd) < 2 or !cmd[1]) {
        write_message(socket.s_socket_value, "530");
        return (false);
    }
    go_to_active_mode(so, idx, cmd[1], socket.s_socket_value);
    if (connect(so->at(so, idx).s_active.fd,
    (const struct sockaddr *)&socket.s_active.s_addr,
    sizeof(so->at(so, idx).s_active.s_addr)) < 0) {
        write_message(so->at(so, idx).s_socket_value, "500");
        so->socket_array[idx].s_transmission_mode = NOT_SET;
    } else {
        write_message(socket.s_socket_value, "200");
        so->socket_array[idx].s_value = so->socket_array[idx].s_active.fd;
        so->socket_array[idx].s_last_fd = so->socket_array[idx].s_active.fd;
    }
    return (true);
}