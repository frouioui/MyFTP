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
    char *path = NULL;
    char *full_root = NULL;
    char *pwd = NULL;

    path = realpath(client->path[0] == '/' ? client->path + 1 : client->path,
        NULL);
    full_root = realpath(client->parent_path, NULL);
    pwd = strdup(path + strlen(full_root));
    if (strlen(pwd) == 0) {
        free(pwd);
        pwd = strdup("/");
    }
    free(path);
    free(full_root);
    return (pwd);
}