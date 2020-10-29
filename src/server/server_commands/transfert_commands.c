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
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void init_transmission(socket_info_t *socket_info)
{
    socklen_t client_size;

    if (socket_info->s_transmission_mode == PASSIVE) {
        socket_info->s_last_fd = socket_info->s_passive.fd;
        client_size = sizeof(socket_info->s_passive.s_addr);
        if ((socket_info->s_value = accept(socket_info->s_passive.fd,
        (struct sockaddr *)&socket_info->s_passive.s_addr, &client_size)) < 0)
            throw_error("Accept transmission error.", EXIT_FAIL);
    }
}

static string my_strcat(string dest, const string src)
{
    unsigned int dest_len = strlen(dest);

    for (unsigned int index = 0; src[index]; index++) {
        dest[dest_len] = src[index];
        dest_len++;
    }
    dest[dest_len] = '\0';
    return (dest);
}

static bool run_list_cmd(socket_info_t *socket_info, string cmd)
{
    int	old_fd;
    string my_cmd = NULL;

    init_transmission(socket_info);
    my_cmd = malloc(sizeof(char) * (strlen(cmd) + 25));
    if (!my_cmd)
        throw_error("Malloc_error", EXIT_FAIL);
    my_cmd[0] = '\0';
    my_cmd = my_strcat(my_cmd, "/bin/ls -l ");
    my_cmd = my_strcat(my_cmd, cmd);
    my_cmd = my_strcat(my_cmd, " | tail -n +2");
    if ((old_fd = dup(1)) == -1 || dup2(socket_info->s_value, 1) == -1 ||
    system(my_cmd) == -1 || dup2(old_fd, 1) == -1)
        return (false);
    free(my_cmd);
    return (true);
}

static void run_command(socket_array_t *sock, unsigned int idx,
    const array cmd)
{
    pid_t pid;
    string dir;
    int status = 0;

    if (tab_len(cmd) > 1)
        dir = get_path_name(cmd[1],
            sock->socket_array[idx].s_user_info.s_actual_path, true);
    else
        dir = strdup(sock->get_user_info(sock, idx).s_actual_path);
    if ((pid = fork()) < 0)
        return;
    else if (pid == 0) {
        run_list_cmd(&sock->socket_array[idx], dir);
        if (shutdown(sock->socket_array[idx].s_last_fd, SHUT_RDWR) == - 1
        or close(sock->socket_array[idx].s_last_fd) == -1)
            exit(EXIT_FAILURE);
        exit(EXIT_SUCCESS);
    } else
        1 ? waitpid(pid, &status, 0), kill(pid, status) : 0;
    free(dir);
}

bool command_list(socket_array_t *socket_info, const array cmd,
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
    write_message(socket_value.s_socket_value, "150");
    run_command(socket_info, index, cmd);
    write_message(socket_value.s_socket_value, "226");
    socket_info->socket_array[index].s_transmission_mode = NOT_SET;
    return (true);
}