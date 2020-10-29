/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** create_server
*/

#ifndef __COMMAND_PARSER__
#define __COMMAND_PARSER__

#include "map_class.h"
#include "server_project.h"

const item_t command_parser_map[] = {
    {"AUTH", &command_auth},
    {"USER", &command_user},
    {"PASS", &command_pass},
    {"QUIT", &command_quit},
    {"PWD", &command_pwd},
    {"CWD", &command_cwd},
    {"CDUP", &command_cdup},
    {"TYPE", &command_type_i},
    {"PASV", &command_pasv},
    {"PORT", &command_port},
    {"LIST", &command_list},
    {"NOOP", &command_noop},
    {"HELP", &command_help},
    {"DELE", &command_dele},
    {"RETR", &command_retr},
    {"STOR", &command_stor},
    {NULL, NULL}
};

#endif //__COMMAND_PARSER__