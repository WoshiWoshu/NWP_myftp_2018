/*
** EPITECH PROJECT, 2019
** ftp server
** File description:
** my_ftp.c
*/

#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include "my_ftp.hpp"

static bool connection(connect_t *connect, char **av)
{
    connect->sock_fd = create_socket();
    if (connect->sock_fd == FAILURE)
        return (FAILURE);
    if (set_socket_opt(connect) == FAILURE)
        return (FAILURE);
    if (bind_socket(connect, av) == FAILURE)
        return (FAILURE);
    if (server_listening(connect) == FAILURE)
        return (FAILURE);
    return (SUCCESS);
}

static bool communication(connect_t *connect, communicate_t *communicate)
{
    while (42) {
        if (handle_multi_clients(connect, communicate) == FAILURE)
            return (FAILURE);
        server_client_communication(connect, communicate);
    }
    return (SUCCESS);
}

bool my_ftp(char **av)
{
    connect_t connect;
    communicate_t communicate;

    strcpy(communicate.cmd.path_user, av[2]);
    chdir(communicate.cmd.path_user);
    if (connection(&connect, av) == FAILURE)
        return (FAILURE);
    if (communication(&connect, &communicate) == FAILURE)
        return (FAILURE);
    close(connect.sock_fd);
    return (SUCCESS);
}
