/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Get the current client's path
*/

#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "client.h"

char *get_current_path(const client_t *client)
{
    char *pwd = NULL;

    pwd = strdup(client->path + strlen(client->parent_path));
    if (strlen(pwd) == 0) {
        free(pwd);
        pwd = strdup("/");
    }
    return (pwd);
}