/*
** EPITECH PROJECT, 2019
** ftp server
** File description:
** parsing
*/

#include "my_ftp.hpp"

void get_second_elem_array(char buff[], char new_buff[])
{
    int j = 0;
    int i = 0;

    while (buff[i] == ' ' || buff[i] == '\t')
        i++;
    while (buff[i] != ' ' && buff[i] != '\t' && buff[i] != '\r'
    && buff[i] != '\n')
        i++;
    while (buff[i] == ' ' || buff[i] == '\t')
        i++;
    while (buff[i] != ' ' && buff[i] != '\t' && buff[i] != '\r'
    && buff[i] != '\n') {
        new_buff[j] = buff[i];
        j++;
        i++;
    }
    new_buff[j] = '\0';
}

void get_first_elem_array(char buff[], char new_buff[])
{
    int j = 0;

    for (int i = 0; buff[i] != '\r' && buff[i] != '\n'; i++) {
        if (buff[i] != ' ' && buff[i] != '\t') {
            new_buff[j] = buff[i];
            j++;
        }
        if ((buff[i] == ' ' || buff[i] == '\t') && j != 0)
            break;
    }
    new_buff[j] = '\0';
}

int check_back_slash_n_r(char buff[])
{
    for (int i = 0; buff[i] != '\0'; i++) {
        if ((buff[i] == '\r' && buff[i + 1] == '\n' && buff[i + 2] == '\0')
        || (buff[i] == '\n' && buff[i + 1] == '\0'))
            return (SUCCESS);
    }
    return (FAILURE);
}
