/*
** EPITECH PROJECT, 2019
** ftp server
** File description:
** multi_clients.c
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "my_ftp.hpp"

static void add_fdserver_to_set(connect_t *connect, communicate_t *communicate)
{
    static bool init_one_time = true;

    if (init_one_time) {
        memset(communicate->client_socket, 0,
        sizeof(communicate->client_socket));
        memset(communicate->enter.username, false,
        sizeof(communicate->enter.username));
        memset(communicate->enter.authent, false,
        sizeof(communicate->enter.authent));
        memset(communicate->enter.anonymous, false,
        sizeof(communicate->enter.anonymous));
        memset(communicate->cmd.path, 0,
        sizeof(communicate->cmd.path));
        communicate->enter.login_exec = false;
        init_one_time = false;
    }
    FD_ZERO(&(communicate->cmd.fset));
    FD_SET(connect->sock_fd, &(communicate->cmd.fset));
    connect->max_fd = connect->sock_fd;
}

static void add_fdclient_to_set(connect_t *connect, communicate_t *communicate)
{
    int sock_cli_fd;

    for (int i = 0; i < CLIENT_SOCKET_SIZE; i++) {
        sock_cli_fd = communicate->client_socket[i];
        if (sock_cli_fd > 0)
            FD_SET(sock_cli_fd, &(communicate->cmd.fset));
        if (sock_cli_fd > connect->max_fd)
            connect->max_fd = sock_cli_fd;
    }
}

static void new_client_request(connect_t *connect, communicate_t *communicate)
{
    connect->conn_fd = accept_client(connect);
    if (connect->conn_fd == FAILURE)
        exit(84);
    printf("New connection, socket fd is %d, ip is : %s, port : %d\n",
    connect->conn_fd, inet_ntoa(connect->addr.sin_addr),
    ntohs(connect->addr.sin_port));
    write(connect->conn_fd, NEW_CLIENT, strlen(NEW_CLIENT));
    for (int i = 0; i < CLIENT_SOCKET_SIZE; i++)
        if (communicate->client_socket[i] == 0) {
            communicate->client_socket[i] = connect->conn_fd;
            break;
        }
}

static bool select_file_descriptor(connect_t *connect,
    communicate_t *communicate)
{
    if (select(connect->max_fd + 1, &(communicate->cmd.fset),
    NULL, NULL, NULL) < 0) {
        write(2, SELECT_FAILED, strlen(SELECT_FAILED));
        return (FAILURE);
    }
    return (SUCCESS);
}

bool handle_multi_clients(connect_t *connect, communicate_t *communicate)
{
    add_fdserver_to_set(connect, communicate);
    add_fdclient_to_set(connect, communicate);
    if (select_file_descriptor(connect, communicate) == FAILURE)
        return (FAILURE);
    if (FD_ISSET(connect->sock_fd, &(communicate->cmd.fset)))
        new_client_request(connect, communicate);
    return (SUCCESS);
}
