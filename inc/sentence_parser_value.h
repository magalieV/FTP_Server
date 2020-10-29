/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** create_server
*/

#ifndef __SENTENCE_PARSER_VALUE__
#define __SENTENCE_PARSER_VALUE__

#include "map_class.h"

const item_t answer_value_map[]  = {
    {"120", "Service ready in nnn minutes.\r"},
    {"125", "Data connection already open; transfer starting.\r"},
    {"150", "File status okay; about to open data connection.\r"},
    {"200", "Command okay.\r"},
    {"214", "Help message.\r"},
    {"220", "Service ready for new user.\r"},
    {"221", "Service closing control connection.\r"},
    {"226", "Closing data connection.\r"},
    {"227", "Entering Passive Mode (h1,h2,h3,h4,p1,p2).\r"},
    {"230", "User logged in, proceed.\r"},
    {"250", "Requested file action okay, completed.\r"},
    {"257", "\"PATHNAME\" created.\r"},
    {"331", "User name okay, need password.\r"},
    {"332", "Need account for login.\r"},
    {"xxx", "Error\r"},
    {"425", "Can't open data connection.\r"},
    {"500", "Syntax error, command unrecognized."},
    {"501", "Syntax error in parameters or arguments.\r"},
    {"503", "Bad sequence of commands.\r"},
    {"530", "Not logged in.\r"},
    {"550", "Requested action not taken.\r"},
    {NULL, NULL}};

#endif //__SENTENCE_PARSER_VALUE__
