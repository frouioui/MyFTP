/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Check if the given user name is correct or not
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_username_correct(const char *username)
{
    return (strcmp(username, "anonymous") == 0);
}