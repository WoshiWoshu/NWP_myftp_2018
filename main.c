/*
** EPITECH PROJECT, 2019
** ftp_server
** File description:
** main.c
*/

#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include "my_ftp.hpp"

static bool help(char **av)
{
    if (av[1] != NULL)
        if (strcmp(av[1], "-help") == 0) {
            puts("USAGE:\t./myftp port path");
            puts("\tport is the port number \
on which the server socket listens");
            puts("\tpath is the path to the home \
directory for the Anonymous user");
            return (SUCCESS);
        }
    return (FAILURE);
}

static bool error_handle(int ac, char **av)
{
    if (ac != 3)
        return (FAILURE);
    for (int i = 0; av[1][i] != '\0'; ++i)
        if (av[1][i] < '0' || av[1][i] > '9')
            return (FAILURE);
    if (opendir(av[2]) == NULL)
        return (FAILURE);
    return (SUCCESS);
}

int main(int ac, char **av)
{
    if (help(av) == SUCCESS)
        return (0);
    if (error_handle(ac, av) == FAILURE)
        return (84);
    if (my_ftp(av) == FAILURE)
        return (84);
    return (0);
}
