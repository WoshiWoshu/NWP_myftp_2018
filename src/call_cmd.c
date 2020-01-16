/*
** EPITECH PROJECT, 2019
** ftp server
** File description:
** call_cmd.c
*/

#include "my_ftp.hpp"

void call_user_commands(communicate_t *communicate,
    char client_msg[], int *sock_cli_fd)
{
    bool (*cmd_ptr[7])(communicate_t *, int *, int) = {quit_cmd, help_cmd,
    noop_cmd, cwd_cmd, pwd_cmd, cdup_cmd, dele_cmd};

    for (int i = 0; i < CMD_NB; i++)
        if ((*cmd_ptr[i])(communicate, sock_cli_fd, i) == SUCCESS)
            return;
    bad_cmd(communicate, client_msg, sock_cli_fd);
}
