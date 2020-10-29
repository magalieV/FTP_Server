/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** create_server
*/

#ifndef __SERVER_PROJECT__
#define __SERVER_PROJECT__

#include "socket_info.h"
#include <sys/select.h>

/*********Error prototypes*********/
void throw_error(const string, int);

/*********Server Prototypes*********/
socket_array_t create_server(string);
void server_loop(socket_array_t *);

/*********Tools prototypes*********/
bool write_message(int, void *);
array split(string, string);
unsigned int tab_len(const array);
string replace_a_char(char, char, string);
string go_to_parent(const string);
string get_path_name(const string, const string, bool);

/*********Commands prototypes*********/
void parse_command(string, socket_array_t *, unsigned int);
bool command_user(socket_array_t *, const array, unsigned int, const string);
bool command_pass(socket_array_t *, const array, unsigned int, const string);
bool command_quit(socket_array_t *, const array, unsigned int, const string);
bool command_pwd(socket_array_t *, const array, unsigned int, const string);
bool command_cwd(socket_array_t *, const array, unsigned int, const string);
bool command_cdup(socket_array_t *, const array, unsigned int, const string);
bool command_auth(socket_array_t *, const array, unsigned int, const string);
bool command_type_i(socket_array_t *, const array, unsigned int, const string);
bool command_pasv(socket_array_t *, const array, unsigned int, const string);
bool command_port(socket_array_t *, const array, unsigned int, const string);
bool command_noop(socket_array_t *, const array, unsigned int, const string);
bool command_list(socket_array_t *, const array, unsigned int, const string);
bool command_help(socket_array_t *, const array, unsigned int, const string);
bool command_dele(socket_array_t *, const array, unsigned int, const string);
bool command_retr(socket_array_t *, const array, unsigned int, const string);
bool command_stor(socket_array_t *, const array, unsigned int, const string);

/*********Client Operation*********/
int set_select(socket_array_t *, fd_set *);
void accept_client(socket_array_t *, fd_set *);
void client_operation(socket_array_t *, fd_set *);

/*********Transfert Operation*********/
void init_transmission(socket_info_t *);

#endif //__SERVER_PROJECT__