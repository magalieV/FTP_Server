/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** create_server
*/

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "socket_info.h"
#include "server_project.h"

static void client_changement(int sd, socket_array_t *so_inf,
    unsigned int index)
{
    int read_value = 0;
    socket_info_t socket_info;
    char buffer[1024];

    if (sd != -1 and (read_value = read(sd, buffer, 1024)) == 0) {
        socket_info = so_inf->at(so_inf, index);
        printf("%s[SERVER FTP] %sHost disconnected %s{IP=%s\tPORT=%d}%s.\n",
        C_YELLOW, C_BLUE, C_GREEN, socket_info.s_ip_addr,
        socket_info.s_port, C_RESET);
        close(sd);
        so_inf->set_free(so_inf, index);
    } else if (sd != -1 and read_value != -3) {
        socket_info = so_inf->at(so_inf, index);
        buffer[read_value] = '\0';
        printf("%s[SERVER FTP] %sMessage from %s{IP=%s\tPORT=%d} %s-> %s%s%s\n",
        C_YELLOW, C_BLUE, C_GREEN, socket_info.s_ip_addr, socket_info.s_port,
        C_RESET, C_MAGENTA, buffer, C_RESET);
        parse_command(buffer, so_inf, index);
    }
}

static int set_max_value(int max_value, int sd, fd_set *readfd)
{
    if (sd > 0)
        FD_SET(sd, readfd);
    if (sd > max_value)
        max_value = sd;
    return (max_value);
}

int set_select(socket_array_t *socket_info, fd_set *readfd)
{
    int server_index = socket_info->get_server_index(socket_info);
    int sd = 0;
    int max_value = socket_info->at(socket_info, server_index).s_socket_value;

    FD_ZERO(readfd);
    FD_SET(max_value, readfd);
    for (unsigned int index = 0; index < MAX_CLIENT; index++) {
        if (socket_info->at(socket_info, index).s_socket_type == CLIENT
        or socket_info->at(socket_info, index).s_socket_type == SERVEUR) {
            sd = socket_info->at(socket_info, index).s_socket_value;
            max_value = set_max_value(max_value, sd, readfd);
        }
    }
    return (max_value);
}

void accept_client(socket_array_t *socket_inf, fd_set *readfd)
{
    int sock = 0, server_index = socket_inf->get_server_index(socket_inf);
    int new_index = 0;
    int sr_val = socket_inf->at(socket_inf, server_index).s_socket_value;
    struct sockaddr_in cl_inf;
    int cl_sz = sizeof(cl_inf);

    if (FD_ISSET(sr_val, readfd)) {
        sock = accept(sr_val, (struct sockaddr *)&cl_inf, (socklen_t *)&cl_sz);
        if (sock < 0)
            throw_error("Accept error", EXIT_FAIL);
        printf("%s[SERVER FTP] %sNew connection by %s{IP=%s\tPORT=%d}%s.\n",
        C_YELLOW, C_BLUE, C_GREEN,
        inet_ntoa(cl_inf.sin_addr), ntohs(cl_inf.sin_port), C_RESET);
        write_message(sock, "220");
        new_index = socket_inf->get_first_free(socket_inf);
        socket_inf->add_client(socket_inf, new_index, sock);
        socket_inf->set_info(socket_inf, new_index, inet_ntoa(cl_inf.sin_addr),
        ntohs(cl_inf.sin_port));
        socket_inf->socket_array[new_index].s_addr = cl_inf;
    }
}

void client_operation(socket_array_t *so_inf, fd_set *readfd)
{
    int sd = 0;
    struct sockaddr_in client_info;

    bzero(&client_info, sizeof(client_info));
    for (unsigned int index = 0; index < MAX_CLIENT; index++) {
        sd = (so_inf->at(so_inf, index).s_socket_type == CLIENT) ?
            so_inf->at(so_inf, index).s_socket_value : -1;
        if (sd != -1 and FD_ISSET(sd, readfd)) {
            client_changement(sd, so_inf, index);
        }
    }
}