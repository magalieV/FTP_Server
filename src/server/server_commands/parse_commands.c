/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** create_server
*/

#include "command_parser.h"
#include "socket_info.h"
#include <stdio.h>

typedef bool (*parse)(socket_array_t *, const array,
    unsigned int, const string str);

void parse_command(string cmd, socket_array_t *socket_info, unsigned int index)
{
    static int counter = 0;
    static map_t map_cmd;
    array arr = split(cmd, "\n\r\t ");

    if (counter == 0) {
        map_cmd = init_map((item_t *)command_parser_map);
        counter++;
    }
    if (!arr or !*arr) {
        write_message(socket_info->at(socket_info, index).s_socket_value,
            "500");
        return;
    }
    parse function = map_cmd.get_value(&map_cmd, arr[0]);
    if (function != NULL) {
        function(socket_info, (const array)arr, index, cmd);
    } else {
        write_message(socket_info->at(socket_info, index).s_socket_value,
            "500");
    }
}
