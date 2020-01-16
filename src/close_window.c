/*
** EPITECH PROJECT, 2019
** my_ftp
** File description:
** close_window.c
*/

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "my_ftp.hpp"

void check_close_window(connect_t *connect,
    communicate_t *communicate,
    int *sock_cli_fd, int i)
{
    int addr_len;

    memset(&(connect->addr), 0, sizeof(connect->addr));
    addr_len = sizeof(connect->addr);
    getpeername(*sock_cli_fd, (struct sockaddr *)&(connect->addr),
    (socklen_t *)&addr_len);
    printf("Host disconnected, ip %s, port %d \n",
    inet_ntoa(connect->addr.sin_addr), ntohs(connect->addr.sin_port));
    close(*sock_cli_fd);
    communicate->client_socket[i] = 0;
    communicate->enter.authent[i] = false;
    communicate->enter.username[i] = false;
}
