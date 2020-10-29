/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** create_server
*/

#include "server_project.h"
#include "project_macro.h"
#include <signal.h>
#include <stdio.h>

static volatile int keep_running = true;

bool use_keep_running(bool state, bool value)
{
    static bool keep_running = true;

    if (state == true) {
        keep_running = value;
    }
    return (keep_running);
}

void end_server(int sig)
{
    signal(sig, SIG_IGN);
    printf("%s[SERVER FTP] %sServer shutdown%s.\n", C_YELLOW, C_BLUE,
        C_RESET);
    use_keep_running(true, false);
    exit(0);
}

void server_loop(socket_array_t *socket_info)
{
    fd_set readfd;
    int activity = 0, max_value = 0;

    signal(SIGINT, end_server);
    while (use_keep_running(false, false)) {
        max_value = set_select(socket_info, &readfd);
        activity =  select(max_value + 1, &readfd, NULL, NULL, NULL);
        accept_client(socket_info, &readfd);
        client_operation(socket_info, &readfd);
    }
    socket_info->clear(socket_info);
}
