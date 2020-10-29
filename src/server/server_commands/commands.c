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

bool command_help(socket_array_t *socket_info, const array cmd,
    unsigned int index, const string str)
{
    user_info_t user_info = socket_info->get_user_info(socket_info, index);
    socket_info_t socket_value = socket_info->at(socket_info, index);

    if (!user_info.s_login or !user_info.s_pass) {
        write_message(socket_value.s_socket_value, "530");
        return (false);
    }
    write(socket_value.s_socket_value,
        "214-The following commands are recognized.\r\n"
        " AUTH\tUSER\tPASS\tQUIT\tPWD\tCWD\tCDUP\tTYPE\tPASV\r\n"
        " PORT\tLIST\tNOOP\tHELP\tDELE\tRETR\tSTOR\r\n", 126);
    write_message(socket_value.s_socket_value, "214");
    return (true);
}

bool command_dele(socket_array_t *socket_info, const array cmd,
    unsigned int index, const string str)
{
    user_info_t user_info = socket_info->get_user_info(socket_info, index);
    socket_info_t socket_value = socket_info->at(socket_info, index);
    const string path = NULL;

    if (!user_info.s_login or !user_info.s_pass) {
        write_message(socket_value.s_socket_value, "530");
        return (false);
    } else if (tab_len(cmd) < 2 or !cmd[1]) {
        write_message(socket_value.s_socket_value, "501");
        return (false);
    }
    path = get_path_name(cmd[1], user_info.s_actual_path, false);
    if (remove(path) != 0) {
        write_message(socket_value.s_socket_value, "550");
        return (false);
    }
    write_message(socket_value.s_socket_value, "250");
    return (true);
}