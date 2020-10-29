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

bool command_auth(socket_array_t *socket_info, const array cmd,
    unsigned int index, const string str)
{
    int socket_value = socket_info->at(socket_info, index).s_socket_value;

    write(socket_value, "530 Please login with USER and PASS.\n", 37);
    return (true);
}

bool command_user(socket_array_t *socket_info, const array cmd,
    unsigned int index, const string str)
{
    int socket_value = socket_info->at(socket_info, index).s_socket_value;

    if (socket_info->at(socket_info, index).s_user_info.s_pass == true
    or tab_len(cmd) < 2) {
        write_message(socket_value, "530");
        return (false);
    }
    socket_info->set_login(socket_info, index, true);
    write_message(socket_value, "331");
    socket_info->set_user_name(socket_info, index, cmd[1]);
    return (true);
}

bool command_pass(socket_array_t *socket_info, const array cmd,
    unsigned int index, const string str)
{
    int socket_value = socket_info->at(socket_info, index).s_socket_value;
    user_info_t user_info = socket_info->get_user_info(socket_info, index);

    if (user_info.s_login != true or !user_info.s_user_name
    or !*user_info.s_user_name or user_info.s_pass == true) {
        write_message(socket_value, "503");
        socket_info->set_login(socket_info, index, false);
        return (false);
    } else if (strcmp(user_info.s_user_name, "Anonymous") != 0
        or (tab_len(cmd) <= 1 and strcmp(str, "PASS \r\n") != 0
        and strcmp(str, "PASS \r") != 0 and strcmp(str, "PASS \n") != 0)) {
        write_message(socket_value, "530");
        return (false);
    }
    socket_info->set_pass(socket_info, index, true);
    socket_info->set_actual_path(socket_info, index, socket_info->real_path);
    write_message(socket_value, "230");
    return (true);
}

bool command_quit(socket_array_t *socket_info, const array cmd,
    unsigned int index, const string str)
{
    socket_info_t socket_value = socket_info->at(socket_info, index);

    write_message(socket_value.s_socket_value, "221");
    close(socket_value.s_socket_value);
    printf("%s[SERVER FTP] %sHost disconnected %s{IP=%s\tPORT=%d}%s.\n",
        C_YELLOW, C_BLUE, C_GREEN,
        socket_value.s_ip_addr, socket_value.s_port,
        C_RESET);
    socket_info->set_free(socket_info, index);
    return (true);
}

bool command_type_i(socket_array_t *socket_info, const array cmd,
    unsigned int index, const string str)
{
    int socket_value = socket_info->at(socket_info, index).s_socket_value;
    user_info_t user_info = socket_info->get_user_info(socket_info, index);

    if (!user_info.s_login or !user_info.s_pass) {
        write_message(socket_value, "530");
        return (false);
    } else if (tab_len(cmd) < 2 or (cmd[1][0] != 'I'
    and cmd[1][0] != 'A' and cmd[1][0] != 'E' and cmd[1][0] != 'L')) {
        write_message(socket_value, "501");
        return (false);
    }
    write_message(socket_value, "200");
    return (true);
}