/*
** EPITECH PROJECT, 2019
** ftp server
** File description:
** normal_cmd.c
*/

#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "my_ftp.hpp"

bool cwd_cmd(communicate_t *communicate, int *sock_cli_fd, int i)
{
    (void)i;
    if (strcmp(communicate->cmd_param[0], "CWD\0") == 0) {
        if (strcmp(communicate->cmd_param[1], "~\0") == 0) {
            chdir(communicate->cmd.path_user);
            dprintf(*sock_cli_fd, CMD_CWD_OK);
            return (SUCCESS);
        }
        else if (strcmp(communicate->cmd_param[1], "\0") == 0
        || opendir(communicate->cmd_param[1]) == NULL)
            dprintf(*sock_cli_fd, CMD_CWD_KO);
        else {
            chdir(communicate->cmd_param[1]);
            dprintf(*sock_cli_fd, CMD_CWD_OK);
        }
        return (SUCCESS);
    }
    return (FAILURE);
}

bool pwd_cmd(communicate_t *communicate, int *sock_cli_fd, int i)
{
    (void)i;
    if (strcmp(communicate->cmd_param[0], "PWD\0") == 0) {
        bzero(communicate->cmd.path, sizeof(communicate->cmd.path));
        getcwd(communicate->cmd.path, sizeof(communicate->cmd.path));
        dprintf(*sock_cli_fd, "257 \"%s\" created.\r\n", communicate->cmd.path);
        return (SUCCESS);
    }
    return (FAILURE);
}

bool cdup_cmd(communicate_t *communicate, int *sock_cli_fd, int i)
{
    (void)i;
    if (strcmp(communicate->cmd_param[0], "CDUP\0") == 0) {
        chdir("..");
        dprintf(*sock_cli_fd, CMD_CWD_OK);
        return (SUCCESS);
    }
    return (FAILURE);
}

bool dele_cmd(communicate_t *communicate, int *sock_cli_fd, int i)
{
    (void)i;
    if (strcmp(communicate->cmd_param[0], "DELE\0") == 0) {
        if (remove(communicate->cmd_param[1]) == -1)
            dprintf(*sock_cli_fd, CMD_CWD_KO);
        else
            dprintf(*sock_cli_fd, CMD_CWD_OK);
        return (SUCCESS);
    }
    return (FAILURE);
}

void bad_cmd(communicate_t *communicate, char client_msg[], int *sock_cli_fd)
{
    if (strcmp(communicate->cmd_param[0], "\0") == 0
    && strcmp(communicate->cmd_param[1], "\0") == 0
    && strcmp(client_msg, "\r\n\0") != 0)
        write(*sock_cli_fd, BAD_INPUT, strlen(BAD_INPUT));
    if (strcmp(communicate->cmd_param[0], "\0") != 0
    || strcmp(communicate->cmd_param[1], "\0") != 0)
        write(*sock_cli_fd, BAD_INPUT, strlen(BAD_INPUT));
}
