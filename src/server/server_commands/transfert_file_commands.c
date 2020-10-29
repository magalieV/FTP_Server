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
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

static bool run_cmd_retr(socket_info_t *socket_info, string cmd)
{
    int	fd;
    char buffer[1025];
    int	read_val;

    init_transmission(socket_info);
    if ((fd = open(cmd, O_RDONLY)) == -1)
        return (false);
    while ((read_val = read(fd, buffer, 1024)) > 0) {
        if (write(socket_info->s_value, buffer, read_val) == -1)
            return (false);
    }
    if (close(fd) == -1)
        return (false);
    return (true);
}

static bool run_cmd_stor(socket_info_t *socket_info, string cmd)
{
    int	fd;
    char buffer[1025];
    int	read_val;

    init_transmission(socket_info);
    if ((fd = creat(cmd, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
        return (false);
    while ((read_val = read(socket_info->s_value, buffer, 1024)) > 0) {
        if (write(fd, buffer, read_val) == -1)
            return (-1);
    }
    if (close(fd) == -1)
        return (false);
    return (true);
}

static void run_cmd(socket_array_t *sock, unsigned int idx,
    const array cmd, bool which)
{
    string dir;
    pid_t pid;
    int status = 0;

    dir = (tab_len(cmd) > 1) ? strdup(cmd[1]) : NULL;
    if (dir)
        dir = get_path_name(dir,
            sock->socket_array[idx].s_user_info.s_actual_path, true);
    if ((pid = fork()) < 0)
        return;
    else if (pid == 0) {
        (which == true) ? run_cmd_retr(&sock->socket_array[idx], dir) :
        run_cmd_stor(&sock->socket_array[idx], dir);
        if (shutdown(sock->socket_array[idx].s_last_fd, SHUT_RDWR) == - 1
            or close(sock->socket_array[idx].s_last_fd) == -1)
            exit(EXIT_FAILURE);
        exit(EXIT_SUCCESS);
    } else
        1 ? waitpid(pid, &status, 0), kill(pid, status) : 0;
    free(dir);
}

bool command_retr(socket_array_t *socket_info, const array cmd,
    unsigned int index, const string str)
{
    user_info_t user_info = socket_info->get_user_info(socket_info, index);
    socket_info_t socket_value = socket_info->at(socket_info, index);

    if (!user_info.s_login or !user_info.s_pass) {
        write_message(socket_value.s_socket_value, "530");
        return (false);
    } else if (socket_value.s_transmission_mode == NOT_SET) {
        write_message(socket_value.s_socket_value, "425");
        return (false);
    }
    if (tab_len(cmd) < 2 or !cmd[1]) {
        write_message(socket_value.s_socket_value, "501");
        return (false);
    }
    write_message(socket_value.s_socket_value, "150");
    run_cmd(socket_info, index, cmd, true);
    write_message(socket_value.s_socket_value, "226");
    socket_info->socket_array[index].s_transmission_mode = NOT_SET;
    return (true);
}

bool command_stor(socket_array_t *socket_info, const array cmd,
    unsigned int index, const string str)
{
    user_info_t user_info = socket_info->get_user_info(socket_info, index);
    socket_info_t socket_value = socket_info->at(socket_info, index);

    if (!user_info.s_login or !user_info.s_pass) {
        write_message(socket_value.s_socket_value, "530");
        return (false);
    } else if (socket_value.s_transmission_mode == NOT_SET) {
        write_message(socket_value.s_socket_value, "425");
        return (false);
    }
    if (tab_len(cmd) < 2 or !cmd[1]) {
        write_message(socket_value.s_socket_value, "501");
        return (false);
    }
    write_message(socket_value.s_socket_value, "150");
    run_cmd(socket_info, index, cmd, false);
    write_message(socket_value.s_socket_value, "226");
    socket_info->socket_array[index].s_transmission_mode = NOT_SET;
    return (true);
}