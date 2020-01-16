/*
** EPITECH PROJECT, 2019
** ftp_server
** File description:
** basic_cmd.c
*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "my_ftp.hpp"

bool user_cmd(communicate_t *communicate, int sock_cli_fd, int i)
{
    if (strcmp(communicate->cmd_param[0], "USER\0") == 0
    && strcmp(communicate->cmd_param[1], "\0") != 0) {
        write(sock_cli_fd, USR_NAME_OK, strlen(USR_NAME_OK));
        communicate->enter.username[i] = true;
        communicate->enter.login_exec = true;
        strcpy(communicate->enter.anonymous, communicate->cmd_param[1]);
        return (SUCCESS);
    } else
        communicate->enter.login_exec = false;
    return (FAILURE);
}

bool pass_cmd(communicate_t *communicate, int sock_cli_fd, int i)
{
    if (strcmp(communicate->cmd_param[0], "PASS\0") == 0
    && communicate->cmd_param[1][0] == '\0'
    && strcmp(communicate->enter.anonymous, "Anonymous\0") == 0) {
        write(sock_cli_fd, USR_PASSWD_OK, strlen(USR_PASSWD_OK));
        communicate->enter.login_exec = true;
        return (SUCCESS);
    }
    else if (strcmp(communicate->cmd_param[0], "PASS\0") == 0
    && (communicate->cmd_param[1][0] != '\0'
    || strcmp(communicate->enter.anonymous, "Anonymous\0") != 0)) {
        communicate->enter.username[i] = false;
        communicate->enter.login_exec = 2;
    } else
        communicate->enter.login_exec = false;
    return (FAILURE);
}

bool quit_cmd(communicate_t *communicate, int *sock_cli_fd, int i)
{
    if (strcmp(communicate->cmd_param[0], "QUIT\0") == 0) {
        write(*sock_cli_fd, CLIENT_QUIT, strlen(CLIENT_QUIT));
        close(*sock_cli_fd);
        FD_CLR(*sock_cli_fd, &(communicate->cmd.fset));
        communicate->enter.login_exec = false;
        communicate->client_socket[i] = false;
        communicate->enter.authent[i] = false;
        communicate->enter.username[i] = false;
        memset(communicate->enter.anonymous, 0,
        sizeof(communicate->enter.anonymous));
        chdir(communicate->cmd.path_user);
        printf("Client socket fd %d disconnected\n", *sock_cli_fd);
        return (SUCCESS);
    }
    return (FAILURE);
}

bool help_cmd(communicate_t *communicate, int *sock_cli_fd, int i)
{
    (void)i;
    if (strcmp(communicate->cmd_param[0], "HELP\0") == 0) {
        write(*sock_cli_fd, CMD_HELP, strlen(CMD_HELP));
        write(*sock_cli_fd,
        "The commands are : PWD, CWD, DELE, HELP, NOOP, CDUP and QUIT.\r\n",
        strlen("The commands are : PWD, CWD, \
DELE, HELP, NOOP, CDUP and QUIT.\r\n"));
        write(*sock_cli_fd, "214 Help OK.\r\n", strlen("214 Help OK.\r\n"));
        return (SUCCESS);
    }
    return (FAILURE);
}

bool noop_cmd(communicate_t *communicate, int *sock_cli_fd, int i)
{
    (void)i;
    if (strcmp(communicate->cmd_param[0], "NOOP\0") == 0) {
        write(*sock_cli_fd, CMD_NOOP, strlen(CMD_NOOP));
        return (SUCCESS);
    }
    return (FAILURE);
}
