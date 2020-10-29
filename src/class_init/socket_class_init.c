/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** create_server
*/

#include <string.h>
#include "socket_info.h"
#include "server_project.h"

static user_info_t get_user_info(struct socket_array_s *this,
    unsigned int index)
{
    if (this == NULL or index < 0 or index >= MAX_CLIENT
        or this->at(this, index).s_socket_type == FREE) {
        throw_error("Error : Set login of socket", EXIT_FAIL);
    }
    return (this->socket_array[index].s_user_info);
}

static bool set_login(struct socket_array_s *this, unsigned int index,
    bool login)
{
    if (this == NULL or index < 0 or index >= MAX_CLIENT
        or this->at(this, index).s_socket_type == FREE) {
        throw_error("Error : Set login of socket", EXIT_FAIL);
    }
    if (this->at(this, index).s_user_info.s_login == login) {
        return (false);
    } else {
        this->socket_array[index].s_user_info.s_login = login;
    }
    return (true);
}

static bool set_pass(struct socket_array_s *this, unsigned int index,
    bool pass)
{
    if (this == NULL or index < 0 or index >= MAX_CLIENT
        or this->at(this, index).s_socket_type == FREE) {
        throw_error("Error : Set pass of socket", EXIT_FAIL);
    }
    if (this->at(this, index).s_user_info.s_pass == pass) {
        return (false);
    } else {
        this->socket_array[index].s_user_info.s_pass = pass;
    }
    return (true);
}

void init_socket_array_part_three(socket_array_t *socket_array)
{
    socket_array->set_pass = &set_pass;
    socket_array->set_login = &set_login;
    socket_array->get_user_info = &get_user_info;
    init_socket_array_part_four(socket_array);
}