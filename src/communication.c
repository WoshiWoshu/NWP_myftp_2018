/*
** EPITECH PROJECT, 2019
** server ftp
** File description:
** communication.c
*/

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "my_ftp.hpp"

static int interpret_login_user_inputs(communicate_t *communicate,
    int *sock_cli_fd, char client_msg[], int i)
{
    quit_cmd(communicate, sock_cli_fd, i);
    if (strcmp(communicate->cmd_param[0], "PASS\0") == 0
    && !(communicate->enter.username[i]) &&
    !(communicate->enter.login_exec)) {
        write(*sock_cli_fd, BAD_SEQUENCES, strlen(BAD_SEQUENCES));
        return (WRONG_ORDER);
    }
    if (strcmp(communicate->cmd_param[0], "\0") == 0
    && strcmp(communicate->cmd_param[1], "\0") == 0
    && strcmp(client_msg, "\r\n\0") != 0
    && (!(communicate->enter.login_exec) || communicate->enter.login_exec == 2))
        write(*sock_cli_fd, BAD_INPUT_LOGIN, strlen(BAD_INPUT_LOGIN));
    if ((strcmp(communicate->cmd_param[0], "\0") != 0
    || strcmp(communicate->cmd_param[1], "\0") != 0)
    && (!(communicate->enter.login_exec) || communicate->enter.login_exec == 2))
        write(*sock_cli_fd, BAD_INPUT_LOGIN, strlen(BAD_INPUT_LOGIN));
    return (SUCCESS);
}

static bool user_authentification_portal(communicate_t *communicate,
    int sock_cli_fd, int i)
{
    if (!(communicate->enter.username[i]) && user_cmd(communicate,
    sock_cli_fd, i) == SUCCESS)
            return (FAILURE);
    if (communicate->enter.username[i] &&
    pass_cmd(communicate, sock_cli_fd, i) == SUCCESS)
            return (SUCCESS);
    return (FAILURE);
}

static void check_for_commands(communicate_t *communicate,
    int *sock_cli_fd, char client_msg[], int i)
{
    bzero(communicate->cmd_param[0], sizeof(communicate->cmd_param[0]));
    bzero(communicate->cmd_param[1], sizeof(communicate->cmd_param[1]));
    get_first_elem_array(client_msg, communicate->cmd_param[0]);
    get_second_elem_array(client_msg, communicate->cmd_param[1]);
    if (!(communicate->enter.authent[i])) {
        communicate->enter.authent[i] =
        user_authentification_portal(communicate, *sock_cli_fd, i);
        if (interpret_login_user_inputs(communicate, sock_cli_fd, client_msg, i)
        == WRONG_ORDER)
            return;
    }
    else
        call_user_commands(communicate, client_msg, sock_cli_fd);
}

static void manage_data_flow(connect_t *connect,
    communicate_t *communicate, int *sock_cli_fd, int i)
{
    char client_msg[BUFF_SIZE];
    int read_fd;

    bzero(client_msg, sizeof(client_msg));
    read_fd = read(*sock_cli_fd, client_msg, BUFF_SIZE);
    if (read_fd == -1) {
        close(*sock_cli_fd);
        close(connect->sock_fd);
        exit(84);
    } else if (read_fd == 0) {
        check_close_window(connect, communicate, sock_cli_fd, i);
    } else
        if (check_back_slash_n_r(client_msg)) {
            printf("From client fd %d: %s", *sock_cli_fd, client_msg);
            check_for_commands(communicate, sock_cli_fd, client_msg, i);
        }
}

void server_client_communication(connect_t *connect, communicate_t *communicate)
{
    int sock_cli_fd;

    for (int i = 0; i < CLIENT_SOCKET_SIZE; i++) {
        sock_cli_fd = communicate->client_socket[i];
        if (FD_ISSET(sock_cli_fd, &(communicate->cmd.fset))) {
            bzero(communicate->cmd_param[0], sizeof(communicate->cmd_param[0]));
            bzero(communicate->cmd_param[1], sizeof(communicate->cmd_param[1]));
            manage_data_flow(connect, communicate, &sock_cli_fd, i);
        }
    }
}
