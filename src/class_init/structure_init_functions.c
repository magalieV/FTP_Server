/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** create_server
*/

#include "socket_info.h"
#include "server_project.h"
#include <string.h>

static int get_first_free(struct socket_array_s *this)
{
    if (this == NULL) {
        throw_error("The socket array doesn't exist", EXIT_FAIL);
    }
    for (int index = 0; index < MAX_CLIENT; index++) {
        if (this->at(this, index).s_socket_type == FREE)
            return (index);
    }
    return (ERROR_VALUE);
}

static bool set_free(struct socket_array_s *this, unsigned int index)
{
    if (this == NULL or index < 0 or index > MAX_CLIENT
    or this->at(this, index).s_socket_type == FREE) {
        return (false);
    }
    if (this->at(this, index).s_socket_type == SERVEUR)
        this->server_index = -1;
    this->socket_array[index] = (socket_info_t){.s_socket_type = FREE,
                                                .s_socket_value = 0};
    this->number_of_socket -= 1;
    return (true);
}

static int get_server_index(struct socket_array_s *this)
{
    return (this->server_index);
}

static bool set_info(struct socket_array_s *this, unsigned int index,
    string ip_addr, unsigned int port)
{
    if (this == NULL or index < 0 or index >= MAX_CLIENT
    or this->at(this, index).s_socket_type == FREE) {
        throw_error("Error : Set info of socket", EXIT_FAIL);
    }
    this->socket_array[index].s_ip_addr = ip_addr;
    this->socket_array[index].s_port = port;
    return (true);
}

void init_socket_array_part_two(socket_array_t *socket_array)
{
    socket_array->server_index = -1;
    socket_array->get_first_free = &get_first_free;
    socket_array->set_free = &set_free;
    socket_array->get_server_index = &get_server_index;
    socket_array->set_info = &set_info;
    init_socket_array_part_three(socket_array);
}
