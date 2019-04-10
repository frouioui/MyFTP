/*
** EPITECH PROJECT, 2019
** MyFTP
** File description:
** Source file of the CDW command
*/

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include "server.h"
#include "client.h"
#include "msg_queue.h"
#include "command.h"
#include "string_parser.h"

static char *check_path(char *root, char *root_2, char *cmd)
{
    char *new_path = NULL;
    char *buf = NULL;

    cmd[0] == 0 ? strcpy(cmd, root_2) : 0;
    root_2 = realpath(root_2, NULL);
    root = realpath(root, NULL);
    if (cmd[0] == '/') {
        buf = calloc(1, sizeof(char) * (strlen(root) + strlen(root_2) +
            strlen(cmd) + 1));
        buf = strcat(buf, root);
        buf = strcat(buf, cmd);
        cmd = buf;
    }
    new_path = realpath(cmd, new_path);
    if (!new_path)
        return (NULL);
    if (strncmp(new_path, root_2, strlen(root)))
        return (root);
    return (new_path);
}

static char *clear_path_client(char *root, char *path)
{
    char *new = malloc(sizeof(char) * (strlen(root) + strlen(path) + 1));
    int a = 0;

    new[a++] = '/';
    for (unsigned int i = strlen(root); i < strlen(path) && path[i]; i++) {
        new[a++] = path[i];
        new[a] = '\0';
    }
    free(path);
    return (new);
}

void cwd_user(server_t *server, __attribute__((unused)) client_t *client,
    char *cmd)
{
    char *new_p = NULL;

    if (is_connected(client->user) == false) {
        append_new_message(&client->write_queue, RESP_530_NEED_CONNECT);
    } else {
        new_p = strdup(cmd);
        new_p = check_path(client->parent_path, client->path, new_p);
        if (new_p == NULL) {
            append_new_message(&client->write_queue, RESP_550);
            free(new_p);
            return;
        }
        new_p = clear_path_client(client->parent_path, new_p);
        free(client->path);
        client->path = new_p;
        append_new_message(&client->write_queue, RESP_250);
    }
    FD_SET(client->socket, &server->sets[WRITING_SET]);
}