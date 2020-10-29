/*
** EPITECH PROJECT, 2020
** myftp
** File description:
** create_server
*/

#ifndef __SOCKET_INFO__
#define __SOCKET_INFO__

#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <netinet/in.h>
#include "project_macro.h"

enum socket_type {SERVEUR, CLIENT, FREE};
enum transmission_mode {NOT_SET, PASSIVE, ACTIVE};

typedef struct info_connection_s
{
    struct sockaddr_in s_addr;
    int fd;
} info_connection_t;

typedef struct user_info_s
{
    string s_user_name;
    bool s_login;
    bool s_pass;
    string s_actual_path;
} user_info_t;

typedef struct socket_info_s {
    enum socket_type s_socket_type;
    int s_socket_value;
    struct sockaddr_in	s_addr;
    string s_ip_addr;
    unsigned int s_port;
    user_info_t s_user_info;
    enum transmission_mode s_transmission_mode;
    int s_value;
    int s_last_fd;
    info_connection_t s_passive;
    info_connection_t s_active;
} socket_info_t;

typedef struct socket_array_s {
    socket_info_t socket_array[MAX_CLIENT];
    unsigned int number_of_socket;
    int server_index;
    string real_path;
    socket_info_t (*at)(struct socket_array_s *this, unsigned int index);
    bool (*add_client)(struct socket_array_s *this, unsigned int index,
        int fd);
    bool (*set_info)(struct socket_array_s *this, unsigned int index,
        string ip_addr, unsigned int port);
    bool (*add_server)(struct socket_array_s *this, unsigned int index,
        int fd);
    int (*get_first_free)(struct socket_array_s *this);
    bool (*set_free)(struct socket_array_s *this, unsigned int index);
    void (*clear)(struct socket_array_s *this);
    bool (*set_login)(struct socket_array_s *this, unsigned int index,
        bool login);
    bool (*set_pass)(struct socket_array_s *this, unsigned int index,
        bool pass);
    int (*get_server_index)(struct socket_array_s *this);
    void (*set_user_name)(struct socket_array_s *this, unsigned int index,
        const string name);
    user_info_t (*get_user_info)(struct socket_array_s *this,
        unsigned int index);
    void (*set_actual_path)(struct socket_array_s *this, unsigned int index,
        const string path);
} socket_array_t;

void init_socket_array_part_one(socket_array_t *socket_array);
void init_socket_array_part_two(socket_array_t *socket_array);
void init_socket_array_part_three(socket_array_t *socket_array);
void init_socket_array_part_four(socket_array_t *socket_array);
socket_array_t init_socket_array(void);

#endif //__SOCKET_INFO__
