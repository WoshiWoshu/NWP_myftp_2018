/*
** EPITECH PROJECT, 2019
** ftp server
** File description:
** connection.c
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "my_ftp.hpp"

int create_socket(void)
{
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (sock_fd == -1) {
        write(2, SOCKET_FAILED, strlen(SOCKET_FAILED));
        return (FAILURE);
    } else
        printf("Socket successfully created\n");
    return (sock_fd);
}

bool set_socket_opt(connect_t *connect)
{
    int opt_sock = 1;

    if (setsockopt(connect->sock_fd, SOL_SOCKET, SO_REUSEADDR
    | SO_REUSEPORT, &opt_sock, sizeof(opt_sock)) < 0)
        return (FAILURE);
    return (SUCCESS);
}

bool bind_socket(connect_t *connect, char **av)
{
    bzero(&(connect->addr), sizeof(connect->addr));
    connect->addr.sin_family = AF_INET;
    connect->addr.sin_addr.s_addr = htonl(INADDR_ANY);
    connect->addr.sin_port = htons(atoi(av[1]));
    if ((bind(connect->sock_fd, (struct sockaddr *)&(connect->addr),
    sizeof(connect->addr))) != 0) {
        write(2, BIND_FAILED, strlen(BIND_FAILED));
        return (FAILURE);
    } else
        printf("Socket successfully binded\n");
    return (SUCCESS);
}

bool server_listening(connect_t *connect)
{
    if ((listen(connect->sock_fd, 10)) != 0) {
        write(2, LISTEN_FAILED, strlen(LISTEN_FAILED));
        return (FAILURE);
    }
    else
        printf("Server listening\n");
    return (SUCCESS);
}

int accept_client(connect_t *connect)
{
    int client_len;
    int conn_fd;

    bzero(&(connect->addr), sizeof(connect->addr));
    client_len = sizeof(connect->addr);
    conn_fd = accept(connect->sock_fd,
    (struct sockaddr *)&(connect->addr), (socklen_t *)&client_len);
    if (conn_fd < 0) {
        write(2, ACCEPT_FAILED, strlen(ACCEPT_FAILED));
        return (FAILURE);
    }
    else
        printf("Server accepted the client\n");
    return (conn_fd);
}
