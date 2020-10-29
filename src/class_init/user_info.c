/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** create_server
*/

#include <string.h>
#include "socket_info.h"
#include "server_project.h"

static socket_info_t at(struct socket_array_s *this, unsigned int index)
{
    if (index >= MAX_CLIENT or index < 0 or this == NULL) {
        throw_error("The index request in the array doesn't exist",
                    EXIT_FAIL);
    }
    return (this->socket_array[index]);
}

static void set_actual_path(struct socket_array_s *this, unsigned int index,
    const string path)
{
    if (this == NULL or index < 0 or index >= MAX_CLIENT
        or this->at(this, index).s_socket_type == FREE) {
        throw_error("Error : Set login of socket", EXIT_FAIL);
    }
    if (this->socket_array[index].s_user_info.s_actual_path != NULL)
        free(this->socket_array[index].s_user_info.s_actual_path);
    this->socket_array[index].s_user_info.s_actual_path = strdup(path);
}

static void set_user_name(struct socket_array_s *this, unsigned int index,
    const string name)
{
    if (this == NULL or index < 0 or index >= MAX_CLIENT
        or this->at(this, index).s_socket_type == FREE) {
        throw_error("Error : Set login of socket", EXIT_FAIL);
    }
    this->socket_array[index].s_user_info.s_user_name = strdup(name);
}

void init_socket_array_part_four(socket_array_t *socket_array)
{
    socket_array->at = &at;
    socket_array->set_user_name = &set_user_name;
    socket_array->set_actual_path = &set_actual_path;
}
