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

bool command_cwd(socket_array_t *socket_info, const array cmd,
    unsigned int index, const string str)
{
    user_info_t user_info = socket_info->get_user_info(socket_info, index);
    socket_info_t socket_value = socket_info->at(socket_info, index);
    const string path;

    if (!user_info.s_login or !user_info.s_pass) {
        write_message(socket_value.s_socket_value, "530");
        return (false);
    } else if (tab_len(cmd) < 2 or !cmd[1]) {
        write_message(socket_value.s_socket_value, "550");
        return (false);
    }
    path = get_path_name(cmd[1], user_info.s_actual_path, true);
    if (chdir(path) != 0) {
        write_message(socket_value.s_socket_value, "550");
        return (false);
    }
    socket_info->set_actual_path(socket_info, index, path);
    write_message(socket_value.s_socket_value, "250");
    return (true);
}

bool command_pwd(socket_array_t *socket_info, const array cmd,
    unsigned int index, const string str)
{
    user_info_t user_info = socket_info->get_user_info(socket_info, index);
    socket_info_t socket_value = socket_info->at(socket_info, index);
    string buffer = NULL;

    if (!user_info.s_login or !user_info.s_pass) {
        write_message(socket_value.s_socket_value, "530");
        return (false);
    }
    buffer = malloc(sizeof(char) * (strlen(user_info.s_actual_path) + 17));
    sprintf(buffer, "257 \"%s\" created.\n", user_info.s_actual_path);
    write(socket_value.s_socket_value, buffer, strlen(buffer));
    free(buffer);
    return (true);
}

bool command_cdup(socket_array_t *socket_info, const array cmd,
    unsigned int index, const string str)
{
    user_info_t user_info = socket_info->get_user_info(socket_info, index);
    socket_info_t socket_value = socket_info->at(socket_info, index);

    if (!user_info.s_login or !user_info.s_pass) {
        write_message(socket_value.s_socket_value, "530");
        return (false);
    }
    socket_info->set_actual_path(socket_info, index,
        go_to_parent(socket_value.s_user_info.s_actual_path));
    write_message(socket_value.s_socket_value, "250");
    return (true);
}

bool command_noop(socket_array_t *socket_info, const array cmd,
    unsigned int index, const string str)
{
    user_info_t user_info = socket_info->get_user_info(socket_info, index);
    socket_info_t socket_value = socket_info->at(socket_info, index);

    if (!user_info.s_login or !user_info.s_pass) {
        write_message(socket_value.s_socket_value, "530");
        return (false);
    } else if (tab_len(cmd) > 1) {
        write_message(socket_value.s_socket_value, "501");
        return (false);
    }
    write_message(socket_value.s_socket_value, "200");
    return (true);
}