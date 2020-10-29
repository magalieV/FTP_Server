/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** create_server
*/

#include "socket_info.h"
#include "server_project.h"
#include <stdio.h>

static void clear(struct socket_array_s *this)
{
    if (this == NULL) {
        throw_error("The array doesn't exit", EXIT_FAIL);
    }
    for (int index = 0; index < MAX_CLIENT; index++) {
        if (this->socket_array[index].s_user_info.s_user_name != NULL)
            free(this->socket_array[index].s_user_info.s_user_name);
        if (this->socket_array[index].s_user_info.s_user_name != NULL)
            free(this->socket_array[index].s_user_info.s_user_name);
        this->socket_array[index] = (socket_info_t){.s_socket_type = FREE,
            .s_socket_value = 0,
            .s_ip_addr = NULL,
            .s_port = 0,
            .s_transmission_mode = NOT_SET,
            .s_user_info = {.s_user_name = NULL,
                            .s_pass = false,
                            .s_login = false,
                            .s_actual_path = NULL}};
    }
    free(this->real_path);
}

static bool add_client(struct socket_array_s *this, unsigned int index,
    int fd)
{
    if (this == NULL) {
        throw_error("The array doesn't exit", EXIT_FAIL);
    }
    if (this->at(this, index).s_socket_type != FREE or index < 0
    or index >= MAX_CLIENT) {
        return (false);
    }
    this->socket_array[index] = (socket_info_t){.s_socket_type = CLIENT,
                                                .s_socket_value = fd};
    this->number_of_socket += 1;
    return (true);
}

static bool add_server(struct socket_array_s *this, unsigned int index, int fd)
{
    if (this == NULL) {
        throw_error("The array doesn't exit", EXIT_FAIL);
    }
    if (this->at(this, index).s_socket_type != FREE or index < 0
        or index >= MAX_CLIENT) {
        return (false);
    }
    this->socket_array[index] = (socket_info_t){.s_socket_type = SERVEUR,
        .s_socket_value = fd};
    this->number_of_socket += 1;
    this->server_index = (int)index;
    return (true);
}

void init_socket_array_part_one(socket_array_t *socket_array)
{
    socket_array->add_client = &add_client;
    socket_array->add_server = &add_server;
    socket_array->clear(socket_array);
}

socket_array_t init_socket_array(void)
{
    socket_array_t sock;

    for (int index = 0; index < MAX_CLIENT; index++) {
        sock.socket_array[index] = (socket_info_t){.s_socket_type = FREE,
            .s_socket_value = 0,
            .s_ip_addr = NULL,
            .s_port = 0,
            .s_transmission_mode = NOT_SET,
            .s_user_info = {.s_user_name = NULL,
                .s_pass = false,
                .s_login = false,
                .s_actual_path = NULL}};
    }
    sock.real_path = NULL;
    sock.number_of_socket = 0;
    sock.clear = &clear;
    init_socket_array_part_one(&sock);
    init_socket_array_part_two(&sock);
    return (sock);
}